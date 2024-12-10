#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "GraphScene.hpp"
#include "GraphView.hpp"
#include "Graph.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onVertexSelected(Vertex* vertex);
    void selectAlgorithm();
    void enterVertexIDs();
    void resetSelection();
    void toggleAntialiasing(bool enabled);

private:
    GraphView* graphicsView;
    GraphScene* graphScene;
    Graph graph;

    Vertex* startVertex;
    Vertex* endVertex;

    enum AlgorithmType {Dijkstra, AStar, BFS};

    AlgorithmType currentAlgorithm;

    enum SelectionState { SelectingStart, SelectingEnd };
    SelectionState selectionState;

    void setupUi();
    void loadGraph();
};

#endif 
