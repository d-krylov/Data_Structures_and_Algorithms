#include <iostream>
#include <limits>
#include <queue>
#include <vector>

const int32_t INFINITY = std::numeric_limits<int32_t>::max();
using Edge = std::pair<uint32_t, uint32_t>;

void Dijkstra(const std::vector<std::vector<Edge>> &g,
              std::vector<uint32_t> &distances, std::vector<uint32_t> &parent) {
  distances.assign(g.size(), INFINITY);
  distances[0] = 0;
  std::vector<uint32_t> visit(g.size(), 0);
  distances[0] = 0;
  for (int32_t i = 0; i < g.size(); ++i) {
    int32_t v = -1;
    for (int32_t j = 0; j < g.size(); ++j)
      if ((visit[j] == 0) && (v == -1 || distances[j] < distances[v])) {
        v = j;
      }
    if (distances[v] == INFINITY) {
      break;
    }
    visit[v] = true;
    for (size_t j = 0; j < g[v].size(); ++j) {
      auto to = g[v][j].first;
      auto weight = g[v][j].second;
      if (distances[v] + weight < distances[to]) {
        distances[to] = distances[v] + weight;
        parent[to] = v;
      }
    }
  }
}

int main() {
  uint32_t n, m;
  uint32_t x, y, w;
  std::cin >> n >> m;
  std::vector<std::vector<Edge>> graph(n);
  for (uint32_t i = 0; i < m; i++) {
    std::cin >> x >> y >> w;
    graph[x].emplace_back(y, w);
    graph[y].emplace_back(x, w);
  }
  std::vector<uint32_t> distances;
  std::vector<uint32_t> parents(n);
  Dijkstra(graph, distances, parents);
  for (int32_t i = 0; i < distances.size(); i++) {
    std::cout << "Distance to " << i << " = " << distances[i] << std::endl;
  }
  return 0;
}