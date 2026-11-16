CXX = g++

izvrsni: dinamicki_niz.o main.o
	$(CXX) $^ -o $@

dinamicki_niz.o: dinamicki_niz.cpp dinamicki_niz.hpp
	$(CXX) -c $<

main.o: main.cpp dinamicki_niz.hpp
	$(CXX) -c $<

.PHONY: clean
clean:
	rm -f *.o izvrsni