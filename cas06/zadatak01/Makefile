CXX = g++

izvrsni: parser.tab.o lex.yy.o Polinom.o
	$(CXX) $^ -o $@

Polinom.o: Polinom.cpp Polinom.hpp
	$(CXX) -c $< 

lex.yy.o: lex.yy.c parser.tab.hpp Polinom.hpp
	$(CXX) -c $<

lex.yy.c: lekser.l
	flex $<

parser.tab.o: parser.tab.cpp parser.tab.hpp Polinom.hpp
	$(CXX) -c $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d $<

.PHONY: clean
clean: 
	rm -f *.o parser.tab* izvrsni lex.yy*