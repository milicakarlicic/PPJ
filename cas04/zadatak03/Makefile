# promenljive za kompilator i opcije
CXX = g++
CXXFLAGS = -Wall

# $^ - kompletna lista zavisnosti
# $@ - cilj pravila
# $< - prvi iz liste zavisnosti
izvrsni: KompleksniBrojevi.o Test.o
	$(CXX) $(CXXFLAGS) $^ -o $@

KompleksniBrojevi.o: KompleksniBrojevi.cpp KompleksniBrojevi.h
	$(CXX) $(CXXFLAGS) -c $<

Test.o: Test.cpp KompleksniBrojevi.h
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o izvrsni 