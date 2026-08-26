#include "include/mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    layout(nullptr),
    openGLWidget(nullptr),
    centralWidget(nullptr) {
    ui->setupUi(this);

    centralWidget = new QWidget(this);
    openGLWidget = new OpenGLWidget(centralWidget);

    layout = new QGridLayout(centralWidget);
    layout->addWidget(openGLWidget, 0, 0);

    QWidget *controls = new QWidget(centralWidget);
    controls->setObjectName("observerControls");
    controls->setAttribute(Qt::WA_StyledBackground, true);
    controls->setStyleSheet(
        "#observerControls { background: rgba(245, 245, 245, 220);"
        " border: 1px solid #777; border-radius: 6px; }"
        "#observerControls QPushButton { min-width: 30px; min-height: 26px; }"
    );
    QGridLayout *controlLayout = new QGridLayout(controls);
    controlLayout->setContentsMargins(6, 6, 6, 6);
    controlLayout->setSpacing(3);

    QPushButton *up = new QPushButton(QStringLiteral("\u2191"), controls);
    QPushButton *left = new QPushButton(QStringLiteral("\u2190"), controls);
    QPushButton *reset = new QPushButton(QStringLiteral("Reset"), controls);
    QPushButton *right = new QPushButton(QStringLiteral("\u2192"), controls);
    QPushButton *down = new QPushButton(QStringLiteral("\u2193"), controls);
    QPushButton *zoomIn = new QPushButton(QStringLiteral("+"), controls);
    QPushButton *zoomOut = new QPushButton(QStringLiteral("\u2212"), controls);

    up->setToolTip(QStringLiteral("Move observer north"));
    down->setToolTip(QStringLiteral("Move observer south"));
    left->setToolTip(QStringLiteral("Move observer toward earlier MLT"));
    right->setToolTip(QStringLiteral("Move observer toward later MLT"));
    zoomIn->setToolTip(QStringLiteral("Move observer closer"));
    zoomOut->setToolTip(QStringLiteral("Move observer farther away"));
    reset->setToolTip(QStringLiteral("Restore the original view"));

    controlLayout->addWidget(up, 0, 1);
    controlLayout->addWidget(left, 1, 0);
    controlLayout->addWidget(reset, 1, 1);
    controlLayout->addWidget(right, 1, 2);
    controlLayout->addWidget(down, 2, 1);
    controlLayout->addWidget(zoomOut, 3, 0);
    controlLayout->addWidget(zoomIn, 3, 2);

    connect(up, &QPushButton::clicked, openGLWidget, &OpenGLWidget::observerUp);
    connect(down, &QPushButton::clicked, openGLWidget, &OpenGLWidget::observerDown);
    connect(left, &QPushButton::clicked, openGLWidget, &OpenGLWidget::observerLeft);
    connect(right, &QPushButton::clicked, openGLWidget, &OpenGLWidget::observerRight);
    connect(zoomIn, &QPushButton::clicked, openGLWidget, &OpenGLWidget::observerZoomIn);
    connect(zoomOut, &QPushButton::clicked, openGLWidget, &OpenGLWidget::observerZoomOut);
    connect(reset, &QPushButton::clicked, openGLWidget, &OpenGLWidget::resetObserver);

    layout->addWidget(controls, 0, 0, Qt::AlignRight | Qt::AlignBottom);
    setCentralWidget(centralWidget);
    layout->setContentsMargins(0, 0, 8, 8);
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
