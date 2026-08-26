#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "include/openglwidget.h"
#include <QGridLayout>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_pushButton_clicked();

    private:
        Ui::MainWindow *ui;
        QGridLayout *layout;
        OpenGLWidget *openGLWidget;
        QWidget *centralWidget;
};

#endif // MAINWINDOW_H
