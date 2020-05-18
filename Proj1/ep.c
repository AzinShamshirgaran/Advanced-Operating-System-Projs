#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void start_timer();
float stop_timer();


int main(int argc, char *argv[]){

  pid_t cpid; 
  int status;
  int buf_size;
  char *buf;
   
  if(argc<1)
    printf("The command had no arguments.");
  else
    buf_size=atoi(argv[1])* 1024; //multiplying to 1024 to get K for buf_size
  buf= calloc(buf_size, sizeof(int)); 
    
  start_timer();
  cpid=fork();
  
  if(cpid<0){
  
    printf("fork error\n");
    exit(1);
  }
  if(cpid==0){ //child process
    int i;
    for(i=0;i<buf_size; i+=4096){
      buf[i]='a'; 
    }
    exit(0);
  }
  else{ //parent process
    waitpid(cpid,&status,0); //wait for child to finish its job
    free (buf);
    printf("elapsed_sec time for creating-deleting buffer size of %s with fork is : %f\n", argv[1] , stop_timer());
  }
    
  
return 0;
}
