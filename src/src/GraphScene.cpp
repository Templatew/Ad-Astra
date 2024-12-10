#include "GraphScene.hpp"
#include "EdgeItem.hpp"
#include <QGraphicsSceneMouseEvent>

GraphScene::GraphScene(QObject* parent) : QGraphicsScene(parent), graph(nullptr), startVertex(nullptr), endVertex(nullptr), startVertexLabel(nullptr), endVertexLabel(nullptr) {
}

void GraphScene::setGraph(Graph* graph) {
    this->graph = graph;
    drawGraph();
}

void GraphScene::drawGraph() {
    if (!graph) return;

    // Clear existing items
    clear();
    vertexItems.clear();
    edgeItems.clear();

    // Determine scaling factors
    double minX = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();

    for (const auto& pair : graph->vertices) {
        Vertex* v = pair.second;
        minX = std::min(minX, v->x);
        maxX = std::max(maxX, v->x);
        minY = std::min(minY, v->y);
        maxY = std::max(maxY, v->y);
    }

    double xRange = maxX - minX;
    double yRange = maxY - minY;

    // Scaling factors
    double sceneWidth = 2000.0;
    double sceneHeight = 2000.0;

    double scaleX = sceneWidth / xRange;
    double scaleY = sceneHeight / yRange;
    double scale = std::min(scaleX, scaleY);

    double offsetX = (sceneWidth - scale * xRange) / 2.0;
    double offsetY = (sceneHeight - scale * yRange) / 2.0;

    // Adjust vertices positions
    for (const auto& pair : graph->vertices) {
        Vertex* v = pair.second;

        double x = offsetX + (v->x - minX) * scale;
        double y = offsetY + (maxY - v->y) * scale; // Invert y-axis

        // Store adjusted coordinates
        v->x = x;
        v->y = y;

        VertexItem* vertexItem = new VertexItem(v);
        addItem(vertexItem);
        vertexItems[v] = vertexItem;

        connect(vertexItem, &VertexItem::vertexClicked, this, &GraphScene::vertexSelected);
    }

    // Draw edges
    for (Edge* e : graph->edges) {
        EdgeItem* edgeItem = new EdgeItem(e);
        addItem(edgeItem);
        edgeItem->setZValue(1);
        edgeItems[e] = edgeItem; // Store the mapping from Edge* to EdgeItem*
    }
}

void GraphScene::setStartVertex(Vertex* vertex) {

    // Reset Selection
    if (startVertex && vertexItems.count(startVertex)) {
        if (startVertex != vertex) {
            vertexItems[startVertex]->setState(VertexItem::Normal);
            vertexItems[endVertex]->setState(VertexItem::Normal);
        }
    }

    // Set new start vertex
    startVertex = vertex;
    if (vertexItems.count(vertex)) {
        vertexItems[vertex]->setState(VertexItem::Start);
    }
}

void GraphScene::setEndVertex(Vertex* vertex) {

    // Set new end vertex
    endVertex = vertex;
    if (vertexItems.count(vertex)) {
        vertexItems[vertex]->setState(VertexItem::End);
    }
}

void GraphScene::clearSelection() {

    // Reset start vertex
    if (startVertex && vertexItems.count(startVertex)) {
        vertexItems[startVertex]->setState(VertexItem::Normal);
    }
    startVertex = nullptr;

    // Reset end vertex
    if (endVertex && vertexItems.count(endVertex)) {
        vertexItems[endVertex]->setState(VertexItem::Normal);
    }
    endVertex = nullptr;

    // Clear path highlights
    clearPathHighlight();
}

void GraphScene::highlightPath(const std::vector<Vertex*>& path) {
    clearPathHighlight(); // Clear any existing path highlighting

    for (size_t i = 0; i < path.size() - 1; ++i) {
        Vertex* u = path[i];
        Vertex* v = path[i + 1];

        // Find the edge between u and v
        Edge* edge = nullptr;
        for (Edge* e : u->edges) {
            if (e->destination == v) {
                edge = e;
                break;
            }
        }
        if (edge) {
            EdgeItem* edgeItem = edgeItems[edge];
            if (edgeItem) {
                edgeItem->setPen(QPen(QColor(0xF72585), 3));
                highlightedItems.push_back(edgeItem);
                edgeItem->setZValue(10);
            }
        }

        // Highlight the vertices if they are not start or end vertices
        VertexItem* vertexItemU = vertexItems[u];
        if (vertexItemU && u != startVertex && u != endVertex) {
            vertexItemU->setState(VertexItem::Path);
            highlightedItems.push_back(vertexItemU);
        }
        VertexItem* vertexItemV = vertexItems[v];
        if (vertexItemV && v != startVertex && v != endVertex) {
            vertexItemV->setState(VertexItem::Path);
            highlightedItems.push_back(vertexItemV);
        }
    }
}


void GraphScene::clearPathHighlight() {
    // Reset the appearance of highlighted items
    for (QGraphicsItem* item : highlightedItems) {
        EdgeItem* edgeItem = dynamic_cast<EdgeItem*>(item);
        if (edgeItem) {
            edgeItem->setPen(QPen(Qt::gray));
            edgeItem->setZValue(1);
        }
        VertexItem* vertexItem = dynamic_cast<VertexItem*>(item);
        if (vertexItem) {
            if (vertexItem->getState() == VertexItem::Path) {
                vertexItem->setState(VertexItem::Normal);
            }
        }
    }
    highlightedItems.clear();
}

