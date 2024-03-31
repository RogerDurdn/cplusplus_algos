#include <iostream>
#include <queue>
#include <set>
#include <tuple>
#include <unordered_map>
#include <vector>

int traverse(int node, std::unordered_map<int, std::vector<int>> graph,
             std::unordered_map<int, int> &values) {
  if (values.count(node))
    return values[node];
  int nodeVal = 0;
  for (auto const &n : graph[node]) {
    nodeVal = values.count(n) ? std::max(nodeVal, values[n])
                              : std::max(nodeVal, traverse(n, graph, values));
  }
  values[node] = nodeVal + 1;
  return values[node];
}

int semestersRequired(int numCourses,
                      std::vector<std::tuple<int, int>> prereqs) {
  std::unordered_map<int, std::vector<int>> graph;
  for (auto [l, r] : prereqs) {
    graph[l].push_back(r);
  }

  std::unordered_map<int, int> values;
  for (int node = 0; node < numCourses; node++) {
    if (graph[node].empty())
      values[node] = 1;
  }

  int maxSemesters = 1;
  for (int node = 0; node < numCourses; node++) {
    if (!values.count(node))
      maxSemesters = std::max(maxSemesters, traverse(node, graph, values));
  }
  return maxSemesters;
}

void searchIsland(std::vector<std::vector<char>> grid, int r, int c,
                  std::queue<std::tuple<int, int, int>> &island,
                  std::set<std::tuple<int, int>> &visited) {
  bool allowedR = 0 <= r && r < grid.size();
  bool allowedC = 0 <= c && c < grid[0].size();
  if (!allowedC || !allowedR)
    return;
  if (visited.count({r, c}))
    return;
  if (grid[r][c] == 'W')
    return;
  island.push({r, c, 0});
  visited.insert({r, c});
  searchIsland(grid, r - 1, c, island, visited);
  searchIsland(grid, r + 1, c, island, visited);
  searchIsland(grid, r, c - 1, island, visited);
  searchIsland(grid, r, c + 1, island, visited);
}

int bestBridge(std::vector<std::vector<char>> grid) {
  std::queue<std::tuple<int, int, int>> island;
  std::set<std::tuple<int, int>> visitedIsland;
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[0].size(); ++j) {
      if (grid[i][j] == 'L') {
        searchIsland(grid, i, j, island, visitedIsland);
        goto outherloop;
      }
    }
  }
outherloop:
  std::vector<std::tuple<int, int>> delta = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  int minBridge = INT_MAX;
  std::set<std::tuple<int, int>> visited;
  while (!island.empty()) {
    auto [r, c, v] = island.front();
    island.pop();
    visited.insert({r, c});
    if (v != 0) {
      if (grid[r][c] == 'L') {
        minBridge = std::min(minBridge, v);
      }
    }
    for (auto [nR, nC] : delta) {
      if (!visited.count({r + nR, c + nC}))
        island.push({r + nR, c + nC, v + 1});
    }
  }
  return minBridge;
}

int main() {

  /* std::vector<std::vector<char>> grid{ */
  /*         {'W', 'W', 'W', 'L', 'L'}, */
  /*         {'L', 'L', 'W', 'W', 'L'}, */
  /*         {'L', 'L', 'L', 'W', 'L'}, */
  /*         {'W', 'L', 'W', 'W', 'W'}, */
  /*         {'W', 'W', 'W', 'W', 'W'}, */
  /*         {'W', 'W', 'W', 'W', 'W'} */
  /* }; */
  /* auto r = bestBridge(grid); // -> 1 */
  std::cout << "hello world" << std::endl;
}

// 0 - [5]
// 1 - [2]
// 2 - [4]
// 3 - [5]
// 4 - []
// 5 - []
