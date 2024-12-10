#include "EdgeItem.hpp"
#include "Vertex.hpp"
#include <QPen>
#include <qpainter.h>

EdgeItem::EdgeItem(Edge* edge)
    : edge(edge) {
    setPen(QPen(Qt::gray));
    setLine(QLineF(edge->source->x, edge->source->y, edge->destination->x, edge->destination->y));
}

Edge* EdgeItem::getEdge() const {
    return edge;
}

