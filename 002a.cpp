#include "lib/get.h"
#include <iostream>
#include <vector>
#include <cmath>

struct Range {
  long start;
  long end;
};

std::vector<Range> set_ranges(std::string& input) {
  size_t i = 0;
  int get_start = true;
  int get_end = false;
  long start = 0;
  long end = 0;
  std::vector<Range> list;

  while (i < input.size()) {
    if (input[i] == '-') {
      get_end = true;
      end = 0;
    } else if (input[i] == ',') {
      list.push_back({start, end});
      get_start = true;
      start = 0;
    } else if (get_start) {
      start = atol(input.c_str() + i);
      get_start = false;
    } else if (get_end) {
      end = atol(input.c_str() + i);
      get_end = false;
    }
    i++;
  }
  list.push_back({start, end});
  return list;
}

int process(std::string& input) {
  std::vector<Range> list = set_ranges(input);
  long long a_out = 0;
  for (Range range: list) {
    // If the range only contains odd lengths, it can't contain a sequence twice
    if ((int)log10(range.start) % 2 == 0 && (int)log10(abs(range.end)) % 2 == 0) continue;

    long c = range.start;
    while (c <= range.end) {
      int length = (int)log10(c) + 1;
      if (length % 2 == 1) { 
        c++;
        continue;
      }
      int half = length / 2;
      long long divisor = (long long)pow(10, half);
      long long left = c / divisor;
      long long right = c % divisor;
      
      if (left == right) {
        a_out += c;
        long long next = ((left * divisor) + 1) + (right + 1);

        if (next <= range.end) {
          c = next;
        } else {
          break;
        }
          
      } else {
          c++;
      }
    }
  }
  std::cout << a_out << std::endl;
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
