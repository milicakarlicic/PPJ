# cilj_pravila: lista zavisnosti
#		kako dobijamo cilj pravila na osnovu liste zavisnosti

a.out: lex.yy.c
	gcc lex.yy.c

lex.yy.c: 5.l
	flex 5.l

.PHONY: clean
clean:
	rm -f a.out lex.yy.c
