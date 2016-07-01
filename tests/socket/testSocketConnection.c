/*
 * File:   testSocketConnection.c
 * Author: will
 *
 * Created on 23/05/2015, 00:36:31
 */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

#define EXITCOMMAND "exit\n"

/*
 * Simple C Test Suite
 */

void test1(int argc, char** argv) 
{
   int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   
   char buffer[256];
   
   if (argc <3) {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }
   portno = atoi(argv[2]);
   
   /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0)
   {
      perror("ERROR opening socket");
      exit(1);
   }
   server = gethostbyname(argv[1]);
   
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);
   
   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
   {
      perror("ERROR connecting");
      exit(1);
   }
   
   /* Now ask for a message from the user, this message
   * will be read by server
   */
   printf("Please enter the message: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);   
   
   if(strcmp(buffer, EXITCOMMAND) == 0)
   {
       exit(0);
   }
   
   /* Send message to the server */
   n = write(sockfd, buffer, strlen(buffer));
   
   if (n < 0)
   {
      perror("ERROR writing to socket");
      exit(1);
   }
   
   /* Now read server response */
   bzero(buffer,256);
   n = read(sockfd, buffer, 255);
   
   if (n < 0)
   {
      perror("ERROR reading from socket");
      exit(1);
   }
   printf("%s\n",buffer);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% testSocketConnection\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (testSocketConnection)\n");
    while(1){
        test1(argc, argv);
    }
    printf("%%TEST_FINISHED%% time=0 test1 (testSocketConnection) \n");    

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
