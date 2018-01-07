#include "csapp.h"
#include <stdio.h>
#include <regex.h>
#include "csapp.h"

int main(int argc, char **argv)
{
  char *buffer;
  int clientfd, retval;
  char *host = "services.aonaware.com", *port = "80", buf[MAXLINE];
  char str[MAXLINE];
  char *request_host_header="Host: services.aonaware.com";
  rio_t rio;
  FILE *fp;
  fpos_t position;
  regex_t regex;
  regex_t regex2;
  int reti;
  int reti2;
  int match = 0;

  /*open a file to write to*/
  fp = fopen("temp.txt", "w+");
  /*get the position of the file*/
  fgetpos(fp, &position);

  if ((buffer = getenv("QUERY_STRING")) != NULL){
  }

  strcpy(str, "/DictService/DictService.asmx/DefineInDict?dictId=wn&");
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
    fprintf(fp, "%s\n", buf);

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
  fsetpos(fp, &position);

  /*do regex stuff*/
  /*compile regex*/
  reti = regcomp(&regex, "<WordDefinition>", 0);
  reti2 = regcomp(&regex2, "</WordDefinition>", 0);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }

  /*execute regex*/
  char buff[255];
  while (fgets(buff, 255, fp)) {
    reti = regexec(&regex, buff, 0, NULL, 0);
    reti2 = regexec(&regex2, buff, 0, NULL, 0);
    if (reti == 0 && match == 0) {
      match = 1;
    }
    else if (reti2 == 0 && match == 1) {
      break;
    }
    else if (match == 1) {
      fprintf(stdout, "%s\n", buff);
      fflush(stdout);
    }
  }
  
  fclose(fp);

  Close(clientfd); //line:netp:echoclient:close
  exit(0);
}
