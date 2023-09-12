#ifndef __STREAMLINE_H__
#define __STREAMLINE_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class Streamline {
	public:
		int n_;
		float x_[269], y_[269];
		Streamline();
		void populateStreamline();
};

#endif
