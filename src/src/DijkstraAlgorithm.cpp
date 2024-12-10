#include "DijkstraAlgorithm.hpp"
#include "Edge.hpp"
#include <queue>
#include <unordered_map>
#include <functional>

struct Node {
    Vertex* vertex;
    double distance;

    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

std::vector<Vertex*> DijkstraAlgorithm::findPath(Vertex* start, Vertex* goal) {
    std::unordered_map<Vertex*, double> distances;
    std::unordered_map<Vertex*, Vertex*> previous;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> queue;

    distances[start] = 0.0;
    queue.push({start, 0.0});

    while (!queue.empty()) {
        Vertex* current = queue.top().vertex;
        double currentDist = queue.top().distance;
        queue.pop();

        if (current == goal) break;

        for (Edge* edge : current->edges) {
            Vertex* neighbor = edge->destination;
            double newDist = currentDist + edge->length;

            if (distances.find(neighbor) == distances.end() || newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                previous[neighbor] = current;
                queue.push({neighbor, newDist});
            }
        }
    }

    // Reconstruct the path
    std::vector<Vertex*> path;
    for (Vertex* at = goal; at != nullptr; at = previous[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    // Return empty path if start and goal are not connected
    if (path.front() != start) {
        path.clear();
    }

    return path;
}
