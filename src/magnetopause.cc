#include "include/magnetopause.h"

Magnetopause::Magnetopause() { 
	std::cout << "Creating Magnetopause Object" << std::endl;
	this->rsm_ = 1.42;
	this->populateBuffers();
} 

Magnetopause::Magnetopause(float rsm) { 
	std::cout << "Creating Magnetopause Object" << std::endl;
	this->rsm_ = rsm;
	this->populateBuffers();
} 

/*Destuctor will delete the arrays malloced earlier*/
Magnetopause::~Magnetopause() {
	std::cout << "Removing Magnetopause Object" << std::endl;
	delete [] this->vertex_;
	delete [] this->colour_;
	delete [] this->normal_;
}

std::tuple<float,float> Magnetopause::getCoordsxrho(float theta) {

	float r = this->rsm_*sqrt(2.0/(1.0 + cos(theta)));
	float x = r*cos(theta);
	float rho = r*sin(theta);

	return std::make_tuple(x,rho);
}

void Magnetopause::getCoordsxyz(
	float x0, float x1,
	float rho0, float rho1,
	float phi0, float phi1,
	float x[], float y[], float z[]
) {
	x[0] = x0;
	x[1] = x0;
	x[2] = x1;
	x[3] = x1;

	y[0] = -rho0*sin(phi0);
	y[1] = -rho0*sin(phi1);
	y[2] = -rho1*sin(phi1);
	y[3] = -rho1*sin(phi0);

	z[0] = rho0*cos(phi0);
	z[1] = rho0*cos(phi1);
	z[2] = rho1*cos(phi1);
	z[3] = rho1*cos(phi0);	
}

void Magnetopause::populateBuffers(){
	std::cout << "Populating Magnetopause Buffers" << std::endl;
	this->nt_ = 179;
	this->np_ = 270;
	this->nVertex_ = this->nt_*this->np_*3*4;
	this->nColour_ = this->nt_*this->np_*4*4;
	this->vertex_ = new GLfloat[this->nVertex_];
	this->colour_ = new GLfloat[this->nColour_];
	this->normal_ = new GLfloat[this->nVertex_];


	float dr, dx, dy, dz;
	int i, j, k, p = 0, pc = 0;
	float x[4],y[4],z[4];
	float r;
	float rho0, rho1;
	float x0, x1; 
	float Opacity, MaxOpacity = 0.75;
	float theta0, theta1, phi0, phi1;
	float deg2rad = M_PI*1.0/180.0;
	std::tuple<float,float> xrho;

	for (i=0;i<this->nt_;i++) {
		theta0 = float(i)*deg2rad;
		theta1 = float(i+1)*deg2rad;
		xrho = this->getCoordsxrho(theta0);
		x0 = std::get<0>(xrho);
		rho0 = std::get<1>(xrho);
		xrho = this->getCoordsxrho(theta1);
		x1 = std::get<0>(xrho);
		rho1 = std::get<1>(xrho);



		if (i == this->nt_-1) {
			rho1 = 0.0;
		}

		dr = x0-this->rsm_;
		
		if (dr >= -2.0) {
			Opacity = MaxOpacity;
		} else if ((dr < -2.0) & (dr >= -5.0)) {
			Opacity = MaxOpacity*(1.0 + (dr+2.0)/3.0);
		} else {
			Opacity = 0.0;
		} 

		for (j=0;j<this->np_;j++) {
			phi0 = float(j)*deg2rad;
			phi1 = float(j+1)*deg2rad;
			
			this->getCoordsxyz(x0,x1,rho0,rho1,phi0,phi1,x,y,z);

			
			for (k=0;k<4;k++){
				wiggleCart(this->rsm_,x[k],y[k],z[k],0.2,&dx,&dy,&dz);
				r = sqrt(pow(x[k],2.0) + pow(y[k],2.0) + pow(z[k],2.0));

				this->vertex_[p+k*3] = x[k]+dx;
				this->vertex_[p+k*3+1] = y[k]+dy;
				this->vertex_[p+k*3+2] = z[k]+dz;

				this->normal_[p+k*3] = -(2.0*x[k] + (pow(x[k],2.0))/r + r);
				this->normal_[p+k*3+1] = -(2.0*y[k] + x[k]*y[k]/r);
				this->normal_[p+k*3+2] = -(2.0*z[k] + x[k]*z[k]/r);

				this->colour_[pc+k*4] = 1.0;
				this->colour_[pc+k*4+1] = 0.0;
				this->colour_[pc+k*4+2] = 0.0;			
				this->colour_[pc+k*4+3] = Opacity;
			}	
			
			p+=12;
			pc+=16;
		}
	}	


	initBuffers(
		this->buffers_,
		this->nVertex_,
		this->vertex_,
		this->nColour_,
		this->colour_,
		0,
		this->normal_
	);
}

