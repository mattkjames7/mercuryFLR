#include "ExampleTraces.h"
using namespace std;

ExampleTraces::ExampleTraces() {
	MaxTraceSteps = 2000;
	printf("Creating Example Traces Object\n");
	CalculateStartingPoints();
	RunTrace();
}

ExampleTraces::ExampleTraces(int MaxSteps) {
	MaxTraceSteps = MaxSteps;
	printf("Creating Example Traces Object\n");
	CalculateStartingPoints();
	RunTrace();
}

ExampleTraces::~ExampleTraces() {
	printf("Removing Example Traces Object\n");
	free(lat);
	free(x0);
	free(y0);
	free(z0);
	free(xt);
	free(yt);
	free(zt);
	free(nstep);
	free(open);
}

void ExampleTraces::CalculateStartingPoints() {
	printf("Calcualting Trace Starting Points\n");
	int nLat = 20;
	lat = (float*) malloc((nLat)*sizeof(float));
	
	int i;
	for (i=0;i<nLat/2;i++) {
		lat[i*2] = 30.0 + i*15.0;
		lat[i*2 + 1] = -lat[i*2];
	}
	
	x0 = (double*) malloc((nLat)*sizeof(double));
	y0 = (double*) malloc((nLat)*sizeof(double));
	z0 = (double*) malloc((nLat)*sizeof(double));
	
	float R=1.01;
	for (i=0;i<nLat;i++) {
		x0[i] = -R*cos(lat[i]*M_PI/180.0);
		y0[i] = 0.0;
		z0[i] = R*sin(lat[i]*M_PI/180.0);
	}
	
	nt = nLat;
}

void ExampleTraces::RunTrace() {
	int MaxTraceSteps = 2000;
	printf("Running Trace Wrapper (%d traces)\n",nt);
	/*allocate memory for trace arrays*/
	nstep = (int*) malloc(sizeof(int)*nt);
	xt = (float*) malloc(sizeof(float)*nt*MaxTraceSteps);
	yt = (float*) malloc(sizeof(float)*nt*MaxTraceSteps);
	zt = (float*) malloc(sizeof(float)*nt*MaxTraceSteps);
	double *xtd = (double*) malloc(sizeof(double)*nt*MaxTraceSteps);
	double *ytd = (double*) malloc(sizeof(double)*nt*MaxTraceSteps);
	double *ztd = (double*) malloc(sizeof(double)*nt*MaxTraceSteps);
	open = (bool*) malloc(sizeof(bool)*nt*MaxTraceSteps);
	TraceWrapper(x0,y0,z0,nt,xtd,ytd,ztd,nstep,MaxTraceSteps,open);
	
	
	//loop through traces and see if there are double-traces
	int i, j;
	for (i=0;i<nt/2;i++) {
		j = i*2 + 1;
		if (open[i] == false) {
			//nstep[j] = 0;
		}
	}
	
	//copy the doubles back into the float arrays
	for (i=0;i<nt*MaxTraceSteps;i++) {
		xt[i] = (float) xtd[i];
		yt[i] = (float) ytd[i];
		zt[i] = (float) ztd[i];
	}
	
	free(xtd);
	free(ytd);
	free(ztd);
	
}
