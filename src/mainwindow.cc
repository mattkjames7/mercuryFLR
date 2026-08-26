#include "include/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    layout(nullptr),
    openGLWidget(nullptr),
    centralWidget(nullptr) {
    ui->setupUi(this);

    openGLWidget = new OpenGLWidget(this);

    layout = new QVBoxLayout;
    layout->addWidget(openGLWidget);

    centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    layout->setMargin(0);
    layout->setSpacing(0);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    // This is the slot for the pushButton's clicked signal.
    // You can place code here to handle the button click.
    ui->statusBar->showMessage("Button was clicked!");
}
