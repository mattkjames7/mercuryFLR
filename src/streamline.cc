#include "include/streamline.h"

Streamline::Streamline() {
	Streamline::populateStreamline();
}

void Streamline::populateStreamline() {
	
	/*start with a line which points along x, at some dy
	 * from X = 6 to X = 1.84*/
	float x0[105];
	float y0[105];
	float dx=0.04;
	float dy=0.5;
	int i;

	for (i=0;i<105;i++) {
		x0[i] = 6.0 - dx*i;
		y0[i] = dy;
	}
	
	/* the curved bit Rss = 1.84, theta 16-179 */
	float x1[164];
	float y1[164];
	float theta;
	float r;
	for (i=0;i<164;i++) { 
		theta = M_PI*(i+16.0)/180.0;
		r = 1.84*sqrtf(2.0/(1.0+cosf(theta)));
		x1[i] = r*cosf(theta);
		y1[i] = r*sinf(theta);
	}
	
	/*join them together*/
	this->n_ = 269;
	float xt[269];
	float yt[269];
	for (i=0;i<105;i++) {
		xt[i] = x0[i];
		yt[i] = y0[i];
	}
	for (i=0;i<164;i++) {
		xt[i+105] = x1[i];
		yt[i+105] = y1[i];
	}
	
	/*smooth them together from X = 2.24 - 1.84 (11 points) and theta =
	 * 16 - 27 using 11 point sliding window*/
	int i0, i1, j;
	float sumx, sumy;
	for (i=0;i<269;i++) {
		if (i < 94) {
			this->x_[i] = xt[i];
			this->y_[i] = yt[i];
		} else if (i > 115) {
			this->x_[i] = xt[i];
			this->y_[i] = yt[i];
		} else {
			i0 = i - 5;
			i1 = i + 5;
			sumx = 0.0;
			sumy = 0.0;
			for (j=i0;j<=i1;j++) {
				sumx += xt[j];
				sumy += yt[j];
			}
			this->x_[i] = sumx/11.0;
			this->y_[i] = sumy/11.0;
		}
	}
		
}
