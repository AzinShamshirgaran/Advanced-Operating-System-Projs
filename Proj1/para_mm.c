#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#define N 160

void start_timer();
float stop_timer();

pthread_barrier_t barrier;

int a[N][N], b[N][N], c[N][N];
int portion_Range = 0;



void worker(int *iptr){
	int my_tid= *iptr;
	//printf("my_tid %i\n", my_tid);
	for(int i = my_tid; i < (my_tid+portion_Range); i++)
		for(int j=my_tid; j < (my_tid+portion_Range); j++){
			c[i][j]=0;
			for(int k=0; k<N; k++)
				c[i][j]+=a[i][k]*b[k][j];
		}
	
	printf("job for child doing part %i has been finished\n",my_tid);
	pthread_barrier_wait(&barrier);	
}


int main(int argc, char *argv[]){

  int thread_Num;

  if(argc<1)
    printf("The command had no arguments.");
  else
	  thread_Num=atoi(argv[1]);
	
 

	pthread_barrier_init(&barrier,NULL,thread_Num+1); //We get threads number from argv[1] ; it means that it also wait for main to finish its job 
	pthread_t child[thread_Num]; 
	

  portion_Range = N/thread_Num; 
  int start_tid = 0;
  int tid [thread_Num]; 
    
  for(int i=0;i<thread_Num;i++){
        tid [i] = start_tid;
        start_tid = start_tid + portion_Range;
    }
    
  
	start_timer();
	
	for(int i=0;i<thread_Num;i++){		
		
		if(pthread_create(&child[i],NULL,(void *)worker, (void *)&tid[i]  ) != 0)
			printf("Cannot create pthread \n");    
		
	}

	pthread_barrier_wait(&barrier);	
	printf("elapsed_sec time for matrix multiplication with %s threads is : %f\n", argv[1] , stop_timer());		
	return 0;
}
