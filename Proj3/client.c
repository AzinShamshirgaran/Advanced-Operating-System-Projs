#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/un.h>
#include <signal.h>
#include <wait.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>


/* This program broadcasts a message in datagram to the server and waits
   for reply. */



#define BUFMAX 1024


int main()
{

int sk;
char buf[BUFMAX];
char GET[] = "GET CISBANK";
char MSG[40];
char* recv4 = malloc(5);
char* recv5 = malloc(20);

struct sockaddr_in clnt_adr, remote, serv_adr;
struct hostent *hp;
socklen_t       serv_add_len;            // Length of client address
  
int             orig_sock,           // Original socket in client
                  len;                 // Misc. counter
if ((orig_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("generate error"); return 2;
  }
clnt_adr.sin_family      = AF_INET;            // Set address type
clnt_adr.sin_addr.s_addr = INADDR_ANY;  // Any interface
clnt_adr.sin_port        = 0;
if (bind( orig_sock, (struct sockaddr *) &clnt_adr,
sizeof(clnt_adr)) < 0){
close(orig_sock);
perror("bind error"); return 3;
  }
  
   
serv_add_len = sizeof(clnt_adr);
getsockname(orig_sock, (struct sockaddr *)&clnt_adr, &serv_add_len);
sprintf(MSG, "%s ", GET);
  /* Create an Internet domain datagram socket */
sk = socket(AF_INET,SOCK_DGRAM,0);

remote.sin_family = AF_INET;

  /* Get the remote machine address from its symbolic name 
     given in the command line argument */
  // remote.sin_addr.s_addr = inet_addr("255.255.255.255"); 
remote.sin_addr.s_addr = inet_addr("137.148.205.255"); 

  /* get the remote port number from the command line */
remote.sin_port = ntohs(29460);
  
  /* setsockopt is required on Linux, but not on Solaris */
setsockopt(sk,SOL_SOCKET,SO_BROADCAST,(struct sockaddr *)&remote,sizeof(remote));

sendto(sk,MSG,strlen(MSG)+1,0,(struct sockaddr *)&remote,sizeof(remote));/* Send the message */
 

socklen_t addrlen;
int lent;

recvfrom(sk,buf,BUFMAX,O_NONBLOCK,(struct sockaddr *) &remote,&addrlen);
  
strncpy(recv4, buf+15, 5);
strncpy(recv5, buf, 15);
printf("Service Provided by %s at port %s\n", recv5, recv4);
 
close(sk);
   
serv_adr.sin_family      = AF_INET;            // Set address type
 
inet_aton(recv5, &serv_adr.sin_addr);
serv_adr.sin_port        = ntohs(atoi(recv4));  
                                
if ((orig_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("generate error");
return 3;
  }                                    // CONNECT
if (connect( orig_sock,(struct sockaddr *)&serv_adr,
               sizeof(serv_adr)) < 0) {
    perror("connect error");
    return 4;
  }
  char msg3[] = "quit";
  char recv2[40];
  char recv3[40];
  //printf("sentttt\n");
   char MSG2[100];
   char MSG3[100];
  do {                                 // Process
  char msg1[] = "query";
  char msg2[] = "update";
  
write(1,"> ", 2);
if ((len=read(0, buf, BUFMAX)) > 0) {
    //printf("%s",buf);
uint32_t recv1;


if (memcmp( buf, msg2, strlen( msg2 )) == 0){
recv1==1002;
  
               
strncpy(recv2, buf+7, 6);

strncpy(recv2, buf+13, 6);
  sprintf(MSG3, " %d %d %d\n" ,  recv1, atoi(recv2), atoi(recv3));

          send(orig_sock, MSG3, strlen( MSG3 )+1, 0);  
          }
           if (memcmp( buf, msg1, strlen( msg1 )) == 0){
      recv1==1001;
                  
          

          strncpy(recv2, buf+7, 6);
          sprintf(MSG2, " %d %d\n" ,  recv1, atoi(recv2));
          send(orig_sock, MSG2, strlen( MSG2 )+1, 0);  
          }
      
      if ((len=recv(orig_sock, buf, len,0)) > 0 )
        write(1, buf, len);
    }
  } while( memcmp( buf, msg3, strlen( msg3 )) != 0 );            
  close(orig_sock);
  return 0;
}
