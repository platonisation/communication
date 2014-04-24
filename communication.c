/*
 * communication.c
 *
 *  Created on: Apr 24, 2014
 *      Author: tbn
 */

#include "communication.h"

/*Create unparse methode*/
/*recuperer read line standrad*/


/*  Write a line to a socket  */

ssize_t Writeline(int sockd, const void *vptr, size_t n) {
    size_t      nleft;
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

int Readline(int sockd, char* buffer, size_t maxlen) {

	//data to read
	unsigned char start;
	unsigned char src[4];
	unsigned char dst[4];
	unsigned char size;
	unsigned char data[20];

	//treat data
	read(sockd, &start, 1);
	if (start == 0xFE) {
//			read(sockd,src,4);
//			read(sockd,dst,4);
		read(sockd,&size,1);
		printf("size:%d\n",size);
		//size in bytes
		if(size < 10000000){//10Mo, msg
			if((read(sockd,buffer,size) != size)){
				//Lecture ok
				printf("Cannot read %d datas\n",size);
			}
			else {
				printf("%s",buffer);
				doAction(buffer,size);
			}

		}
		else { // files
			//attention bug ! client envoie coucou trouve un fichier
			printf("This is a file\n");
		}
	}
	else {
		printf("Not a starting sequence\n");
	}
	return 1;
}

char* parseMessage(char* buffer, int size) {
	char* s;
	s = malloc(size*sizeof(char) + 2);
	s[0]=0xFE;
	s[1]=strlen(buffer);
	strcat(s,buffer);

	return s;
}





