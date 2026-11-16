CXX = g++

izvrsni: kompleksni.o main.o
	$(CXX) $^ -o $@

kompleksni.o: kompleksni.cpp kompleksni.hpp
	$(CXX) -c $<

main.o: main.cpp kompleksni.hpp
	$(CXX) -c $<

.PHONY: clean
clean:
	rm -f *.o a.out izvrsni