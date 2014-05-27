/*
 * communication.c
 *
 *  Created on: Apr 24, 2014
 *      Author: tbn
 */

#include "communication.h"

/*Create unparsed method*/
/*get read line standard*/


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

//	//data to read
	unsigned char start;
	unsigned char src[4];
	unsigned char dst[4];
	unsigned char size;
	unsigned char data[20];

//	read(sockd, &start, 1);
//	if (start == 0xFE) {
//		read(sockd,&size,1);
//		//size in bytes
//		if(size > 0){//10Mo, msg
//			read(sockd, vptr, size);
//			fclean(sockd);
//		}
//		else { // files
//			//attention bug ! client envoie coucou trouve un fichier
//			debugTrace("Cannot read the message size or = to 0.\n")
//			return -1;
//		}
//	}
//	else {
//		printf("Not a starting sequence\n");
//		return 0;
//	}
//	return size;

//	unsigned char start = ctx->messageToReceive[0];
	//	unsigned char size = ctx->messageToReceive[1];
	//
	//	if (start == 0xFE) {
	//	//			read(sockd,src,4);
	//	//			read(sockd,dst,4);
	//	//size in bytes
	//		if(size < 10000000){//10Mo, msg
	//			debugTrace("You got a message\n");
	//			printf("%s\n",ctx->messageToReceive);
	//			doAction((unsigned char*)ctx->messageToReceive+2,&(ctx->messageToSend));
	//		}
	//		else { // files
	//			//attention bug ! client envoie coucou trouve un fichier
	//			debugTrace("You got a file\n");
	//		}
	//	}
	//	else {
	//		debugTrace("This is not a valid sequence\n");
	//	}
	//	return 1;



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
	s = malloc(size*sizeof(char) + 2);
//	s[0]=0xFE;
//	s[0]=strlen(buffer);
	strcat(s,buffer);
	s[strlen(buffer)] = '\0';

	return s;
}





