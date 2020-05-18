#include <stdio.h>
#include <math.h>
#include <string.h>
#include <rpc/rpc.h>
#include "rcalc.h"

static record2  *pR = NULL;


float         *
sumsqrt_range_1_svc( record1 *r, struct svc_req *rqp)
{


static float             res;
res=0;
int delta=(r->value2)-(r->value1);
for (int i=0;i<=delta;++i){
 res =res+ sqrt (r->value1+i);
}

  return ((float *) &res);
}

record2         *
update_list_1_svc( record2 *r, struct svc_req *rqp)
{
pR = (record2 *) malloc(sizeof(record2));
pR->value1=(r->value1*r->value1)/10.0;
pR->value2=(r->value2*r->value2)/10.0;
pR->value3=(r->value3*r->value3)/10.0;
pR->value4=(r->value4*r->value4)/10.0;
pR->value5=(r->value5*r->value5)/10.0;
return ((record2 *) pR);
}
