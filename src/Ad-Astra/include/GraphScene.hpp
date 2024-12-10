#ifndef GRAPHSCENE_HPP
#define GRAPHSCENE_HPP

#include <QGraphicsScene>
#include <map>
#include "Graph.hpp"
#include "VertexItem.hpp"
#include "EdgeItem.hpp"

class GraphScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit GraphScene(QObject* parent = nullptr);

    void setGraph(Graph* graph);
    void setStartVertex(Vertex* vertex);
    void setEndVertex(Vertex* vertex);
    void clearSelection();
    void highlightPath(const std::vector<Vertex*>& path);
    void clearPathHighlight();

signals:
    void vertexSelected(Vertex* vertex);

private:
    Graph* graph;
    std::map<Vertex*, VertexItem*> vertexItems;
    std::map<Edge*, EdgeItem*> edgeItems;
    std::vector<QGraphicsItem*> highlightedItems;

    Vertex* startVertex;
    Vertex* endVertex;

    QGraphicsTextItem* startVertexLabel;
    QGraphicsTextItem* endVertexLabel;

    void drawGraph();
};

#endif
