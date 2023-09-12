#include "include/flatarrow.h"

void flatArrow(float x, float y, float angle, float len, float wid, float *col) {
	/*this is a 2D arrow in the x,y plane*/
	
	/*length of the arrow head is 0.33*len, and stickis 0.67*len
	 * the width of the stick is 0.33* width of arrow head*/
	float st_x[2], st_y[2], hd_x[2], hd_y[2];
	st_x[0] = -0.5*len;
	st_x[1] = 0.17*len;
	hd_x[0] = 0.17*len;
	hd_x[1] = 0.5*len;	
	st_y[0] = -0.5*wid*0.33;
	st_y[1] = 0.5*wid*0.33;
	hd_y[0] = -0.5*wid;
	hd_y[1] = 0.5*wid;
	
	/*now calculate the x and y coords of the three triangles (1 head, 2 stick)*/
	float x0[3][3], y0[3][3];
	
	//head
	x0[0][0] = hd_x[0];
	x0[0][1] = hd_x[1];
	x0[0][2] = hd_x[0];
	y0[0][0] = hd_y[0];
	y0[0][1] = 0.0;
	y0[0][2] = hd_y[1];
	
	//stick
	x0[1][0] = st_x[0];
	x0[1][1] = st_x[1];
	x0[1][2] = st_x[0];
	y0[1][0] = st_y[0];
	y0[1][1] = st_y[1];
	y0[1][2] = st_y[1];
	
	x0[2][0] = st_x[0];
	x0[2][1] = st_x[1];
	x0[2][2] = st_x[1];
	y0[2][0] = st_y[0];
	y0[2][1] = st_y[0];
	y0[2][2] = st_y[1];
	
	/*now to rotate and translate*/
	float x1[3][3], y1[3][3];
	float rad = angle*M_PI/180.0;
	int i, j;
	for (i=0;i<3;i++) {
		for (j=0;j<3;j++) {
			x1[i][j] = x0[i][j]*cosf(rad) - y0[i][j]*sinf(rad) + x;
			y1[i][j] = x0[i][j]*sinf(rad) + y0[i][j]*cosf(rad) + y;
		}
	}
	
	/*now that bit is done, time to render*/
	glDisable(GL_LIGHTING);
	glBegin(GL_TRIANGLES);	
	glColor4f(col[0],col[1],col[2],col[3]);
	for (i=0;i<3;i++) {
		for (j=0;j<3;j++) {
			glVertex3f(x1[i][j],y1[i][j],0.01);
		}
	}
	glEnd();
	glEnable(GL_LIGHTING);	
}
