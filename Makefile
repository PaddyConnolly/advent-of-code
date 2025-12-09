CXX = g++
CXXFLAGS = -Wall -O2
LDFLAGS = -lcurl

TARGETS = 001a 001b 002a 002b 003a 003b 004a 004b 005a 005b \
          006a 006b 007a 007b 008a 008b 009a 009b 010a 010b \
          011a 011b 012a 012b 013a 013b 014a 014b 015a 015b \
          016a 016b 017a 017b 018a 018b 019a 019b 020a 020b \
          021a 021b 022a 022b 023a 023b 024a 024b 025a 025b

BIN_TARGETS = $(addprefix bin/, $(TARGETS))

lib/get.o: lib/get.cpp lib/get.h
	$(CXX) $(CXXFLAGS) -c lib/get.cpp -o lib/get.o

bin/%: %.cpp lib/get.o | bin
	$(CXX) $(CXXFLAGS) -o $@ $< lib/get.o $(LDFLAGS)

bin:
	mkdir -p bin

all: $(BIN_TARGETS)

clean:
	rm -f lib/get.o
	rm -rf bin

.PHONY: all clean
