#ifndef __INITGL_H_INCLUDED__
#define __INITGL_H_INCLUDED__
#define GL_GLEXT_PROTOTYPES
#include <stdio.h>
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <iostream>

bool initgl(float *light_position, float *spec, float *shine, float *amb, float *bright);
#endif
