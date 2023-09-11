#include "include/initbuffers.h"

void initBuffers(GLuint *buffer, int nV, GLfloat *vertex, int nC, GLfloat *colour, int nN, GLfloat *normal){
	//generate buffers
	glGenBuffers(3,buffer);
	
	//bind the vertexes
	glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*nV,&vertex[0],GL_STATIC_DRAW);

	if (nN > 0) {
		//bind the normals
		glBindBuffer(GL_ARRAY_BUFFER,buffer[1]);
		glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*nN,&normal[0],GL_STATIC_DRAW);	
	}
	
	//bind the colours
	glBindBuffer(GL_ARRAY_BUFFER,buffer[2]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*nC,&colour[0],GL_STATIC_DRAW);			
}
