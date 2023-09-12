#include "include/mainwindow.h"
#include "include/mercurysurface.h"
#include "include/magnetopause.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    MercurySurface mercury;
    Magnetopause magnetopause;

    return app.exec();
}