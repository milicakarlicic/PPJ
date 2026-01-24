CXX = g++

izvrsni: parser.tab.o lex.yy.o Funkcije.o TablicaSimbola.o SintaksnoStablo.o
	$(CXX) $^ -o $@

SintaksnoStablo.o: SintaksnoStablo.cpp SintaksnoStablo.hpp
	$(CXX) -c $<	

Funkcije.o: Funkcije.cpp Funkcije.hpp
	$(CXX) -c $< 

TablicaSimbola.o: TablicaSimbola.cpp TablicaSimbola.hpp
	$(CXX) -c $< 

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CXX) -c $< 

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<

lex.yy.o: lex.yy.c parser.tab.hpp
	$(CXX) -c $< 

lex.yy.c: lekser.l
	flex $<

.PHONY: clean
clean:	
	rm -f *.o parser.tab* lex.yy* izvrsni parser.output
