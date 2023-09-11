#ifndef __MERCURY_H_INCLUDED__
#define __MERCURY_H_INCLUDED__
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <FL/gl.h>
#include "include/initbuffers.h"
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QDataStream>
#include <iostream>
#include <vector>


class MercurySurface {
	private:
		std::vector<unsigned char> R_, G_, B_;
		void readBinary();
		void populateBuffers();
	public:
		GLfloat *vertex_, *colour_, *normal_;
		int w_, h_, nVertices_;
		MercurySurface();
		~MercurySurface();
		GLuint buffers_[3];
};
#endif
