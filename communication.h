#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <sys/socket.h>       /*  socket definitions        */
#include <sys/types.h>        /*  socket types              */
#include <arpa/inet.h>        /*  inet (3) funtions         */
#include <unistd.h>           /*  misc. UNIX functions      */
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define debugTrace(string) printf("\n%s\n",string);
#define MAX_USR_LENGTH 		20

int ParseCmdLine(int argc, char *argv[], char **szAddress, char **szPort, char * username);
int Readline(int sockd, void *vptr, ssize_t maxlen);
ssize_t Writeline(int sockd, const void *vptr, ssize_t n);
char* parseMessage(char* buffer, int size) ;

#endif /* COMMUNICATION_H_ */

