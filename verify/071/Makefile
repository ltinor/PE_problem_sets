CXX = g++
CXXFLAGS = -std=c++17 -O2

all: std brute gen gen_data

std:
	$(CXX) code/std.cpp $(CXXFLAGS) -o std

brute:
	$(CXX) code/brute.cpp $(CXXFLAGS) -o brute

gen:
	$(CXX) code/gen.cpp $(CXXFLAGS) -o gen

gen_data:
	$(CXX) code/gen_data.cpp $(CXXFLAGS) -o gen_data

data: gen_data
	./gen_data
	bash scripts/gen_out.sh

check: all
	bash scripts/check.sh

clean:
	rm -f std brute gen gen_data
