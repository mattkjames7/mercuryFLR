#include "TraceWrapper.h"


void TraceWrapper(double *x, double *y, double *z, int n, double *xt, double *yt, double *zt, int *nstep, int maxlen, bool *open) {
	printf("Tracing Field\n");
	double Params[3] = {1.42,7.37,2.16};
	double FP[n*20];
	double bx[n*maxlen],by[n*maxlen],bz[n*maxlen],Rmsm[n*maxlen],Rmso[n*maxlen];
	//double *bx,*by,*bz,*Rmsm,*Rmso;
	int i;
	kt17MultiTrace(x,y,z,n,maxlen,0.01,0.05,79,3,Params,nstep,xt,yt,zt,bx,by,bz,Rmsm,Rmso,FP);

	for (i=0;i<n;i++) {
		
		if (isfinite(FP[i*20 + 18])) {
			open[i] = false;
		} else {
			open[i] = true;
		}
	}
	printf("Finished Tracing\n");
	return;
}
