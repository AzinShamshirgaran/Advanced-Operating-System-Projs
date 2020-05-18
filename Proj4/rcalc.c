#include <stdio.h>
#include <ctype.h>
#include <rpc/rpc.h>
#include "rcalc.h"

#define PRINTRECORD(pR) {\
    printf("%.6g\t%.6g\t%.6g\t%.6g\t%.6g\n", \
    pR->value1, pR->value2, \
    pR->value3, pR->value4, pR->value5);\
  }
  
int main(argc, argv)
  int             argc;
  char           *argv[];
{

  CLIENT         *cl;    /* a client handle */
  int             key;
 
  if  (strcmp(argv[2] , "-u")==0) {
  key= 2;
   if ((argc != 8) ) {
    fprintf(stderr, "Usage: %s server key value value value value value\n", argv[0]);
    exit(1);
  }
}
else if  (strcmp(argv[2] , "-r")==0) {
key=1;
 if ((argc != 5) ) {
    fprintf(stderr, "Usage: %s server key value value \n", argv[0]);
    exit(1);
  }
}
else{
fprintf(stderr, "key is not valid\n");
    exit(1);
}

 if (!(cl = clnt_create(argv[1], RCALCPROG, RCALCVERS, "tcp"))) {
    /*
     * CLIENT handle couldn't be created, server not there.
     */
    clnt_pcreateerror(argv[1]);
    exit(1);
  }


  switch (key) {
  case SUMSQRT_RANGE:
  {   
  record1  *cR = (record1 *) malloc(sizeof(record1));
cR->value1=atoi(argv[3]);
cR->value2=atoi(argv[4]);

//    double res;
//    res=*sumsqrt_range_1(cR, cl);
    printf("%f\n",*sumsqrt_range_1(cR, cl));

    break;
    }
    case UPDATE_LIST:
    {
    record2  *fR = (record2 *) malloc(sizeof(record2));
    fR->value1=atoi(argv[3]);
    fR->value2=atoi(argv[4]);
    fR->value3=atoi(argv[5]);
    fR->value4=atoi(argv[6]);
    fR->value5=atoi(argv[7]);
//    record2  *kR = (record2 *) malloc(sizeof(record2));
//    kR=update_list_1(fR, cl);
    PRINTRECORD(update_list_1(fR, cl));

    break;
    }
     default:
    fprintf(stderr, "%s: unknown key\n", argv[0]);
    exit(1);
  }
  
 
}
