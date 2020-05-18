/* structure definitions, no enumerations needed */

struct record1 {
  int value1;	/* <> defines the maximum */
  int value2;		 /* possible length */
};

struct record2 {
  float value1;	/* <> defines the maximum */
  float value2;		 /* possible length */
  float value3;
  float value4;
  float value5;
};

/* program definition, no union or typdef definitions needed */
program RCALCPROG { /* could manage multiple servers */
	version RCALCVERS {
		float SUMSQRT_RANGE(record1) = 1;
   record2 UPDATE_LIST(record2) = 2;
	} = 1;
} = 0x20009460;  /* program number ranges established by ONC */
