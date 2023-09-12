#include "include/mainwindow.h"
#include "include/mercurysurface.h"
#include "include/magnetopause.h"
#include "include/streamline.h"
#include "include/cutout.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    Q_INIT_RESOURCE(resources);

    MercurySurface mercury;
    Magnetopause magnetopause;
    Streamline streamline;
    CutOut cutout;

    return app.exec();
}