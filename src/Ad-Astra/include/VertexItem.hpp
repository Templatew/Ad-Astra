#ifndef VERTEXITEM_HPP
#define VERTEXITEM_HPP

#include <QObject>
#include <QGraphicsEllipseItem>
#include "Vertex.hpp"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class VertexItem : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    enum VertexState {
        Normal,
        Hovered,
        Start,
        End,
        Path
    };

    VertexItem(Vertex* vertex, double size = 3.0);

    Vertex* getVertex() const;

    void setState(VertexState state);
    VertexState getState() const;

    // Override the paint method
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

signals:
    void vertexClicked(Vertex* vertex);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    Vertex* vertex;
    VertexState state;

    void updateAppearance();
};

#endif
