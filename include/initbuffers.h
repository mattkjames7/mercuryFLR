#ifndef __INITBUFFERS_H_INCLUDED__
#define __INITBUFFERS_H_INCLUDED__
#define GL_GLEXT_PROTOTYPES
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>

void initBuffers(GLuint *buffer, int nV, GLfloat *vertex, int nC, GLfloat *colour, int nN, GLfloat *normal);
#endif
