#include "lib/get.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

struct Point {
  int x, y, z;
};

struct Edge {
  int a, b;
  long long dist;
};

struct Union {
  std::vector<int> parent, size;

  Union(int n) {
    parent = std::vector<int>(n);
    size = std::vector<int>(n, 1);
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  int find(int x) {
    if (parent[x] == x) {
      return x;
    } else {
      return parent[x] = find(parent[x]);
    }
  }

  bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y)
      return false;
    if (size[x] < size[y])
      std::swap(x, y);
    parent[y] = x;
    size[x] += size[y];
    return true;
  }
};

int process(std::string &input) {
  std::istringstream stream(input);
  std::string line;
  std::vector<Point> points;
  while (std::getline(stream, line)) {
    std::stringstream lineStream(line);
    std::string token;
    Point p;

    if (std::getline(lineStream, token, ','))
      p.x = std::stoi(token);
    if (std::getline(lineStream, token, ','))
      p.y = std::stoi(token);
    if (std::getline(lineStream, token, ','))
      p.z = std::stoi(token);

    points.push_back(p);
  }

  std::vector<Edge> edges;
  int n = points.size();
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      long long dx = points[i].x - points[j].x;
      long long dy = points[i].y - points[j].y;
      long long dz = points[i].z - points[j].z;

      long long dist2 = dx * dx + dy * dy + dz * dz;
      edges.push_back({i, j, dist2});
    }
  }
  std::sort(edges.begin(), edges.end(),
            [](const Edge &a, const Edge &b) { return a.dist < b.dist; });

  Union u(n);
  int components = n;
  int last_a = -1;
  int last_b = -1;

  for (Edge &e : edges) {
    if (u.unite(e.a, e.b)) {
      last_a = e.a;
      last_b = e.b;
      components--;
      if (components == 1)
        break;
    }
  }

  long long result = (long long)points[last_a].x * points[last_b].x;
  std::cout << result << std::endl;
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
