#ifndef __WIGGLE_H__
#define __WIGGLE_H__
#include <cmath>

void wiggle(
	float rss, float theta, float phi, float A,
	float *dx, float *dy, float *dz
);

void wiggleCart(
	float rss, float x, float y, float z, float A, 
	float *dx, float *dy, float *dz
);
#endif
