#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


#define PORT 29460
#define BUFMAX 2048
#define MSG "OK"



struct map
{
    char  name[20];
    char  address[20];
};




int main()
{

struct sockaddr_in local, remote;
int sk,sk1,rlen=sizeof(remote),len=sizeof(local);
char buf[BUFMAX];
int i,p=0;
char recv1[40];

    //char *recv3;
char recv3[40];
    //char recv4[40];
char* recv4 = malloc(5);
char* db_name = malloc(20);
char MSG2[100];

  /* Create an Internet domain datagram socket from which to read */
  
  
sk1 = socket(AF_INET,SOCK_DGRAM,0);
    
local.sin_family = AF_INET; /* Define the socket domain */
local.sin_addr.s_addr = INADDR_ANY; /* Wildcard mach. addr */
local.sin_port = htons(29460); /* hardcode port number */
  


struct map my_map;
char msg1[] = "PUT";
char msg2[] = "GET";
int lent;



do{
sk = socket(AF_INET,SOCK_DGRAM,0);
if (sk < 0) {
      perror("ERROR opening socket");
      exit(1);
}

if(bind(sk,(struct sockaddr *)&local,sizeof(local)) <0) {
       printf("bind fails%s\n", strerror(errno));
       exit(1); 
}


while((lent=recvfrom(sk,buf,BUFMAX,0,(struct sockaddr *) &remote,&rlen))>0){

   for (i=0; i<lent;i++){
   if (isdigit(buf[i])){
   p=i;
   //printf("%d\n",i);
   break;
   }
}
strncpy(db_name, buf+4, p-4);
if (memcmp( buf, msg1, strlen( msg1 )) == 0){ // it has PUT
sendto(sk,MSG,strlen(MSG)+1,0,(struct sockaddr *) &remote,sizeof(remote));

          
strncpy(recv4, buf+p, 5);
      
    
strncpy(recv3,inet_ntoa(remote.sin_addr), strlen(inet_ntoa(remote.sin_addr)));
int Q = atoi(recv4) / 256;
int R = atoi (recv4) % 256;
    
   
printf("Received from %s: PUT %s %s.%d.%d\n", inet_ntoa(remote.sin_addr), db_name,inet_ntoa(remote.sin_addr), Q,R );

     
    
     
strncpy(my_map.name, db_name, strlen(db_name)); 
sprintf(MSG2, "%s %d %d\n" ,  recv3, Q,R);
strncpy(my_map.address, MSG2, strlen(MSG2));
   
 
  }

if (memcmp( buf, msg2, strlen( msg2 )) == 0){ //it has GET
printf("Received from %s: %s \n", inet_ntoa(remote.sin_addr), buf);
 
  
char MSG1[40];

  
  
sprintf(MSG1, "%s %s\n" ,  recv3, recv4);
sendto(sk,MSG1,strlen(MSG1)+1,0,(struct sockaddr *)&remote,sizeof(remote));

  
  }
  }
   }while(1);
  
  close(sk);

  

  return 0;
}
