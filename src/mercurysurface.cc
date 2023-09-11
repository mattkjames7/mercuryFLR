#include "include/mercurysurface.h"

/*Constructor for the Mercury class, loads the binary and populates the 
 * Vertex,Colour,Normal arrays*/
MercurySurface::MercurySurface() {
	std::cout << "Creating Mercury Object" << std::endl;
	this->readBinary();
	this->populateBuffers();
}

/*Destuctor will delete the arrays malloced earlier*/
MercurySurface::~MercurySurface() {
	std::cout << "Removing Mercury Object" << std::endl;

	delete [] this->vertex_;
	delete [] this->colour_;
	delete [] this->normal_;
}

/*this will read a binary file containing the RGB values for Mercury's surface*/
void MercurySurface::readBinary(){
	std::cout << "Reading Mercury Surface Image" << std::endl;
	Q_INIT_RESOURCE(resources);

	QFile file(":/data/mercurysurface.bin");
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "Failed to open the file!";
		return;
	}	
		
	QDataStream stream(&file);
	stream.setByteOrder(QDataStream::LittleEndian);

	stream >> this->w_ >> this->h_;
	std::cout << this->w_ << " " << this->h_ << std::endl;
	int n = this->w_*this->h_;
	this->R_.resize(n);
	this->G_.resize(n);
	this->B_.resize(n);

	int i;
	for (i=0;i<n;i++) {
		stream >> this->R_[i];
	}
	for (i=0;i<n;i++) {
		stream >> this->G_[i];
	}
	for (i=0;i<n;i++) {
		stream >> this->B_[i];
	}

	file.close();
	
}


/*Here we will calculate the vertex,normal and colour arrays*/
void MercurySurface::populateBuffers() {
	std::cout << "Populating Mercury Buffers" << std::endl;
	this->nVertices_ = this->w_*this->h_*3*4; //total size of buffers
	int p = 0;

	this->vertex_ = new GLfloat[this->nVertices_];
	this->colour_ = new GLfloat[this->nVertices_];
	this->normal_ = new GLfloat[this->nVertices_];

	int i, j, k;
	float x,y,z,lat[4],lon[4];
	
	int w = this->w_;
	int h = this->h_;

	for (i=0;i<w;i++) {
		for (j=0;j<h;j++) {
			lat[0] = -M_PI*(float(j)/float(h)-0.5);
			lat[1] = -M_PI*(float(j)/float(h)-0.5);
			lat[2] = -M_PI*(float(j+1)/float(h)-0.5);
			lat[3] = -M_PI*(float(j+1)/float(h)-0.5);
			
			lon[0] = 2*M_PI*(1.0-float(i)/float(w));
			lon[1] = 2*M_PI*(1.0-float(i+1)/float(w));
			lon[2] = 2*M_PI*(1.0-float(i+1)/float(w));
			lon[3] = 2*M_PI*(1.0-float(i)/float(w));
						
			for (k=0;k<4;k++) {
				x = cos(lat[k])*sin(lon[k]);
				y = cos(lat[k])*cos(lon[k]);
				z = sin(lat[k])-0.196;
				
				this->vertex_[p+3*k] = x;
				this->vertex_[p+3*k+1] = y;
				this->vertex_[p+3*k+2] = z;

				this->normal_[p+3*k] = x;
				this->normal_[p+3*k+1] = y;
				this->normal_[p+3*k+2] = z;

				this->colour_[p+3*k] = float(this->R_[j + h*i])/256.0;
				this->colour_[p+3*k+1] = float(this->G_[j + h*i])/256.0;
				this->colour_[p+3*k+2] = float(this->B_[j + h*i])/256.0;
			
			}
			p+=12;
		}
	}
	
	initBuffers(
		this->buffers_,
		this->nVertices_,
		this->vertex_,
		this->nVertices_,
		this->colour_,
		this->nVertices_,
		this->normal_
	);
}
