CXX = g++

izvrsni: parser.tab.o lex.yy.o
	$(CXX) $^ -o $@

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CXX) -c $<

# opcija -d generise parser.tab.hpp 
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d $<

lex.yy.o: lex.yy.c parser.tab.hpp
	$(CXX) -c $<

lex.yy.c: lekser.l
	flex $<

.PHONY: clean
clean:
	rm -f *.o lex.yy* parser.tab* izvrsni