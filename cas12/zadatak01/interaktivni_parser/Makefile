CXX = g++

izvrsni: parser.tab.o lex.yy.o TablicaSimbola.o Graf.o
	$(CXX) $^ -o $@

TablicaSimbola.o: TablicaSimbola.cpp TablicaSimbola.hpp
	$(CXX) -c $<

Graf.o: Graf.cpp Graf.hpp
	$(CXX) -c $<

parser.tab.o: parser.tab.cpp parser.tab.hpp TablicaSimbola.hpp Graf.hpp
	$(CXX) -c $< 

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d $<

lex.yy.o: lex.yy.c parser.tab.hpp TablicaSimbola.hpp Graf.hpp
	$(CXX) -c $< 

lex.yy.c: lekser.l
	flex $<

.PHONY: clean
clean:	
	rm -f *.o parser.tab* lex.yy* izvrsni
