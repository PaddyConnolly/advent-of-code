#include "lib/get.h"
#include <iostream>
#include <vector>
#include <cmath>

struct Range {
  long start;
  long end;
};

std::vector<int> factorise(int n) {
  std::vector<int> out;
  for (int i = 1; i*i<=n; i++) {
    if (n % i == 0) {
      out.push_back(i);
      if (i != n/i) {
        out.push_back(n/i);
      }
    }
  }
  return out;
}

bool check_if_repeated(long n) {
  std::string nstring = std::to_string(n);
  int length = nstring.size();
  std::vector<int> divisors = factorise(length);
  for (int d: divisors) {
    if (d == length) continue;
    std::string pattern = nstring.substr(0,d);
    std::string repeated = "";

    for (int i = 0; i < length / d; i++) {
      repeated += pattern;
    }
    if (repeated == nstring) {
      return true;
    }
  }

  return false;

}

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
  long long b_out = 0;

  for (Range range: list) {
    long c = range.start;  
    while (c <= range.end) {
      if (check_if_repeated(c)) {
        b_out += c;
      }
      c++;
    }
  }
  std::cout << b_out << std::endl;
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
