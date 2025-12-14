#include "lib/get.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>

struct Range {
  long long start;
  long long end;
};

std::vector<Range> setRanges(const std::string& input) {
    std::vector<Range> ranges;
    std::istringstream iss(input);
    std::string line;

    while (std::getline(iss, line)) {
        if (line.empty()) break;
        long long s, e;
        char dash;
        std::istringstream linestream(line);
        linestream >> s >> dash >> e;
        ranges.push_back({s, e});
    }

    if (ranges.empty()) return ranges;

    std::sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b){
        return a.start < b.start;
    });

    std::vector<Range> merged;
    merged.push_back(ranges[0]);
    for (size_t i = 1; i < ranges.size(); i++) {
        Range& last = merged.back();
        if (ranges[i].start <= last.end + 1) {
            last.end = std::max(last.end, ranges[i].end);
        } else {
            merged.push_back(ranges[i]);
        }
    }

    return merged;
}

int binarySearch(const std::vector<Range>& a, long long V) {
    int L = 0;
    int R = (int)a.size() - 1;
    int ans = -1;

    while (L <= R) {
        int M = L + (R - L) / 2;

        if (a[M].start <= V) {
            ans = M;
            L = M + 1;
        } else {
            R = M - 1;
        }
    }
    return ans;
}

int process(std::string& input) {
  int count = 0;
  std::vector<Range> ranges = setRanges(input);
  size_t pos = input.find("\n\n");
  input = input.substr(pos+2);

  std::istringstream stream(input);
  std::string line;
  while (std::getline(stream, line)) {
    int idx = binarySearch(ranges, stoll(line));
    Range range = ranges[idx];
    if (range.end >= stoll(line)) {
      count++;
    }
  }

  std::cout << count << std::endl;

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
