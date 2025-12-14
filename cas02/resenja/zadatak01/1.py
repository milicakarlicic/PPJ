#!/usr/bin/python3

# Ako hocemo da pokrecemo skript sa ./1.py u prvoj liniji definisemo
# specijalni komentar koji pocinje sa #! i unosimo putanju do interpretatora
# koji ce izvrsavati skript
# Putanja do interpretatora se dobija sa: which python3
# Dodavanje prava za izvrsavanje: chmod +x 1.py

import sys
import re

if len(sys.argv) != 2:
    sys.exit('Pozivanje: ./1.py putanja_do_html')

putanja_do_datoteke = sys.argv[1]
if not putanja_do_datoteke.lower().endswith('.html'):
    sys.exit('Nije html!')

try:
    f = open(putanja_do_datoteke)
    sadrzaj = f.read()
    f.close()
except FileNotFoundError:
    sys.exit('Datoteka ne postoji!')

regex_student = r'<td>\s*([a-zA-Z]+)((\s+[a-zA-Z]+)+)\s*</td>'
regex_student += r'\s*<td>\s*(m[irmsn][0-9]{5})\s*</td>'
regex_student += r'\s*<td>\s*([0-9]|[1-4][0-9]|50)\s*</td>'
regex_student += r'\s*<td>\s*([0-9]|[1-4][0-9]|50)\s*</td>'

# lista ciji je jedan element torka sa grupama iz regex-a
lista_poklapanja = re.findall(regex_student, sadrzaj)
studenti = []
for poklapanje in lista_poklapanja:
    # (ime prezime, indeks, ukupno poena)
    ime = poklapanje[0].strip()
    prezime = poklapanje[1].strip()

    alas = poklapanje[3] # mr22011
    godina = '20' + alas[2:4] # 2022
    broj = int(alas[-3:]) # 11
    indeks = str(broj) + '/' + godina

    poeni_prakticni = int(poklapanje[4])
    poeni_usmeni = int(poklapanje[5])

    studenti.append((ime + ' ' + prezime, indeks, poeni_prakticni + poeni_usmeni))

# [(ime prezime, indeks, broj poena), ..]
studenti.sort(key = lambda element: -element[2])

for student in studenti:
    print(student[0], student[1], student[2])