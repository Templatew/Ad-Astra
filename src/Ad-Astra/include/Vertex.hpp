#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>

class Edge; 

class Vertex {
public:
    int id;
    double longitude;
    double latitude;
    double x; 
    double y; 

    Vertex(int id, double longitude, double latitude);

    // Edges connected to this vertex
    std::vector<Edge*> edges;
};

#endif
