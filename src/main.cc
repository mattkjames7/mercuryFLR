#include "include/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Q_INIT_RESOURCE(resources);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
