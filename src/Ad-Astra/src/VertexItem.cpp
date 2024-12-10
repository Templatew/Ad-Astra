#include "VertexItem.hpp"
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <qpainter.h>

VertexItem::VertexItem(Vertex* vertex, double size) : QGraphicsEllipseItem(vertex->x - size / 2, vertex->y - size / 2, size, size), vertex(vertex), state(Normal) {
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    setPen(Qt::NoPen); // Remove outline
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
        break;
    case Hovered:
        setBrush(Qt::yellow);
        break;
    case Start:
        setBrush(QColor(0x00DE64));
        setZValue(30);
        break;
    case End:
        setBrush(QColor(0x880044));
        setZValue(30);
        break;
    case Path:
        setBrush(QColor(0xF72585));
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

    if (lod < 1.5) {
        // Skip painting when the level of detail is too low
        return;
    }

    // Proceed with normal painting
    QGraphicsEllipseItem::paint(painter, option, widget);
}

