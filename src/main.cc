#include "include/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    Q_INIT_RESOURCE(resources);



    return app.exec();
}