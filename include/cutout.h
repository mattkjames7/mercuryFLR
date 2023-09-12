#ifndef __CUTOUT_H__
#define __CUTOUT_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/initbuffers.h"
#include <FL/gl.h>
#include "include/wiggle.h"
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QDataStream>
#include <iostream>

class CutOut {
	private:
		float rsm_;
		float x_,y_,z_;
		
		void populateBuffer();
		float rFunc(float);
		void readMPFile();
		void coordCalcNose(float theta, float *x, float *rho);
		void getBuffVertNose(
			float x[], float rho[],
			float col[], float MaxOpacity, 
			float norms[], float cols[], float verts[]
		);
		void getBuffHorzNose(
			float x[], float rho[],
			float dx0, float dy0, float dx1, float dy1,
			float col[], float MaxOpacity, 
			float norms[], float cols[], float verts[]
		);
		void getBuffVertTri1(
			float x[], float rho[],
			float col[], float Opacity, 
			float norms[], float cols[], float verts[]
		);
		void getBuffVertTri2(
			float x[], float rho[],
			float col[], float Opacity, 
			float norms[], float cols[], float verts[]
		);
		void getBuffHorzTri1(
			float x[], float rho[],
			float dx0, float dy0, float dx1, float dy1,
			float col[], float MaxOpacity, 
			float norms[], float cols[], float verts[]
		);
		void getBuffHorzTri2(
			float x[], float rho[],
			float dx0, float dy0, float dx1, float dy1,
			float col[], float MaxOpacity, 
			float norms[], float cols[], float verts[]
		);

	public:
		float *mpx_, *mpr_;
		int nt_, np_, nVertex_, nColour_;
		GLfloat *vertex_, *colour_, *normal_;
		CutOut();
		~CutOut();
		GLuint buffers_[3];
};
#endif
