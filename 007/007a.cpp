#include "lib/get.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

int process(std::string &input) {
  std::istringstream stream(input);
  std::string line;
  int line_number = 0;
  int start;
  int min_pos;
  int max_pos;
  std::unordered_set<int> beam;
  int splits = 0;

  while (std::getline(stream, line)) {
    if (line_number % 2 == 0) {
      if (line_number == 0) {
        for (int i = 0; i < (int)line.size(); i++) {
          if (line[i] == 'S') {
            start = i;
            min_pos = start;
            max_pos = start;
            beam.insert(start);
          }
        }
      } else {
        for (int i = min_pos; i <= max_pos; i++) {
          if (line[i] == '^') {
            if (i - 1 < min_pos) {
              min_pos--;
            }

            if (i + 1 > max_pos) {
              max_pos++;
            }

            if (beam.count(i) == 1) {
              beam.erase(i);
              beam.insert(i - 1);
              beam.insert(i + 1);
              splits++;
            }
          }
        }
      }
    }
    line_number++;
  }
  std::cout << splits << std::endl;

  return 1;
}

int main(int argc, char *argv[]) {
  std::string url = argv[1];
  std::string session_cookie = argv[2];
  std::string content;

  if (get(url, session_cookie, content) != "Error") {
    process(content);
  } else {
    std::cerr << "Failed to fetch URL" << std::endl;
  }
  return 0;
}
