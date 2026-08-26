#ifndef __TRACEWRAPPER_H_INCLUDED__
#define __TRACEWRAPPER_H_INCLUDED__
#include "kt17trace.h"
#include <math.h>
void TraceWrapper(double *x, double *y, double *z, int n, double *xt, double *yt, double *zt, int *nstep, int maxlen, bool *open);
#endif
