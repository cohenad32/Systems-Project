#include "csapp.h"
#include <stdio.h>

int main(void) {
  char *buf;
  char arg1[MAXLINE], content[MAXLINE];
  int clientfd;
  char str[MAXLINE];
  char *rio;
  char *command;

  /*get input from user*/
  if ((buf = getenv("QUERY_STRING")) != NULL){
  }
  
  strcpy(str, "GET /DictService/DictService.asmx/Define?");
  strcat(str,buf);
  strcat(str," HTTP/1.1\nHost: services.aonaware.com\n\n");

  command = str;

  /*open a connection with the dictionary api in order to get the definition*/
  clientfd = (Open_clientfd("services.aonaware.com", "80"));
  Rio_readinitb(&rio, clientfd);
  Rio_writen(clientfd, command, strlen(command));
  Rio_readlineb(&rio, buf, MAXLINE);
  /* Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE); */
  Fputs(buf, stdout);
  
  /* Make the response body */
  sprintf(content,"%s", buf);
  sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
  sprintf(content, "%sThanks for visiting!\r\n", content);

  /* Generate the HTTP response */
  printf("Connection: close\r\n");
  printf("Content-length: %d\r\n", (int)strlen(content));
  printf("Content-type: text/html\r\n\r\n");
  printf("%s", content);
  fflush(stdout);

  exit(0);
}
