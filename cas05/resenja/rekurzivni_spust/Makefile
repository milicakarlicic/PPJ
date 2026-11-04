# cilj pravila: lista zavisnosti
#		na koji nacin dobijamo cilj pravila na osnovu liste zavisnosti

a.out: lex.yy.o parser.o
	g++ lex.yy.o parser.o

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

parser.o: parser.cpp
	g++ -c parser.cpp

lex.yy.c: lekser.l
	flex lekser.l

# specijalno pravilo za brisanje svih generisanih fajlova
.PHONY: clean
clean:
	rm *.o lex.yy.c a.out