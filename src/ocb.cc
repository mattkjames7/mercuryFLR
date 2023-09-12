#include "include/ocb.h"

OCB::OCB() {
	this->loadOCB();
}


void OCB::loadOCB() {
	std::cout << "Loading OCB" << std::endl;
	this->readOCBBinary();
	this->convertToCartesian();
}

void OCB::readOCBBinary() {
	std::cout << "Reading OCB File" << std::endl;

	QFile file(":/data/ocb.bin");
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "Failed to open the file!";
		return;
	}	
		
	QDataStream stream(&file);
	stream.setByteOrder(QDataStream::LittleEndian);

	stream.readRawData(reinterpret_cast<char*>(this->mlt_), sizeof(float)*24);
	stream.readRawData(reinterpret_cast<char*>(this->lctn_), sizeof(float)*24);
	stream.readRawData(reinterpret_cast<char*>(this->lcts_), sizeof(float)*24);

	stream.readRawData(reinterpret_cast<char*>(this->mlat_), sizeof(float)*24);
	stream.readRawData(reinterpret_cast<char*>(this->latn_), sizeof(float)*24);
	stream.readRawData(reinterpret_cast<char*>(this->lats_), sizeof(float)*24);

	file.close();
	
}

void OCB::convertToCartesian() {
	int i, j;
	float r = 1.01;
	for (i=0;i<25;i++) {
		j = i % 24;
		this->xn_[i] = -r*cos(this->latn_[j]*M_PI/180.0)*cos(15.0*this->lctn_[j]*M_PI/180.0);
		this->yn_[i] = -r*cos(this->latn_[j]*M_PI/180.0)*sin(15.0*this->lctn_[j]*M_PI/180.0);
		this->zn_[i] = r*sin(this->latn_[j]*M_PI/180.0)-0.196;

		this->xs_[i] = -r*cos(this->lats_[j]*M_PI/180.0)*cos(15.0*this->lcts_[j]*M_PI/180.0);
		this->ys_[i] = -r*cos(this->lats_[j]*M_PI/180.0)*sin(15.0*this->lcts_[j]*M_PI/180.0);
		this->zs_[i] = r*sin(this->lats_[j]*M_PI/180.0)-0.196;
	}
	
}
