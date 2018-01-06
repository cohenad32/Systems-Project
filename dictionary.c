#include "csapp.h"
#include <stdio.h>

#include "csapp.h"

int main(int argc, char **argv)
{
  char *buffer;
  int clientfd, retval;
  char *host = "services.aonaware.com", *port = "80", buf[MAXLINE];
  char str[MAXLINE];
  char *request_host_header="Host: services.aonaware.com";
  rio_t rio;

  if ((buffer = getenv("QUERY_STRING")) != NULL){
  }

  strcpy(str, "/DictService/DictService.asmx/Define?");
  strcat(str,buffer);

  char *request_uri = str, *newline = "\r\n";

  clientfd = Open_clientfd(host, port);
  Rio_readinitb(&rio, clientfd);

  /* send the request */
  sprintf(buf, "GET %s HTTP/1.1%s%s%s%s",
	  request_uri, newline, request_host_header, newline, newline);

  printf("sending to server: %s\n", buf);
  Rio_writen(clientfd, buf, strlen(buf));

  char *stop_string="  </Definitions>";
  int stop_string_len = strlen(stop_string);

  while((retval = Rio_readlineb(&rio, buf, MAXLINE)) > 0) {
    fprintf(stdout, "response: %s\n", buf);
    fflush(stdout);

    /*                                                                                                                                                                              
     * GROSS HACK: It seems this particular server doesn't send a                                                                                                                   
     * newline after the last line, so Rio_readlineb ends up blocking                                                                                                               
     * forever waiting for the last line.  To work around this, Look                                                                                                                
     * for the next to last line, then close the connection.                                                                                                                        
     */
    if(strncmp(buf, stop_string, stop_string_len) == 0) {
      break;
    }
  }

  Close(clientfd); //line:netp:echoclient:close
  exit(0);
}
/* $end echoclientmain

int main(void) {
  char *buf;
  char arg1[MAXLINE], content[MAXLINE];
  int clientfd;
  char str[MAXLINE];
  char *rio;
  char *command;

  /*get input from user*/
/*if ((buf = getenv("QUERY_STRING")) != NULL){
  }
  
  strcpy(str, "GET /DictService/DictService.asmx/Define?");
  strcat(str,buf);
  strcat(str," HTTP/1.1\nHost: services.aonaware.com\n\n");

  command = str;
  /* open a text file to write the info that will be parsed*/
/*FILE * fp;
  fp = fopen("temp.txt","w");
  /*open a connection with the dictionary api in order to get the definition*/
/*clientfd = (Open_clientfd("services.aonaware.com", "80"));
  Rio_readinitb(&rio, clientfd);
  Rio_writen(clientfd, command, strlen(command));
  Rio_readlineb(&rio, buf, MAXLINE);
  sprintf (content, "%s", buf);
 
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Rio_readlineb(&rio, buf, MAXLINE);
  Fputs(buf, stdout);
  fclose(fp);
  /* Make the response body */
/*sprintf(content,"%s", buf);
  sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
  sprintf(content, "%sThanks for visiting!\r\n", content);

 /* Generate the HTTP response */
/*printf("Connection: close\r\n");
  printf("Content-length: %d\r\n", (int)strlen(content));
  printf("Content-type: text/html\r\n\r\n");
  printf("%s", content);
  fflush(stdout);

  exit(0);
}
*/
