# use g++ with C++11 support
CXX=g++
CXXFLAGS?=-Wall -pedantic -g -O0 -std=c++11
OUTFILES=compress uncompress

all: $(OUTFILES)

compress: compress.cpp Helper.cpp HCTree.cpp Helper.hpp HCTree.hpp
	$(CXX) $(CXXFLAGS) -o compress compress.cpp Helper.cpp HCTree.cpp

uncompress: uncompress.cpp Helper.cpp HCTree.cpp Helper.hpp HCTree.hpp
	$(CXX) $(CXXFLAGS) -o uncompress uncompress.cpp Helper.cpp HCTree.cpp

clean:
	rm -f $(OUTFILES) *.o

