#include "include/wiggle.h"

void wiggleCart(
	float rss, float x, float y, float z, float A, 
	float *dx, float *dy, float *dz
) {
	float rho, theta, phi;
	rho = sqrtf(y*y + z*z);
	phi = atan2f(y,z);
	theta = atan2f(rho,x);
	wiggle(rss,theta,phi,A,dx,dy,dz);
	
}


void wiggle(
	float rss, float theta, float phi, float A,
	float *dx, float *dy, float *dz
) {
	float rho, r, x, y, z;
	float mlt;
	float mltR[2] = {13.0,21.0};
	float f = 0.5;
	float dR;
	float mu = M_PI/2.0;
	float sig = M_PI/8.0;
	r = rss*sqrtf(2.0/(1.0+cosf(theta)));
	x = r*cosf(theta);
	rho = r*sinf(theta);
	y = rho*sinf(phi);
	z = rho*cosf(phi);

	mlt = 12.0*theta/M_PI + 12.0;
	if ((mlt >= mltR[0]) && (mlt <= mltR[1])) {
		dR = A*sinf(2*M_PI*f*(mlt-mltR[0]))*(0.5*cosf(2*M_PI*(mlt-mltR[0])*f/4.0 + M_PI) + 0.5);
	} else {
		dR = 0.0;
	}
	dR = dR*expf(-(powf(phi-mu,2.0))/(2*sig*sig));
	
	float nR, nrho, nx, ny, nz;
	nR = r + dR;
	nrho = nR*sinf(theta);
	nx = nR*cosf(theta);
	ny = nrho*sinf(phi);
	nz = nrho*cosf(phi);
	dx[0] = nx - x;
	dy[0] = ny - y;
	dz[0] = nz - z;
}
