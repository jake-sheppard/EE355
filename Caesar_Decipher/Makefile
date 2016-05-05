# change CXX to g++ or clang++ if you like, but will lose all warnings.
CXX = compile 

all: caesarlib.o libtest shift crack 

clean:
	rm -f caesarlib.o libtest shift crack 

caesarlib.o: caesarlib.cpp caesarlib.h
	$(CXX) -c caesarlib.cpp -o caesarlib.o

%: %.cpp caesarlib.o caesarlib.h
	$(CXX) $@.cpp caesarlib.o -o $@

