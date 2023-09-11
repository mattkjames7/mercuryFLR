#include "include/mainwindow.h"
#include "include/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    // This is the slot for the pushButton's clicked signal.
    // You can place code here to handle the button click.
    ui->statusBar->showMessage("Button was clicked!");
}