#ifndef _CURL_COMMUNICATION_H_
#define _CURL_COMMUNICATION_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ubidots-types.h>


#include "json-c/json.h"


// lazar: debug
// #include <time.h>


int 			curlInit				();
int 			curlCleanup				();

int  			curlPost				(char* url, char* postData);
int 			curlGet					(char* url, char* getVariable);
size_t 			writeData 				(void *ptr, size_t size, size_t nmemb, void *userdata);
int 			writeMultipleJsonData 	(char* receivedData);
int 			processWriteData		(char* receivedData);

#endif // _CURL_COMMUNICATION_H_ 

