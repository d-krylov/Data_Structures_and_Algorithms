#include <iostream>
#include <queue>
#include <vector>

void BreadthFirstSearch(const std::vector<std::vector<uint32_t>> &graph) {
  std::queue<uint32_t> queue;
  queue.push(0);
  std::vector<uint32_t> visited(graph.size(), 0);
  visited[0] = 1;
  while (queue.empty() == false) {
    auto current_vertex = queue.front();
    queue.pop();
    std::cout << "Visit " << current_vertex << std::endl;
    for (auto neighbour : graph[current_vertex]) {
      if (visited[neighbour] == 0) {
        visited[neighbour] = 1;
        queue.push(neighbour);
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
  BreadthFirstSearch(graph);
}