#include "include/initgl.h"

bool initGL(float *light_position, float *spec, float *shine, float *amb, float *bright){

    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
  	glFrustum (-1.0, 1.0, -0.75, 0.75, 1.5, 1000.0); //this should set it up correctly for a 4:3 aspect ratio
  	
    //Initialize Modelview Matrix
    glEnable(GL_DEPTH_TEST);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 1.f, 1.f, 1.f, 1.f ); //clear the screen white

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR ){
        std::cout << "Error initializing OpenGL!" << std::endl;
        return false;
    }
    glDisable(GL_CULL_FACE);
    
    glShadeModel (GL_SMOOTH);
	
   	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
   	glEnable(GL_LIGHT0); 
   	glEnable(GL_COLOR_MATERIAL);	//need this to get the colours working using the arrays rather than glMaterialfv
    	
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	
	glEnable(GL_POLYGON_SMOOTH);
	//glBlendFunc(GL_SRC_ALPHA_SATURATE,GL_ZERO);
	glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
	// QOpenGLWidget composites its framebuffer into the Qt window. Preserve an
	// opaque destination alpha while blending scene RGB, otherwise translucent
	// geometry makes the entire widget reveal windows behind it.
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
	
    return true;
}
