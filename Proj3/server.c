#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <wait.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUFMAX  2048
#define PORTNUM 29460
#define MAX     1024               


// struct of each record in databse 
struct record
{
    int	  acctnum; /* unique key in sorted order*/
    char  name[20];
    float value;
    int age;
};


void signal_catcher(int the_sig){
  wait(0);                             // cleanup the zombie 
}


int main()
{

 int             orig_sock,           // Original socket in server
                  new_sock;            // New socket from connect
socklen_t	clnt_len;
 
  struct sockaddr_in  clnt_adr, serv_adr; // client and  server addresses
   socklen_t       serv_add_len;            // Length of client address
  int             len, i;              // Misc counters, etc.
                                       // Catch when child terminates
  if (signal(SIGCHLD , signal_catcher) == SIG_ERR) {
    perror("SIGCHLD"); return 1;
  }
  if ((orig_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("generate error"); return 2;
  }
  serv_adr.sin_family      = AF_INET;            // Set address type
  serv_adr.sin_addr.s_addr = INADDR_ANY;  // Any interface
  serv_adr.sin_port        = 0;
  
 if (bind( orig_sock, (struct sockaddr *) &serv_adr,
            sizeof(serv_adr)) < 0){
    close(orig_sock);
    perror("bind error"); return 3;
  }
  
   
  serv_add_len = sizeof(serv_adr);
  getsockname(orig_sock, (struct sockaddr *)&serv_adr, &serv_add_len);
//printf("%s:\n", inet_ntoa(serv_adr.sin_addr));
//printf("%d:\n", serv_adr.sin_port);
    
 
  


 


  char PUT[] = "PUT CISBANK";
  
 
  char MSG[40];
  

  sprintf(MSG, "%s %d", PUT,  ntohs(serv_adr.sin_port));
  
  
  int sk;
  unsigned char buf[BUFMAX];
  

  struct sockaddr_in remote;
  

  struct hostent *hp;


  sk = socket(AF_INET,SOCK_DGRAM,0);
  remote.sin_family = AF_INET;


  remote.sin_addr.s_addr = inet_addr("137.148.205.255"); 


  remote.sin_port = ntohs(29460);
  

 
  setsockopt(sk,SOL_SOCKET,SO_BROADCAST,(struct sockaddr *)&remote,sizeof(remote));
  
 
  sendto(sk,MSG,strlen(MSG)+1,0,(struct sockaddr *)&remote,sizeof(remote));
  
//printf("sent\n");
  socklen_t addrlen;
  recvfrom(sk, &buf, BUFMAX,  O_NONBLOCK, (struct sockaddr *)&remote, &addrlen);
  
 //printf("sentttt\n");
  char ip_buff[100];
  inet_ntop(AF_INET, &(remote.sin_addr), ip_buff, 100);
  
  if (strcmp(buf, "OK") == 0){
      printf("Registration OK from %s\n", ip_buff);
  } 
  //while ((getchar()) != '\n'); 
 
  close(sk);
  
 //  The communication to service map has been done
 // Now it starts to communicate with client trough CTP
//  

 if (listen(orig_sock, 5) < 0 ) {               
    close (orig_sock);
    perror("listen error"); 
    return 4;
  }
  

  do {
    clnt_len = sizeof(clnt_adr);

    if ((new_sock = accept( orig_sock, (struct sockaddr *) &clnt_adr, &clnt_len)) < 0) {
      close(orig_sock);
      perror("accept error"); 
      return 5;
    }
    
     char ip_buff_tcp[100];
    inet_ntop(AF_INET, &(clnt_adr.sin_addr), ip_buff_tcp, 100);
    printf("Service requested from %s\n", ip_buff_tcp);


    if ( fork( ) == 0 ) {                       

      close(orig_sock);
      while ( (len=recv(new_sock, buf, MAX, 0)) > 0 ){
      

        uint32_t recv1;
        uint32_t recv2;
        uint32_t recv3;
        char ar[40];


        strncpy(ar, buf, 4);
       // printf("%s\n", buf);
        

        if (recv1==1002){
          

          recv2 = buf[4] + (buf[5]<<8) + (buf[6]<<16) + (buf[7]<<24)  ;
          recv2 = recv2 >> 16;
          recv2 = ntohs(recv2);
          

          recv3 = buf[8] + (buf[9]<<8) + (buf[10]<<16) + (buf[11]<<24)  ;
          recv3 = ntohs(recv3);
          recv3 = recv3<<16;
          uint32_t num = recv3;
          float f;
          f = *((float*)&num);
          

          int flag = 0;
          

          int counter;
          struct record my_record;
          

          int db_test = open("db20",O_RDWR);
          if (!db_test){
            printf("Unable to open file!\n");
          }
          

          char buff_send [100];
          
 
  
          

            lseek(db_test,sizeof(struct record),1);
            
                     if (lockf(db_test, F_LOCK, sizeof(my_record))==-1){
                  printf("can not lock\n");
                  exit(1);
              }
              read(db_test, &my_record,sizeof(struct record));

            if (my_record.acctnum==recv2){
              

              flag = 1;
              
          
              my_record.value = my_record.value + f;
              

              lseek(db_test,-sizeof(my_record.value),1);              
              
  
     
              
    
              write(db_test , &my_record.value , sizeof(my_record.value) );
              
            
              lockf(db_test, F_ULOCK, -sizeof(struct record));
             
              
 
              
 
              sprintf(buff_send, "%s %d %.1f                  ", my_record.name, my_record.acctnum, my_record.value);
              
  
              send(new_sock, buff_send, strlen(buff_send)+1, 0);      
            }
          
          if (flag == 0){
 
              char ret_msg[] = "Inquiry not found";
              sprintf(buff_send, "%s                                   ", ret_msg);
              send(new_sock, buff_send, strlen(buff_send)+1, 0);        
          }
          

          close(db_test);
        }
        
        
 
        if (ar=="query"){
                      
          recv2 = buf[4] + (buf[5]<<8) + (buf[6]<<16) + (buf[7]<<24)  ;
          recv2 = recv2 >> 16;
          recv2 = ntohs(recv2);

          int counter;
          struct record my_record;
          
          int db_test = open("db20",O_RDWR);
          
          if (!db_test){
            printf("Unable to open file!\n");
          }
          
          int flag = 0;
          char buff_send [100];
          lseek(db_test,sizeof(struct record),1);
               if (lockf(db_test, F_LOCK, sizeof(my_record))==-1){
                  printf("can not lock\n");
                  exit(1);
              }

            
            read(db_test, &my_record,sizeof(struct record));
            lseek(db_test,-sizeof(struct record),1);

            if (my_record.acctnum==recv2){
              flag = 1;
              sprintf(buff_send, "%s %d %.1f                  ", my_record.name, my_record.acctnum, my_record.value);
              send(new_sock, buff_send, strlen(buff_send)+1, 0);               
            }
          lockf(db_test, F_ULOCK, -sizeof(my_record));
          
          if (flag == 0){
              char ret_msg[] = "Inquiry not found";
              sprintf(buff_send, "%s                                   ", ret_msg);
              send(new_sock, buff_send, strlen(buff_send)+1, 0);               
          }
          
          close(db_test);
        }

        close(new_sock);                           
        return 0;
      }
    } else

      close(new_sock);                           
  } while( 1 );                               
  return 0;
}
