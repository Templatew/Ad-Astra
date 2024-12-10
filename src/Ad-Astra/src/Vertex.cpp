#include "Vertex.hpp"
#include <cmath>

#define EARTH_RADIUS 6371000.0

Vertex::Vertex(int id, double longitude, double latitude)
    : id(id), longitude(longitude), latitude(latitude) {
    
    double lonRad = longitude * M_PI / 180.0;
    double latRad = latitude * M_PI / 180.0;

    x = EARTH_RADIUS * lonRad;
    y = EARTH_RADIUS * log(tan(M_PI / 4.0 + latRad / 2.0));
}
