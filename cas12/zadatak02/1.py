#!/usr/bin/python3

import re, sys

def ispisi_na_osnovu_opcije(podaci, opcija, vrednost):
    for redni_broj in podaci: #
        if opcija == '-a':
            if re.search(rf'\b{vrednost}\b', podaci[redni_broj]['autori']):
                print(podaci[redni_broj]['kompletno_poklapanje'])
        elif opcija == '-g':
            if int(vrednost) <= podaci[redni_broj]['godina']:
                print(podaci[redni_broj]['kompletno_poklapanje'])
        elif opcija == '-i':
            if 'izdavac' in podaci[redni_broj] and vrednost in podaci[redni_broj]['izdavac']:
                print(podaci[redni_broj]['kompletno_poklapanje'])
        elif opcija == '-p':
            if 'broj_strana' in podaci[redni_broj] and int(vrednost) <= podaci[redni_broj]['broj_strana']:
                print(podaci[redni_broj]['kompletno_poklapanje'])
        else:
            print('Nepoznata opcija!!!')
            return

##################################################

redni_broj = r'(?P<redni_broj>0|[1-9][0-9]*)'
autor = r'([A-Z]\.\s*)+\s+[A-Z][a-z]+'
autori = rf'(?P<autori>({autor},\s*)*{autor},?\s+and\s+{autor}|{autor})'
naziv_rada = r'(?P<naziv_rada>(\w|-)+(\s+(\w|-)+)*)'
naziv_konf = r'(?P<naziv_konf>In\s+[^,]+)'
broj_strana = r'(pages\s+(?P<leva_granica>[0-9]{1,})\s*-\s*(?P<desna_granica>[0-9]{1,}))'
volume = r'volume\s*[0-9]+\s+of\s+LNCS'
izdavac = r'(?P<izdavac>[^,]+)'
godina = r'(?P<godina>[0-9]{4})'

ka_konferencija = re.compile(rf'{redni_broj}\s*:\s*{autori}\s*\.\s*{naziv_rada}\s*\.\s*{naziv_konf}\s*,(\s*{volume}\s*,)?(\s*{broj_strana}\s*,)?\s*{godina}\.') 
ka_knjiga = re.compile(rf'{redni_broj}\s*:\s*{autori}\s*\.\s*{naziv_rada}\s*\.\s*{izdavac}\s*,\s*{godina}\.') 

podaci = {}
with open(sys.argv[1]) as f:
    sadrzaj = f.read()

    for poklapanje in ka_konferencija.finditer(sadrzaj):
        # redni_broj -> {'naziv' : naziv_rada, ...}
        podaci[poklapanje.group('redni_broj')] = {
            'naziv' : poklapanje.group('naziv_rada'),
            'autori' : poklapanje.group('autori'),
            'naziv_konf' : poklapanje.group('naziv_konf'),
            'godina' : int(poklapanje.group('godina')),
            'kompletno_poklapanje' : poklapanje.group() # treba nam zbog formata za ispis podataka
        }
        if poklapanje.group('leva_granica') and poklapanje.group('desna_granica'):
            podaci[poklapanje.group('redni_broj')]['broj_strana'] = int(poklapanje.group('desna_granica'))\
            - int(poklapanje.group('leva_granica')) + 1

    for poklapanje in ka_knjiga.finditer(sadrzaj):
        # preskacemo konferencijske radove - ako nema volume i pages
        # moze doci do poklapanja naziva konf i izdavaca       
        if poklapanje.group('redni_broj') in podaci:
            continue
        podaci[poklapanje.group('redni_broj')] = {
            'naziv' : poklapanje.group('naziv_rada'),
            'autori' : poklapanje.group('autori'),
            'izdavac' : poklapanje.group('izdavac'),
            'godina' : int(poklapanje.group('godina')),
            'kompletno_poklapanje' : poklapanje.group()
        }

if len(sys.argv) > 2:
    ispisi_na_osnovu_opcije(podaci, sys.argv[2], sys.argv[3])
else:
    # sortiramo podatke po godini (iteracija kroz mapu iterira kroz njene kljuceve)
    sortirani_kljucevi = sorted(podaci, key = lambda kljuc: int(podaci[kljuc]['godina']))
    for kljuc in sortirani_kljucevi:
        print(podaci[kljuc]['kompletno_poklapanje'])
