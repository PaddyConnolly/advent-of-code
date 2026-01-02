#include "lib/get.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

struct Point {
  long long x, y;
};

long long process(std::string &input) {
  std::istringstream stream(input);
  std::string line;
  std::vector<Point> points;

  while (std::getline(stream, line)) {
    if (line.empty())
      continue;

    std::stringstream lineStream(line);
    std::string token;
    Point p;
    if (std::getline(lineStream, token, ','))
      p.x = std::stoll(token);
    if (std::getline(lineStream, token, ','))
      p.y = std::stoll(token);
    points.push_back(p);
  }

  long long max_area = 0;
  int n = points.size();

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      long long width = std::abs(points[i].x - points[j].x) + 1;
      long long height = std::abs(points[i].y - points[j].y) + 1;
      long long area = width * height;
      max_area = std::max(max_area, area);
    }
  }

  std::cout << max_area << std::endl;
  return max_area;
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
