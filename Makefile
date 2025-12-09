CXX = g++
CXXFLAGS = -Wall -O2 -I.
LDFLAGS = -lcurl

lib/get.o: lib/get.cpp lib/get.h
	$(CXX) $(CXXFLAGS) -c lib/get.cpp -o lib/get.o

bin:
	mkdir -p bin

all: lib/get.o | bin
	@for f in 0*/*.cpp; do \
		name=$$(basename $$f .cpp); \
		echo "Building bin/$$name"; \
		$(CXX) $(CXXFLAGS) -o bin/$$name $$f lib/get.o $(LDFLAGS); \
	done

0%: lib/get.o | bin
	$(CXX) $(CXXFLAGS) -o bin/$@ 0*/$@.cpp lib/get.o $(LDFLAGS)

clean:
	rm -f lib/get.o
	rm -rf bin

.PHONY: all clean

