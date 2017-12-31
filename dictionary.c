#include "csapp.h"
#include <stdio.h>

int main(void) {
  char *buf, *p;
  char arg1[MAXLINE], content[MAXLINE];
  int clientfd;

  /*get input from user*/
  if ((buf = getenv("QUERY_STRING")) != NULL) {
    strcpy(arg1, buf);
    printf(content, "got here");
  }

  /*open a connection with the dictionary api in order to get the definition*/

  clientfd = (Open_clientfd(ada.stern.net, 1776));
  Rio_readiinitb(&rio, clientfd);


}
