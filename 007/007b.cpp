#include "lib/get.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

std::vector<std::string> lines;
std::vector<std::vector<long long>> memo;

long long recur(int x, int y, int max_y) {
  if (y == max_y) {
    if (lines[y][x] == '^') {
      return 2;
    } else {
      return 1;
    }
  }

  if (memo[y][x] != -1)
    return memo[y][x];

  long long res;
  if (lines[y][x] == '^') {
    res = recur(x - 1, y + 1, max_y) + recur(x + 1, y + 1, max_y);
  } else {
    res = recur(x, y + 1, max_y);
  }

  memo[y][x] = res;
  return res;
}

int process(std::string &input) {
  std::istringstream stream(input);
  std::string line;
  int start = 0;
  std::string substring;
  int line_count = 0;
  while (std::getline(stream, line)) {
    if (line_count % 2 == 0) {
      lines.push_back(line);
    }
    line_count++;
  }

  std::string first_line = lines[0];
  for (int i = 0; i < (int)first_line.size(); i++) {
    if (lines[0][i] == 'S') {
      start = i;
    }
  }

  memo.assign(lines.size(), std::vector<long long>(lines[0].size(), -1));

  long long paths = recur(start, 0, (int)lines.size() - 1);
  std::cout << paths << std::endl;

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
