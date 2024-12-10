#ifndef ASTARALGORITHM_HPP
#define ASTARALGORITHM_HPP

#include "PathfindingAlgorithm.hpp"

class AStarAlgorithm : public PathfindingAlgorithm {
    public:
        std::vector<Vertex*> findPath(Vertex* start, Vertex* goal) override;
};

#endif
