#ifndef __FLR_H__
#define __FLR_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QDataStream>


class FLR {
	public:
		FLR();
		~FLR();
		void readFLR();
		void calculateDisplacedFieldLine();
		float *x_, *y_, *z_, *xd_, *yd_, *zd_;
		float f_[3];
		float *wr0_, *wi0_, *wr1_, *wi1_, *wr2_, *wi2_;
		int n_;
};



#endif
