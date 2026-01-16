CXX = g++
CXXFLAGS = -Wall -g

izvrsni: parser.tab.o lex.yy.o SintaksnoStablo.o
	$(CXX) $(CXXFLAGS) -o $@ $^

SintaksnoStablo.o: SintaksnoStablo.cpp SintaksnoStablo.hpp
	$(CXX) $(CXXFLAGS) -c $<

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d $<

lex.yy.o: lex.yy.c parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c $<

lex.yy.c: lekser.l
	flex $<

.PHONY: clean
clean:
	rm -f *.o izvrsni parser.tab* lex.yy*
	
