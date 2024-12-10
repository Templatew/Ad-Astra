#include "VertexItem.hpp"
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <qpainter.h>

VertexItem::VertexItem(Vertex* vertex, double size) : QGraphicsEllipseItem(vertex->x - size / 2, vertex->y - size / 2, size, size), vertex(vertex), state(Normal) {
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    updateAppearance();
}

Vertex* VertexItem::getVertex() const {
    return vertex;
}

void VertexItem::setState(VertexState newState) {
    state = newState;
    updateAppearance();
}

VertexItem::VertexState VertexItem::getState() const {
    return state;
}

void VertexItem::updateAppearance() {
    switch (state) {
    case Normal:
        setBrush(Qt::white);
        setZValue(2);
        setPen(Qt::NoPen);
        break;
    case Hovered:
        setBrush(Qt::yellow);
        setPen(QPen(Qt::yellow, 2));
        break;
    case Start:
        setBrush(QColor(0x00DE64));
        setPen(QPen(QColor(0x00DE64), 2));
        setZValue(30);
        break;
    case End:
        setBrush(QColor(0x880044));
        setPen(QPen(QColor(0x880044), 2));
        setZValue(30);
        break;
    case Path:
        setBrush(QColor(0xF72585));
        setPen(QPen(QColor(0xF72585), 2));
        setZValue(30);
        break;
        // Temp 0xFFD6E0 Mimi Pink for explored
    }
}

void VertexItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    if (state == Normal) {
        setState(Hovered);
    }
    QGraphicsEllipseItem::hoverEnterEvent(event);
}

void VertexItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    if (state == Hovered) {
        setState(Normal);
    }
    QGraphicsEllipseItem::hoverLeaveEvent(event);
}

void VertexItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    emit vertexClicked(vertex);
    QGraphicsEllipseItem::mousePressEvent(event);
}

void VertexItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());

    if (lod < 1.2) {
        // Skip painting when the level of detail is too low
        return;
    }

    // Proceed with normal painting
    QGraphicsEllipseItem::paint(painter, option, widget);
}

