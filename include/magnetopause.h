#ifndef __MAGNETOPAUSE_H_INCLUDED__
#define __MAGNETOPAUSE_H_INCLUDED__
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <sstream>
#include <FL/gl.h>
#include "include/initbuffers.h"
#include "include/wiggle.h"
#include <tuple>

class Magnetopause {
	private:
		float rsm_;
	public:
		int nt_, np_, nVertex_, nColour_;
		GLfloat *vertex_, *colour_, *normal_;
		Magnetopause();
		Magnetopause(float);
		~Magnetopause();
		void populateBuffers();
		std::tuple<float,float> getCoordsxrho(float theta) ;
		void getCoordsxyz(
			float x0, float x1,
			float rho0, float rho1,
			float phi0, float phi1,
			float x[], float y[], float z[]
		);
		GLuint buffers_[3];
};
#endif
