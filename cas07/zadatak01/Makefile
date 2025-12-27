CXX = g++

izvrsni: Izrazi.o Test.o
	$(CXX) $^ -o $@

Izrazi.o: Izrazi.cpp Izrazi.hpp
	$(CXX) -c $<

Test.o: Test.cpp Izrazi.hpp
	$(CXX) -c $<

.PHONY: clean
clean:
	rm -f *.o izvrsni