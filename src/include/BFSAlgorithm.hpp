#ifndef BFSALGORITHM_HPP
#define BFSALGORITHM_HPP

#include "PathfindingAlgorithm.hpp"

class BFSAlgorithm : public PathfindingAlgorithm {
public:
    std::vector<Vertex*> findPath(Vertex* start, Vertex* goal) override;
};

#endif
