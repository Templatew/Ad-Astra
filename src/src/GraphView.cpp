#include "GraphView.hpp"
#include <QWheelEvent>
#include <QtMath>
#include <QOpenGLWidget>

GraphView::GraphView(QWidget* parent)
    : QGraphicsView(parent) {
    // setCursor(Qt::ArrowCursor);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    setInteractive(true);
    setStyleSheet("background-color: #232426;");
    //setViewport(new QOpenGLWidget());
    //setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
}

void GraphView::wheelEvent(QWheelEvent* event) {
    const double scaleFactor = 1.15;
    if (event->angleDelta().y() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        // Zoom out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}
