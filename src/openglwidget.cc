#include "include/openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      mercury(nullptr),
      magnetopause(nullptr),
      streamline(nullptr),
      cutout(nullptr),
      flr(nullptr),
      ocb(nullptr)
{
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

    float spec[4] = {0.5, 0.5, 0.5, 1.0};
    float shine[1] = {10.0};
    float amb[4] = {0.2, 0.2, 0.2, 1.0};
    float bright[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {10.0, 0.0, 0.0, 1.0};

    initGL(light_position, spec, shine, amb, bright);

    // These constructors upload OpenGL buffers, so they must run while the
    // QOpenGLWidget context is current.
    mercury = new MercurySurface;
    magnetopause = new Magnetopause;
    streamline = new Streamline;
    cutout = new CutOut;
    flr = new FLR;
    ocb = new OCB;
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
