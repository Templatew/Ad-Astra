#include "Graph.hpp"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

Graph::Graph() {}

Graph::~Graph() {
    // Clean up vertices and edges
    for (auto& pair : vertices) {
        delete pair.second;
    }
    for (Edge* edge : edges) {
        delete edge;
    }
}

bool Graph::loadFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filename;
        return false;
    }

    QTextStream in(&file);
    bool readingVertices = false;
    bool readingEdges = false;

    while (!in.atEnd()) {
        QString line = in.readLine();

        // Skip comments and empty lines
        if (line.isEmpty() || line.startsWith('#')) {
            if (line.contains("Vertex List")) {
                readingVertices = true;
                readingEdges = false;
            } else if (line.contains("Edge List")) {
                readingVertices = false;
                readingEdges = true;
            }
            continue;
        }

        QStringList tokens = line.split(',');

        if (readingVertices) {
            if (tokens.at(0) != "V") continue;

            int id = tokens.at(1).toInt();
            double longitude = tokens.at(2).toDouble();
            double latitude = tokens.at(3).toDouble();

            Vertex* vertex = new Vertex(id, longitude, latitude);
            vertices[id] = vertex;
        } else if (readingEdges) {
            if (tokens.at(0) != "E") continue;

            int sourceId = tokens.at(1).toInt();
            int destId = tokens.at(2).toInt();
            double length = tokens.at(3).toDouble();
            QString name = tokens.at(4);

            Vertex* source = vertices[sourceId];
            Vertex* dest = vertices[destId];

            if (source && dest) {
                Edge* edge = new Edge(source, dest, length, name.toStdString());
                edges.push_back(edge);
                source->edges.push_back(edge);
            } else {
                qDebug() << "Invalid edge:" << sourceId << "->" << destId;
            }
        }
    }

    file.close();
    return true;
}

