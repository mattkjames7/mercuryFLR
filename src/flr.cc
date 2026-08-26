#include "include/flr.h"

FLR::FLR() {
	this->readFLR();
	this->calculateDisplacedFieldLine();
}

FLR::~FLR() {

	delete [] x_;
	delete [] y_;
	delete [] z_;
	delete [] xd_;
	delete [] yd_;
	delete [] zd_;

	delete [] wr0_;
	delete [] wi0_;
	delete [] wr1_;
	delete [] wi1_;
	delete [] wr2_;
	delete [] wi2_;

}

void FLR::readFLR() {
	printf("Reading FLR\n");

	QFile file(":/data/flr.bin");
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "Failed to open the file!";
		return;
	}	
		
	QDataStream stream(&file);
	stream.setByteOrder(QDataStream::LittleEndian);

	stream >> this->n_;
	stream.readRawData(reinterpret_cast<char*>(this->f_), sizeof(float) * 3);

	//create arrays
	this->x_ = new float[this->n_];
	this->y_ = new float[this->n_];
	this->z_ = new float[this->n_];

	this->wr0_ = new float[this->n_];
	this->wi0_ = new float[this->n_];
	this->wr1_ = new float[this->n_];
	this->wi1_ = new float[this->n_];
	this->wr2_ = new float[this->n_];
	this->wi2_ = new float[this->n_];

	/* GPT did this bit, nice! */
	stream.readRawData(reinterpret_cast<char*>(this->x_), sizeof(float) * this->n_);
	stream.readRawData(reinterpret_cast<char*>(this->y_), sizeof(float) * this->n_);
	stream.readRawData(reinterpret_cast<char*>(this->z_), sizeof(float) * this->n_);

	stream.readRawData(reinterpret_cast<char*>(this->wr0_), sizeof(float) * this->n_);
	stream.readRawData(reinterpret_cast<char*>(this->wi0_), sizeof(float) * this->n_);
	stream.readRawData(reinterpret_cast<char*>(this->wr1_), sizeof(float) * this->n_);
	stream.readRawData(reinterpret_cast<char*>(this->wi1_), sizeof(float) * this->n_);
	stream.readRawData(reinterpret_cast<char*>(this->wr2_), sizeof(float) * this->n_);
	stream.readRawData(reinterpret_cast<char*>(this->wi2_), sizeof(float) * this->n_);

	file.close();
	
}

void FLR::calculateDisplacedFieldLine() {
	std::cout << "Calculating Wave Displacement" << std::endl;
	
	
	//create output and temp arrays first
	this->xd_ = new float[this->n_];
	this->yd_ = new float[this->n_];
	this->zd_ = new float[this->n_];	

	float *r = new float[this->n_];
	float *t = new float[this->n_];
	float *p = new float[this->n_];

	//convert to spherical
	int i;
	for (i=0;i<this->n_;i++) {
		r[i] = sqrtf(this->x_[i]*this->x_[i] + this->y_[i]*this->y_[i] +this->z_[i]*this->z_[i]);
		t[i] = atan2f(this->z_[i],sqrtf(this->x_[i]*this->x_[i] + this->y_[i]*this->y_[i]));
		p[i] = atan2f(this->y_[i],this->x_[i]);
	}
	
	//add some displacement
	float A = 0.2;
	for (i=0;i<this->n_;i++) {
		p[i] += A*this->wr2_[i]/r[i];
	}
	
	//convert back
	for (i=0;i<this->n_;i++) {
		this->xd_[i] = r[i]*cosf(p[i])*cosf(t[i]);
		this->yd_[i] = r[i]*sinf(p[i])*cosf(t[i]);
		this->zd_[i] = r[i]*sinf(t[i]);
	}
	
	delete [] r;
	delete [] t;
	delete [] p;
	
} 
