#include <stdio.h>
#include<sys/time.h>

static struct timeval start_time,stop_time; //created the global variables to be accessible in both function

void start_timer(){	

	//gettimeofday is part of time.h library and give us the time in sec and micro second
	gettimeofday(&start_time,(struct timezone*)NULL);
}
float stop_timer(){
  
  float elapsed_sec;
	gettimeofday(&stop_time,(struct timezone*)NULL);
	elapsed_sec= stop_time.tv_sec - start_time.tv_sec + (stop_time.tv_usec - start_time.tv_usec ) / 1000000.0; //casting the microsec time interval to float and get it in sec
	return elapsed_sec;
}
