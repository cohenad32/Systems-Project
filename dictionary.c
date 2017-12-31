#include "csapp.h"
#include <stdio.h>

int main(void) {
  char *buf, *p;
  char arg1[MAXLINE], content[MAXLINE];
  int clientfd;
  char str[MAXLINE];
  char word[MAXLINE];
  char string[MAXLINE];
  char *rio;

  /*get input from user*/
  if ((buf = getenv("QUERY_STRING")) != NULL) {
  }

  /*open a connection with the dictionary api in order to get the definition*/

  clientfd = (Open_clientfd("services.aonaware.com", "80"));
  Rio_readiinitb(&rio, clientfd);

  strcpy(str, "/DictService/DictService.asmx/Define?");
  strcat(str, buf);

      /* Make the response body */
  sprintf(content, buf);
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
