#include "lib/get.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <unordered_map>


int process(std::string & input) {
  std::istringstream stream(input);
  std::string line;

  long long total_joltage = 0;
  long long joltage = 0;
  int batteries_allowed = 12;
  
  while (std::getline(stream, line)) {
    std::unordered_map<int, int> map = {{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0},{11,0},{12,0}};
    joltage = 0;
    int bank = (int) line.size();
    for (int i = 0; i < bank; i++) {
      int valid_start = std::max((i+1) - (bank - batteries_allowed), 1);
      bool update = false;
      for (int j = valid_start; j <= batteries_allowed; j++) {
        if (update) {
          map[j] = 0;
        } else if (line[i] > map[j]) {
          map[j] = line[i];
          update = true;
        }
      }
    }

    for (int i = 1; i <= batteries_allowed; i++) {

      joltage = joltage + pow(10, (12-i))*(map[i]-'0');


    }
    total_joltage += joltage;

    
  }
  std::cout << total_joltage << std::endl;
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
