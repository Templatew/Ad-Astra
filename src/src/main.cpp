#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("Ad-Astra");

    MainWindow w;
    w.show();

    return app.exec();
}
