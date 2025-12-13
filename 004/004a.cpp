#include "lib/get.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int process(std::string & input) {
  std::istringstream stream(input);
  std::string line;
  std::vector<std::string> charGrid;

  while(std::getline(stream, line)) {
    if (!line.empty()) {
      charGrid.push_back(line);
    }
  }

  int rows = charGrid.size();
  int cols = charGrid[0].size();

  std::vector<std::vector<int>> counts(rows, std::vector<int>(cols, 0));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j< cols; ++j) {
      if (charGrid[i][j] == '@') {
        for (int di = -1; di <= 1; ++di) {
            for (int dj = -1; dj <= 1; ++dj) {
                if (di == 0 && dj == 0) continue; // Skip the center

                int ni = i + di;
                int nj = j + dj;

                // Check boundary conditions
                if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                    counts[ni][nj]++;
                }
            }
        }
      }
    }
  }
  int count = 0;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (charGrid[i][j] == '@' && counts[i][j] < 4) {
        count++;
      }
    }
  }

  std::cout << count << std::endl;
  return 1;
}

int main (int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << std::endl;
    std::cerr << "Example: " << argv[0] << std::endl;
    return 0;
  }
  
  std::string url = argv[1];
  std::string content;
  std::string session_cookie = argv[2];

  if (get(url, session_cookie, content) != "Error") {
    process(content);
  } else {
    std::cerr << "Failed to fetch URL" << std::endl;
    return 0;
  }
  return 1;
}
