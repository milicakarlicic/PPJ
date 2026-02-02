CXX = g++

izvrsni: parser.o lex.yy.o
	$(CXX) -o $@ $^

parser.o: parser.cpp tokeni.hpp
	$(CXX) -c $<

lex.yy.o: lex.yy.c tokeni.hpp
	$(CXX) -c $<

lex.yy.c: lekser.l
	flex $<

.PHONY: clean
clean:
	rm -f *.o izvrsni lex.yy*
