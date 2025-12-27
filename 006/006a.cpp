#include "lib/get.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <array>

int process(std::string& input) {
  std::istringstream stream(input);
  std::string line;
  long long num;
  char sym;
  std::vector<std::array<long long, 2>> v;
  std::vector<char> o;
  bool first = true;
  int count = 0;

  while (std::getline(stream, line)) {
    if (line.empty()) continue;

    std::istringstream iss(line);

    if (first) {
      while (iss >> num) {
        std::array<long long, 2> a = {num, num};
        v.push_back(a);
        count++;
      }
      first = false;
    } else if (line[0] == '*' || line[0] == '+') {
      while (iss >> sym) {
        o.push_back(sym);
      }
    } else {
      int idx = 0;
      while (iss >> num) {
        v[idx][0] += num; 
        v[idx][1] *= num;
        idx++;
      }
    }
  }
  long long total = 0;
  int i = 0;
  while (i < (int) o.size()) {
    if (o[i] == '+') {
      total += v[i][0];
    } else {
      total += v[i][1];
    }
    i++;
  }

  std::cout << total << std::endl;
  return 1;
}

int main (int argc, char *argv[]) {
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
