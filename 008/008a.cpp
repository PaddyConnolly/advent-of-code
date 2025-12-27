#include "lib/get.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <unordered_map>
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
  int to_connect = 1000;
  int attempts = 0;

  for (Edge &e : edges) {
    u.unite(e.a, e.b);
    attempts++;
    if (attempts == to_connect) {
      break;
    }
  }

  std::unordered_set<int> unique_roots;
  for (int i = 0; i < n; i++)
    unique_roots.insert(u.find(i));

  std::vector<long long> sizes;
  for (int root : unique_roots)
    sizes.push_back(u.size[root]);

  std::sort(sizes.begin(), sizes.end(), std::greater<long long>());

  while (sizes.size() < 3)
    sizes.push_back(1);

  long long result = sizes[0] * sizes[1] * sizes[2];
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
