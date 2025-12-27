CXX = g++
# ako hocemo da odredimo tacnu liniju u kojoj je doslo do curenja memorije koriscenjem Valgrind-a
CXXFLAGS = -g

izvrsni: parser.tab.o lex.yy.o Polinom.o
	$(CXX) $(CXXFLAGS) $^ -o $@

Polinom.o: Polinom.cpp Polinom.hpp
	$(CXX) $(CXXFLAGS) -c $< 

lex.yy.o: lex.yy.c parser.tab.hpp Polinom.hpp
	$(CXX) $(CXXFLAGS) -c $<

lex.yy.c: lekser.l
	flex $<

parser.tab.o: parser.tab.cpp parser.tab.hpp Polinom.hpp
	$(CXX) $(CXXFLAGS) -c $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d $<

.PHONY: clean
clean: 
	rm -f *.o parser.tab* izvrsni lex.yy*