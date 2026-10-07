CXX = g++
CXXFLAGS = -std=c++17 -O2

all: std brute gen gen_data spj

std:
	$(CXX) code/std.cpp $(CXXFLAGS) -o std

brute:
	$(CXX) code/brute.cpp $(CXXFLAGS) -o brute

gen:
	$(CXX) code/gen.cpp $(CXXFLAGS) -o gen

gen_data:
	$(CXX) code/gen_data.cpp $(CXXFLAGS) -o gen_data

spj:
	$(CXX) spj.cpp $(CXXFLAGS) -o spj

data: gen_data
	./gen_data
	chmod +x scripts/gen_out.sh
	./scripts/gen_out.sh

check: all
	chmod +x scripts/check.sh
	./scripts/check.sh

clean:
	rm -f std brute gen gen_data spj
