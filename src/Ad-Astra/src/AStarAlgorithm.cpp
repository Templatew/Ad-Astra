#include "AStarAlgorithm.hpp"
#include "Edge.hpp"
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <cmath>

struct AStarNode {
    Vertex* vertex;
    double fScore;

    bool operator>(const AStarNode& other) const {
        return fScore > other.fScore;
    }
};

double heuristic(Vertex* a, Vertex* b) {
    // Use Euclidean distance as heuristic
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    return std::sqrt(dx * dx + dy * dy);
}

std::vector<Vertex*> AStarAlgorithm::findPath(Vertex* start, Vertex* goal) {
    std::unordered_map<Vertex*, double> gScore;
    std::unordered_map<Vertex*, double> fScore;
    std::unordered_map<Vertex*, Vertex*> cameFrom;
    std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> openSet;

    gScore[start] = 0.0;
    fScore[start] = heuristic(start, goal);
    openSet.push({start, fScore[start]});

    while (!openSet.empty()) {
        Vertex* current = openSet.top().vertex;
        openSet.pop();

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
            double tentativeGScore = gScore[current] + edge->length;

            if (gScore.find(neighbor) == gScore.end() || tentativeGScore < gScore[neighbor]) {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentativeGScore;
                fScore[neighbor] = gScore[neighbor] + heuristic(neighbor, goal);
                openSet.push({neighbor, fScore[neighbor]});
            }
        }
    }

    // No path found
    return std::vector<Vertex*>();
}
