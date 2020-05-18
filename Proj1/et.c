#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

void start_timer();
float stop_timer();


int buf_size;
char *buf;


void foo(){
  int i;
	for(i=0;i<buf_size; i+=4096){
      buf[i]='a'; 
    }
}

int main(int argc, char * argv[]){   
  
  if(argc<1)
    printf("The command had no arguments.");
  else
    buf_size=atoi(argv[1])* 1024; //multiplying to 1024 to get K for buf_size (heap size)
  buf= calloc(buf_size, sizeof(int));
  
  pthread_t child;  
  start_timer();
  
  if(pthread_create(&child,NULL,(void *)foo,NULL) != 0){
    printf("Cannot create pthread \n");    
  }
  
  pthread_join(child , NULL); //wait for the child to finish its job 
  free (buf);
  
  printf("elapsed_sec time for creating-deleting buffer size of %s with thread is : %f\n", argv[1] , stop_timer());
  
    
  
return 0;
}
