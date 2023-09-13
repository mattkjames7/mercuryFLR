#include "include/openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    
{
    this->mercury = new MercurySurface;
    this->magnetopause = new Magnetopause;
    this->streamline = new Streamline;
    this->cutout = new CutOut;
    this->flr = new FLR;
    this->ocb = new OCB;
}

OpenGLWidget::~OpenGLWidget()
{
    // Cleanup, if necessary
    delete this->mercury;
    delete this->magnetopause;
    delete this->streamline;
    delete this->cutout;
    delete this->flr;
    delete this->ocb;
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // Setup your OpenGL context, shaders, buffers, etc.
}

void OpenGLWidget::paintGL()
{
    // Your OpenGL rendering code to draw the planet
}

void OpenGLWidget::resizeGL(int w, int h)
{
    // Adjust the viewport based on the widget's dimensions
    glViewport(0, 0, w, h);
}