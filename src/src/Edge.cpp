#include "Edge.hpp"

Edge::Edge(Vertex* source, Vertex* destination, double length, const std::string& name)
    : source(source), destination(destination), length(length), name(name) {}
