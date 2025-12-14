#!/bin/python3

# primer pozivanja: ./1.py -aic Yacc 

import sys
import re

def ispisi_info_o_knjizi(naslov_trazena_knjiga, opcije):
    knjiga_nadjena = False
    for rbr, knjiga in knjige.items():
        if knjiga['naslov'] == naslov_trazena_knjiga:
            knjiga_nadjena = True
            if re.fullmatch(r'-[aicgn]+', opcije):
                if 'a' in opcije:
                    print(knjiga['autor'])
                if 'i' in opcije:
                    print(knjiga['izdavac']) 
                if 'g' in opcije:
                    print(knjiga['godina'])
                if 'c' in opcije:
                    print(str(knjiga['cena']) + knjiga['valuta'])           
            else:
                print(knjiga)
            break
    if not knjiga_nadjena:
        print('Knjiga sa zadatim naslovom ne postoji!')

if len(sys.argv) < 2:
    sys.exit('Pozivanje: .... ')

try:
    with open('knjige.xml', 'r') as dat:
        sadrzaj = dat.read()
except IOError:
    sys.exit('open')

# imenovane grupe (?P<ime_gupe>...)
regex = r'<knjiga\s*rbr\s*=\s*"(?P<rbr>\d+)"\s*>'
# . obuhvata i novi red jer smo ukljucili flag re.S <=> .|\n
regex += r'(?=.*?<naslov>\s*(?P<naslov>\w+(\s+\w+)*)\s*</naslov>)'
regex += r'(?=.*?<izdavac>\s*(?P<izdavac>.*?)\s*</izdavac>)'
regex += r'(?=.*?<godina_izdanja>\s*(?P<godina>(19\d{2}|20([01]\d|2[0-5])))\s*</godina_izdanja>)'
regex += r'(?=.*?<autor>\s*(?P<autor>\w+(\s+\w+)*)\s*</autor>)'
regex += r'(?=.*?<cena\s*valuta\s*=\s*"(?P<valuta>\w+)"\s*>\s*(?P<cena>\d+)\s*</cena>)'
regex += r'.*?'
regex += r'</knjiga>'

# kreiramo konacni automat 
automat_knjiga = re.compile(regex, re.S)

# {rbr_knjige -> knjiga,...}
# knjiga: {naslov -> ..., izdavac -> ..., ....}
knjige = {}
for poklapanje in automat_knjiga.finditer(sadrzaj):
    knjige[poklapanje.group('rbr')] = {}
    knjige[poklapanje.group('rbr')]['naslov'] = poklapanje.group('naslov')
    knjige[poklapanje.group('rbr')]['autor'] = poklapanje.group('autor')
    knjige[poklapanje.group('rbr')]['izdavac'] = poklapanje.group('izdavac')
    knjige[poklapanje.group('rbr')]['godina'] = int(poklapanje.group('godina'))
    knjige[poklapanje.group('rbr')]['cena'] = int(poklapanje.group('cena'))
    knjige[poklapanje.group('rbr')]['valuta'] = poklapanje.group('valuta')

naslov_trazena_knjiga = sys.argv[-1]
ispisi_info_o_knjizi(naslov_trazena_knjiga, sys.argv[1])