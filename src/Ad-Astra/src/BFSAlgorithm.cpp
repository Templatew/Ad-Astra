#include "BFSAlgorithm.hpp"
#include "Edge.hpp"
#include <algorithm>
#include <queue>
#include <unordered_map>

std::vector<Vertex*> BFSAlgorithm::findPath(Vertex* start, Vertex* goal) {
    std::queue<Vertex*> queue;
    std::unordered_map<Vertex*, Vertex*> cameFrom;
    std::unordered_map<Vertex*, bool> visited;

    queue.push(start);
    visited[start] = true;

    while (!queue.empty()) {
        Vertex* current = queue.front();
        queue.pop();

        if (current == goal) {
            // Reconstruct path
            std::vector<Vertex*> path;
            for (Vertex* at = goal; at != nullptr; at = cameFrom[at]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (Edge* edge : current->edges) {
            Vertex* neighbor = edge->destination;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                cameFrom[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }

    // No path found
    return std::vector<Vertex*>();
}
