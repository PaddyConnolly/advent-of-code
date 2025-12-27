#include "lib/get.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <deque>
#include <iostream>
#include <sstream>
#include <vector>

int process(std::string &input) {
  std::istringstream stream(input);

  std::string line;
  std::vector<std::deque<char>> grid;
  int line_length = 0;
  int line_count = 0;
  std::string ops;

  while (std::getline(stream, line)) {
    if (line.empty())
      continue;

    if (line.find("*") != std::string::npos) {
      ops = line;
      std::string ops_only;

      for (char c : ops) {
        if (c != ' ') {
          ops_only.push_back(c);
        }
      }

      std::reverse(ops_only.begin(), ops_only.end());
      ops = ops_only;
      break;
    }

    std::deque<char> deq(std::begin(line), std::end(line));
    deq.push_front(' ');
    grid.push_back(deq);
    line_length = (int)deq.size();

    line_count++;
  }

  long long total = 0;
  int problems_completed = 0;
  std::vector<long long> problem;
  for (int i = line_length - 1; i >= 0; --i) {
    bool isSpaces = true;
    long long num = 0;
    int digit_count = 0;
    for (int j = line_count - 1; j >= 0; --j) {
      if (grid[j][i] != ' ') {
        isSpaces = false;
        long digit = std::pow(10, digit_count) * (grid[j][i] - '0');
        num += digit;
        digit_count++;
      }
    }

    if (num != 0) {
      problem.push_back(num);
    }

    if (isSpaces) { // Empty column means we can perform operation

      long long add_value = 0;
      long long mul_value = 1;
      for (long long i : problem) {
        if (ops[problems_completed] == '*') {
          mul_value *= i;
        } else {
          add_value += i;
        }
      }
      problems_completed++;
      total += std::max(add_value, mul_value);
      problem.clear();
    }
  }
  std::cout << total << std::endl;

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
