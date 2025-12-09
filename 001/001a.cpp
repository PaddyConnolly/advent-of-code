#include <iostream>
#include <curl/curl.h>
#include <string>
#include "lib/get.h"
#include <sstream>

int safecrack(std::string& instructions) {
  std::istringstream stream(instructions);
  std::string line;
  int dial = 50;
  int zeroes = 0;
  while (std::getline(stream, line)) {
    int move = std::stoi(line.substr(1));
    int direction = line[0];
    if (direction == 'L') {
      dial -= move;

    } else {
      dial += move;

    }
    if (dial % 100 == 0) zeroes++;
  }

  std::cout << zeroes << std::endl;
  
  return 1;
}

int main (int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << std::endl;
    std::cerr << "Example: " << argv[0] << std::endl;
    return 0;
  }
  
  std::string url = argv[1];
  std::string content;
  std::string session_cookie = argv[2];

  if (get(url, session_cookie, content) != "Error") {
    safecrack(content);
  } else {
    std::cerr << "Failed to fetch URL" << std::endl;
    return 0;
  }
  return 1;
}
