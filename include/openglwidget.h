#ifndef __OPENGLWIDGET_H__
#define __OPENGLWIDGET_H__

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "include/mercurysurface.h"
#include "include/magnetopause.h"
#include "include/streamline.h"
#include "include/cutout.h"
#include "include/flr.h"
#include "include/ocb.h"
#include "include/initgl.h"
#include "include/vec.h"
#include "src/legacy/ExampleTraces.h"

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

    public:
        OpenGLWidget(QWidget *parent = nullptr);
        ~OpenGLWidget();

    protected:
        void initializeGL() override; 
        void paintGL() override;       
        void resizeGL(int w, int h) override; 

        MercurySurface *mercury;
        Magnetopause *magnetopause;
        Streamline *streamline;
        CutOut *cutout;
        FLR *flr;
        OCB *ocb;
        ExampleTraces *exampleTraces;
};

#endif
