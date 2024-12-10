#include "MainWindow.hpp"
#include "AStarAlgorithm.hpp"
#include "BFSAlgorithm.hpp"
#include "DijkstraAlgorithm.hpp"
#include "PathfindingAlgorithm.hpp"
#include <QMessageBox>
#include <QStatusBar>
#include <QMenuBar>
#include <QInputDialog>
#include <QDebug>
#include <QElapsedTimer>
#include <QDebug>
#include <QLocale>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      graphicsView(new GraphView(this)),
      graphScene(new GraphScene(this)),
      startVertex(nullptr), endVertex(nullptr),
      selectionState(SelectingStart),
      currentAlgorithm(Dijkstra) {

    setupUi();
    loadGraph();
}

MainWindow::~MainWindow() {
    // Destructor
}

void MainWindow::setupUi() {
    setCentralWidget(graphicsView);
    graphicsView->setScene(graphScene);

    connect(graphScene, &GraphScene::vertexSelected, this, &MainWindow::onVertexSelected);
    
    // Create menu actions
    QAction* selectAlgorithmAction = new QAction("Select Algorithm", this);
    QAction* enterVertexIDsAction = new QAction("Enter Vertex IDs", this);
    QAction* toggleAntialiasingAction = new QAction("Toggle Antialiasing", this);
    QAction* resetAction = new QAction("Reset", this);

    toggleAntialiasingAction->setCheckable(true);
    toggleAntialiasingAction->setChecked(true);

    connect(selectAlgorithmAction, &QAction::triggered, this, &MainWindow::selectAlgorithm);
    connect(enterVertexIDsAction, &QAction::triggered, this, &MainWindow::enterVertexIDs);
    connect(toggleAntialiasingAction, &QAction::toggled, this, &MainWindow::toggleAntialiasing);
    connect(resetAction, &QAction::triggered, this, &MainWindow::resetSelection);

    // Add actions to the menu
    QMenu* menu = menuBar()->addMenu("Options");
    menu->addAction(selectAlgorithmAction);
    menu->addAction(enterVertexIDsAction);
    menu->addAction(toggleAntialiasingAction);
    menu->addAction(resetAction);
}

void MainWindow::loadGraph() {
    bool success = graph.loadFromFile(":/map");
    if (!success) {
        QMessageBox::critical(this, "Error", "Failed to load graph data.");
        return;
    }
    graphScene->setGraph(&graph);
}

void MainWindow::toggleAntialiasing(bool enabled) {
    if (enabled) {
        graphicsView->setRenderHint(QPainter::Antialiasing, true);
        statusBar()->showMessage("Antialiasing enabled.");
    } else {
        graphicsView->setRenderHint(QPainter::Antialiasing, false);
        statusBar()->showMessage("Antialiasing disabled.");
    }

    // Force the view to update
    graphicsView->viewport()->update();
}

void MainWindow::selectAlgorithm() {
    QStringList algorithms = {"Dijkstra", "A*", "BFS"};
    bool ok;
    QString selectedAlgorithm = QInputDialog::getItem(this, "Select Algorithm", "Algorithm:", algorithms, 0, false, &ok);
    if (ok && !selectedAlgorithm.isEmpty()) {
        if (selectedAlgorithm == "Dijkstra") {
            currentAlgorithm = Dijkstra;
        } else if (selectedAlgorithm == "A*") {
            currentAlgorithm = AStar;
        } else if (selectedAlgorithm == "BFS") {
            currentAlgorithm = BFS;
        }
        statusBar()->showMessage("Selected Algorithm: " + selectedAlgorithm);
    }
}

void MainWindow::onVertexSelected(Vertex* vertex) {
    if (selectionState == SelectingStart) {
        // If a previous path exists, clear it
        graphScene->clearPathHighlight();
        startVertex = vertex;
        graphScene->setStartVertex(vertex);
        selectionState = SelectingEnd;
        statusBar()->showMessage("Start vertex selected. Please select the end vertex.");
    } 
    else if (selectionState == SelectingEnd) {
        endVertex = vertex;
        graphScene->setEndVertex(vertex);
        selectionState = SelectingStart;

        // Start pathfinding
        PathfindingAlgorithm* algorithm = nullptr;

        if (currentAlgorithm == Dijkstra) {
            algorithm = new DijkstraAlgorithm();
        } 
        else if (currentAlgorithm == AStar) {
            algorithm = new AStarAlgorithm();
        } 
        else if (currentAlgorithm == BFS) {
            algorithm = new BFSAlgorithm();
        }

        if (algorithm) {

            // Measure the time
            QElapsedTimer timer;
            timer.start();

            std::vector<Vertex*> path = algorithm->findPath(startVertex, endVertex);

            qint64 elapsedNanoseconds = timer.nsecsElapsed();
            double elapsedMicroseconds = elapsedNanoseconds / 1000.0;

            if (path.empty()) {
                statusBar()->showMessage("No path found.");
                qDebug() << "No path found.";
            } else {
                // Highlight the path
                graphScene->highlightPath(path);

                statusBar()->showMessage(QString("Path found in %1 us").arg(elapsedMicroseconds));

                // Output the time and path to the debug console
                qDebug() << "Path found in" << elapsedMicroseconds << "us.";
                qDebug() << "Path:";
                for (Vertex* v : path) {
                    qDebug() << "Vertex ID:" << v->id;
                }
            }
            delete algorithm;
        }
    }
}

void MainWindow::enterVertexIDs() {
    bool ok1, ok2;
    int startID = QInputDialog::getInt(this, "Enter Start Vertex ID", "Start Vertex ID:", 0, 0, 100000, 1, &ok1);
    int endID = QInputDialog::getInt(this, "Enter End Vertex ID", "End Vertex ID:", 0, 0, 100000, 1, &ok2);

    if (ok1 && ok2) {
        if (graph.vertices.count(startID) && graph.vertices.count(endID)) {
            startVertex = graph.vertices[startID];
            endVertex = graph.vertices[endID];

            graphScene->clearSelection();
            graphScene->setStartVertex(startVertex);
            selectionState = SelectingEnd;
            onVertexSelected(endVertex);

        } else {
            QMessageBox::warning(this, "Invalid IDs", "One or both vertex IDs are invalid.");
        }
    }
}

void MainWindow::resetSelection() {
    // Clear selections in the scene
    graphScene->clearSelection();

    // Reset start and end vertices in MainWindow
    startVertex = nullptr;
    endVertex = nullptr;

    // Reset selection state
    selectionState = SelectingStart;

    // Update status bar
    statusBar()->showMessage("Selections and path have been reset.");
}
