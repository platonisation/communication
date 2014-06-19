/*
 * communication.c
 *
 *  Created on: Apr 24, 2014
 *      Author: tbn
 */

#include "communication.h"


/*  Write a line to a socket  */

ssize_t Writeline(int sockd, const void *vptr, ssize_t n) {
	ssize_t      nleft;
    ssize_t     nwritten;
    const char *buffer;

    buffer = vptr;
    nleft  = n;

    while ( nleft > 0 ) {
	if ( (nwritten = write(sockd, buffer, nleft)) <= 0 ) {
	    if ( errno == EINTR )
		nwritten = 0;
	    else
		return -1;
	}
	nleft  -= nwritten;
	buffer += nwritten;
    }

    return n;
}


/*  Read a line from a socket  */

int Readline(int sockd, void *vptr, ssize_t maxlen) {

	 ssize_t n, rc;
	    char    c, *buffer;

	    buffer = vptr;

	    for ( n = 1; n < maxlen; n++ ) {

			if ( (rc = read(sockd, &c, 1)) == 1 ) {
				*buffer++ = c;
				if ( c == '\0' )
					break;
			}
			else if ( rc == 0 ) { //timeout
				if ( n == 1 )
					return 0;
				else
					buffer[maxlen-1] = '\0';
					//return -2;
			}
			else {
				if ( errno == EINTR )
					continue;
				return -1;
			}
	    }

	    *buffer = 0;
	    return n;


}

char* parseMessage(char* buffer, int size) {
	char* s;
	s = malloc(size+1*sizeof(char));
	memset(s,0,size+1);
	strcat(s,buffer);
	s[size] = '\0';
	return s;
}





