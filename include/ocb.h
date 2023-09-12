#ifndef __OCB_H_INCLUDED__
#define __OCB_H_INCLUDED__
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QDataStream>

class OCB {
	private:
		float mlt_[24], mlat_[24], lctn_[24], latn_[24], lcts_[24], lats_[24];
		void readOCBBinary();
		void convertToCartesian();
	public:
		int n_ = 24;
		float xn_[25], yn_[25], zn_[25], xs_[25], ys_[25], zs_[25];
		void loadOCB();
		OCB();
};

#endif
