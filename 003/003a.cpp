#include "lib/get.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int process(std::string & input) {
  std::istringstream stream(input);
  std::string line;
  long joltage = 0;
  while (std::getline(stream, line)) {
    int largest = 0;
    int largest_second = 0;
    for (size_t i = 0; i < line.size()-1; i++) {
      int d1 = line[i] - '0';
      int d2 = line[i+1] - '0';

      if (d1 > largest) {
        largest = d1;
        largest_second = d2;
      } else if (d2 > largest_second) {
        largest_second = d2;
      }
    }
    joltage = joltage + (10 * largest) + largest_second;
  }
  std::cout << joltage << std::endl;
  return 1;
}

int main (int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << std::endl;
    std::cerr << "Example: " << argv[0] << std::endl;
    return 0;
  }
  
  std::string url = argv[1];
  std::string content;
  std::string session_cookie = argv[2];

  if (get(url, session_cookie, content) != "Error") {
    process(content);
  } else {
    std::cerr << "Failed to fetch URL" << std::endl;
    return 0;
  }
  return 1;
}
