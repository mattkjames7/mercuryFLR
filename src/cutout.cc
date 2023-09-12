#include "include/cutout.h"

CutOut::CutOut() {
	this->rsm_ = 1.42;
	this->readMPFile();
	this->populateBuffer();
}

CutOut::~CutOut() {
	delete [] this->mpx_;
	delete [] this->mpr_;
	delete [] this->vertex_;
	delete [] this->normal_;
	delete [] this->colour_;
}

float CutOut::rFunc(float theta) {
	return this->rsm_*sqrt(2.0/(1.0+cos(theta*M_PI/180.0)));
} 

void CutOut::coordCalcNose(float theta, float *x, float *rho) {
	float r[2];
	r[0] = this->rFunc(theta);
	r[1] = this->rFunc(theta+1);
	
	x[0] = r[0]*cos(theta*M_PI/180.0);
	rho[0] = r[0]*sin(theta*M_PI/180.0);
	x[1] = r[1]*cos((theta+1)*M_PI/180.0);
	rho[1] = r[1]*sin((theta+1)*M_PI/180.0);
	
}

void CutOut::readMPFile() {

	this->mpx_ = new float[643];
	this->mpr_ = new float[643];

	std::cout << "Reading Magnetopause Cutout File" << std::endl;

	QFile file(":/data/kt17mp.bin");
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "Failed to open the file!";
		return;
	}	
		
	QDataStream stream(&file);
	stream.setByteOrder(QDataStream::LittleEndian);

	int i;
	for (i=0;i<643;i++) {
		stream >> this->mpx_[i];
	} 
	for (i=0;i<643;i++) {
		stream >> this->mpr_[i];
	} 

	file.close();
}

void CutOut::getBuffVertNose(
	float x[], float rho[],
	float col[], float MaxOpacity, 
	float norms[], float cols[], float verts[]
) {

	int j;
	for (j=0;j<9;j++) {
		if (j % 3 == 1) {	
			norms[j] = 1.0;
		} else {
			norms[j] = 0.0;
		}
		verts[j] = 0.0;
	}
	verts[3] = x[0];
	verts[5] = rho[0];
	verts[6] = x[1];
	verts[8] = rho[1];

	int dj;
	for (j=0;j<12;j++) {
		dj = j % 4;
		if (dj == 3) {
			cols[j] = MaxOpacity;
		} else {
			cols[j] = col[dj]; 
		}
	}
} 

void CutOut::getBuffHorzNose(
	float x[], float rho[],
	float dx0, float dy0, float dx1, float dy1,
	float col[], float MaxOpacity, 
	float norms[], float cols[], float verts[]
) {

	int j;
	for (j=0;j<9;j++) {
		if (j % 3 == 2) {	
			norms[j] = 1.0;
		} else {
			norms[j] = 0.0;
		}
		verts[j] = 0.0;
	}
	verts[3] = x[0] + dx0;
	verts[4] = rho[0] + dy0;
	verts[6] = x[1] + dx1;
	verts[7] = rho[1] + dy1;

	int dj;
	for (j=0;j<12;j++) {
		dj = j % 4;
		if (dj == 3) {
			cols[j] = MaxOpacity;
		} else {
			cols[j] = col[dj]; 
		}
	}
} 


void CutOut::getBuffVertTri1(
	float x[], float rho[],
	float col[], float Opacity, 
	float norms[], float cols[], float verts[]
) {

	int j;
	for (j=0;j<9;j++) {
		if (j % 3 == 1) {	
			norms[j] = 1.0;
		} else {
			norms[j] = 0.0;
		}
		verts[j] = 0.0;
	}
	verts[0] = x[0];
	verts[3] = x[0];
	verts[5] = rho[0];
	verts[6] = x[1];
	verts[8] = rho[1];

	int dj;
	for (j=0;j<12;j++) {
		dj = j % 4;
		if (dj == 3) {
			cols[j] = Opacity;
		} else {
			cols[j] = col[dj]; 
		}
	}
} 


void CutOut::getBuffVertTri2(
	float x[], float rho[],
	float col[], float Opacity, 
	float norms[], float cols[], float verts[]
) {

	int j;
	for (j=0;j<9;j++) {
		if (j % 3 == 1) {	
			norms[j] = 1.0;
		} else {
			norms[j] = 0.0;
		}
		verts[j] = 0.0;
	}
	verts[0] = x[0];
	verts[3] = x[1];
	verts[5] = rho[1];
	verts[6] = x[1];
	
	int dj;
	for (j=0;j<12;j++) {
		dj = j % 4;
		if (dj == 3) {
			cols[j] = Opacity;
		} else {
			cols[j] = col[dj]; 
		}
	}
} 



void CutOut::getBuffHorzTri1(
	float x[], float rho[],
	float dx0, float dy0, float dx1, float dy1,
	float col[], float MaxOpacity, 
	float norms[], float cols[], float verts[]
) {

	int j;
	for (j=0;j<9;j++) {
		if (j % 3 == 2) {	
			norms[j] = 1.0;
		} else {
			norms[j] = 0.0;
		}
		verts[j] = 0.0;
	}
	verts[0] = x[0] + dx0;
	verts[3] = x[0] + dx0;
	verts[4] = rho[0] + dy0;
	verts[6] = x[1] + dx1;
	verts[7] = rho[1] + dy1;

	int dj;
	for (j=0;j<12;j++) {
		dj = j % 4;
		if (dj == 3) {
			cols[j] = MaxOpacity;
		} else {
			cols[j] = col[dj]; 
		}
	}
} 



void CutOut::getBuffHorzTri2(
	float x[], float rho[],
	float dx0, float dy0, float dx1, float dy1,
	float col[], float MaxOpacity, 
	float norms[], float cols[], float verts[]
) {

	int j;
	for (j=0;j<9;j++) {
		if (j % 3 == 2) {	
			norms[j] = 1.0;
		} else {
			norms[j] = 0.0;
		}
		verts[j] = 0.0;
	}
	verts[0] = x[0] + dx0;
	verts[3] = x[1] + dx1;
	verts[4] = rho[1] + dy1;
	verts[6] = x[1] + dx1;
	
	int dj;
	for (j=0;j<12;j++) {
		dj = j % 4;
		if (dj == 3) {
			cols[j] = MaxOpacity;
		} else {
			cols[j] = col[dj]; 
		}
	}
} 

void CutOut::populateBuffer() {
	
	/*firstly we need to move around in theta to create  triangles
	 * which have two vertices on the MP and one on the centre of the 
	 * planet*/
	int nTheta = 90; //90 triangles
	
	/*Then use evenly space quads (two triangles) from the centre of the
	 * planet until the end of the cutout*/
	int nX = 500; //100 triangles from X=0 to X=-5.0 
	
	float col[3] = {1.0,0.5,0.0};
	this->nVertex_ = (2*(nX*2+nTheta))*3*3; //number triangles * number of dimensions *number of vertices
	this->nColour_ = (2*(nX*2+nTheta))*4*3; //number triangles * number colour channels *number of vertices

	/*allocate arrays to feed buffers*/
	this->vertex_ = new float[this->nVertex_];
	this->colour_ = new float[this->nColour_];
	this->normal_ = new float[this->nVertex_];


	/*MS nose first*/
	float x[2], rho[2],  MaxOpacity = 0.5, dr, Opacity, dx0, dy0, dz0, dx1, dy1, dz1;
	int i, j, p = 0, pc = 0;
	float norms[9], verts[9], cols[12];

	for (i=0;i<nTheta;i++) {
		this->coordCalcNose((float) i,x,rho);

		/*vertical bit*/
		this->getBuffVertNose(x,rho,col,MaxOpacity,norms,cols,verts);
		for (j=0;j<9;j++) {
			this->normal_[p] = norms[j];
			this->vertex_[p] = verts[j];
			p++;
		}
		for (j=0;j<12;j++) {
			this->colour_[pc] = cols[j];
			pc++;
		}
		
		/*horizontal bit*/
		wiggleCart(this->rsm_,x[0],rho[0],0.0,0.2,&dx0,&dy0,&dz0);
		wiggleCart(this->rsm_,x[1],rho[1],0.0,0.2,&dx1,&dy1,&dz1);
		this->getBuffHorzNose(x,rho,dx0,dy0,dx1,dy1,col,MaxOpacity,norms,cols,verts);

		for (j=0;j<9;j++) {
			this->normal_[p] = norms[j];
			this->vertex_[p] = verts[j];
			p++;
		}
		for (j=0;j<12;j++) {
			this->colour_[pc] = cols[j];
			pc++;
		}	
	}
	
	
	/*now the middle bit*/
	for (i=0;i<nX;i++) {
		//get the right index for the mpx/mpr arrays
		j = i + 142;
		x[0] = this->mpx_[j];
		rho[0] = this->mpr_[j];
		x[1] = this->mpx_[j+1];
		rho[1] = this->mpr_[j+1];

		wiggleCart(this->rsm_,x[0],rho[0],0.0,0.2,&dx0,&dy0,&dz0);
		wiggleCart(this->rsm_,x[1],rho[1],0.0,0.2,&dx1,&dy1,&dz1);	
		
		dr = x[0]-this->rsm_;
		if (dr >= -2.0) {
			Opacity = MaxOpacity;
		} else if ((dr < -2.0) & (dr >= -5.0)) {
			Opacity = MaxOpacity*(1.0 + (dr+2.0)/3.0);
		} else {
			Opacity = 0.0;
		} 
		
		/*start with the vertical again*/
		//triangle 1 (x0,0),(x0,r0),(x1,r1)
		this->getBuffVertTri1(x,rho,col,Opacity,norms,cols,verts);
		for (j=0;j<9;j++) {
			this->normal_[p] = norms[j];
			this->vertex_[p] = verts[j];
			p++;
		}
		for (j=0;j<12;j++) {
			this->colour_[pc] = cols[j];
			pc++;
		}


		//triangle 2 (x0,0),(x1,r1),(x1,0)
		this->getBuffVertTri2(x,rho,col,Opacity,norms,cols,verts);
		for (j=0;j<9;j++) {
			this->normal_[p] = norms[j];
			this->vertex_[p] = verts[j];
			p++;
		}
		for (j=0;j<12;j++) {
			this->colour_[pc] = cols[j];
			pc++;
		}

		/*now horizontal*/
		//triangle 1 (x0,0),(x0,r0),(x1,r1)
		this->getBuffHorzTri1(x,rho,dx0,dy0,dx1,dy1,col,Opacity,norms,cols,verts);

		for (j=0;j<9;j++) {
			this->normal_[p] = norms[j];
			this->vertex_[p] = verts[j];
			p++;
		}
		for (j=0;j<12;j++) {
			this->colour_[pc] = cols[j];
			pc++;
		}	


		//triangle 2 (x0,0),(x1,r1),(x1,0)
		this->getBuffHorzTri2(x,rho,dx0,dy0,dx1,dy1,col,Opacity,norms,cols,verts);

		for (j=0;j<9;j++) {
			this->normal_[p] = norms[j];
			this->vertex_[p] = verts[j];
			p++;
		}
		for (j=0;j<12;j++) {
			this->colour_[pc] = cols[j];
			pc++;
		}	

	}
	
	initBuffers(
		this->buffers_,
		this->nVertex_,
		this->vertex_,
		this->nColour_,
		this->colour_,
		this->nVertex_,
		this->normal_
	);	
}
