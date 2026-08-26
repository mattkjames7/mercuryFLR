#ifndef __EXAMPLETRACES_H_INCLUDED__
#define __EXAMPLETRACES_H_INCLUDED__

#include "TraceWrapper.h"
using namespace std;
class ExampleTraces {
	private:
		double *x0, *y0, *z0;
		float *lat;
		void CalculateStartingPoints();
		void RunTrace();
	public:
		int nt;
		float *xt, *yt, *zt;
		int *nstep, MaxTraceSteps;
		bool *open;
		ExampleTraces();
		ExampleTraces(int);
		~ExampleTraces();
};
#endif
