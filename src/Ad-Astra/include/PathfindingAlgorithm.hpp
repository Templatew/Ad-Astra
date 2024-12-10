#ifndef PATHFINDINGALGORITHM_HPP
#define PATHFINDINGALGORITHM_HPP

#include <vector>
#include "Vertex.hpp"

class PathfindingAlgorithm {
public:
    virtual ~PathfindingAlgorithm() {}
    virtual std::vector<Vertex*> findPath(Vertex* start, Vertex* goal) = 0;
};

#endif
