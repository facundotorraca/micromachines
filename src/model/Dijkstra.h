#ifndef MICROMACHINES_DIJKSTRA_H
#define MICROMACHINES_DIJKSTRA_H

#include <vector>
#include <cstdint>

#define NOT_EDGE 0
#define INF 999999

class Dijkstra {

    private:
        static size_t min_distance(std::vector<bool>& visited, std::vector<int32_t>& ans) {
                int min = INF; size_t min_index = 0;
                for (size_t j = 0; j < ans.size(); j++) {
                    if (!visited[j] && ans[j] <= min) {
                        min = ans[j];
                        min_index = j;
                    }
                }
                return min_index;
        }

    public:
        static void dijkstra(std::vector< std::vector<int32_t> >& graph, std::vector<int32_t>& ans, size_t src) {
            std::vector<bool> visited(graph.size());

            for (size_t i = 0; i < graph.size(); i++) {
                ans[i] = INF;
                visited.push_back(false);
            }

            ans[src] = 0; //Source distance is 0

            for (size_t i = 0; i < graph.size(); i++) {
                // Find shortest path for all vertices
                size_t min_idx = min_distance(visited, ans);

                visited[min_idx] = true;

                for (size_t j = 0; j < graph.size(); j++) {
                    if (!visited[j] && (graph[min_idx][j] != NOT_EDGE)) {
                        if ((ans[min_idx] + graph[min_idx][j]) < ans[j])
                            ans[j] = ans[min_idx] + graph[min_idx][j];
                    }
                }
            }
        }
};

#endif //MICROMACHINES_DIJKSTRA_H
