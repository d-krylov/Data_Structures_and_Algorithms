#include <iostream>
#include <stack>
#include <vector>

void DepthFirstSearch(const std::vector<std::vector<uint32_t>> &graph) {
  std::stack<uint32_t> stack;
  std::vector<uint32_t> visited(graph.size(), 0);
  stack.push(0);
  while (stack.empty() == false) {
    auto current_vertex = stack.top();
    stack.pop();
    if (visited[current_vertex] == 0) {
      std::cout << "Visit " << current_vertex << std::endl;
      visited[current_vertex] = 1;
      for (auto neighbour : graph[current_vertex]) {
        if (visited[neighbour] == 0) {
          stack.push(neighbour);
        }
      }
    }
  }
}

int main() {
  uint32_t n, m;
  uint32_t x, y;
  std::cin >> n >> m;
  std::vector<std::vector<uint32_t>> graph(n);
  for (uint32_t i = 0; i < m; i++) {
    std::cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  DepthFirstSearch(graph);
  return 0;
}