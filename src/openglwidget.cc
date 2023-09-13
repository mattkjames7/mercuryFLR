#include "include/openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    
{

	float spec[4]={0.5,0.5,0.5,1.0};
	float shine[1]={ 10.0};
	float amb[4]={0.2,0.2,0.2,1.0};
	float bright[4]={1.0,1.0,1.0,1.0};

	// /*Position Vectors*/
	// Vec *eyesph = new Vec[1]; //This is the position in spherical coords (sort of) of the camera "eye"
	// eyesph[0].x = 30.0;
	// eyesph[0].y = 15.0;
	// eyesph[0].z = 6.0;
	// Vec cent = {0.0,0.0,0.0}; //This is where the camera is looking
	// Vec up = {0.0,0.0,1.0}; //up vector for the camera

	GLfloat light_position[] = { 10.0, 0.0, 0.0, 1.0 };
    initGL(light_position,spec,shine,amb,bright);
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
    //initializeOpenGLFunctions();
    
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