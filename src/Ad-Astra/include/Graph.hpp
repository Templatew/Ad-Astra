#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <vector>
#include <string>
#include <QString>
#include "Vertex.hpp"
#include "Edge.hpp"

class Graph {
public:
    std::map<int, Vertex*> vertices;
    std::vector<Edge*> edges;

    Graph();
    ~Graph();

    bool loadFromFile(const QString& resourcePath);
};

#endif
