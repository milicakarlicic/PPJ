CXX = g++

izvrsni: DinamickiNiz.o Test.o
	$(CXX) $^ -o $@

DinamickiNiz.o: DinamickiNiz.cpp DinamickiNiz.hpp
	$(CXX) -c $<

Test.o: Test.cpp DinamickiNiz.hpp
	$(CXX) -c $<

.PHONY: clean
clean:
	rm -f izvrsni *.o
