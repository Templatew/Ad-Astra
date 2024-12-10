#ifndef EDGE_HPP
#define EDGE_HPP

#include <string>

class Vertex;

class Edge {
public:
    Vertex* source;
    Vertex* destination;
    double length;
    std::string name;

    Edge(Vertex* source, Vertex* destination, double length, const std::string& name);
};

#endif
