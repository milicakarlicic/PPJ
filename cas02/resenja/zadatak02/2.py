#!/usr/bin/python3

import sys
import os
import re

if len(sys.argv) != 2:
    sys.exit('Pozivanje: ./2.py putanja_do_dir')

putanja_do_dir = sys.argv[1]
if not os.path.isdir(putanja_do_dir):
    sys.exit('Nije direktorijum!')
sadrzaj = os.listdir(putanja_do_dir)

regex_alas = r'm[irmns][0-9]{5}'
studenti = {}
# studenti = {alas1 : {1 : 'cpp', 2 : 'java',...}, alas2 : {...}}
for rad_studenta in sadrzaj:
    rezultat = re.fullmatch(regex_alas, rad_studenta)
    if rezultat is None:
        continue
    studenti[rad_studenta] = {}

regex_zadatak = r'([1-4])\.(java|py|cpp|c)'
for alas, zadaci in studenti.items():
    putanja_alas = putanja_do_dir + os.path.sep + alas  # ili os.path.join(putanja_do_dir, alas)
    if not os.path.isdir(putanja_alas):
        continue

    for zadatak in os.listdir(putanja_alas):
        rezultat_zadatka = re.fullmatch(regex_zadatak, zadatak)
        if rezultat_zadatka is None:
            continue
        
        broj_zadatka = int(rezultat_zadatka.group(1))
        ekstenzija = rezultat_zadatka.group(2)
        # {1: 'cpp', ...}
        if broj_zadatka not in zadaci:
            zadaci[broj_zadatka] = ekstenzija

for alas, zadaci in studenti.items():
    print('Alas: ' + alas + ', zadaci: ' + str(zadaci))
