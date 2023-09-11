#include "include/mainwindow.h"
#include "include/mercurysurface.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    MercurySurface mercury;

    return app.exec();
}