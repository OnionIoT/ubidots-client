#ifndef _CURL_COMMUNICATION_H_
#define _CURL_COMMUNICATION_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


// #include "json-c/json.h"


// lazar: debug
// #include <time.h>


int 			curlInit		();
int 			curlCleanup		();


int  			curlPost		(char* url, char* postData);
int 			curlGet			(char* url, char* getVariable);

#endif // _CURL_COMMUNICATION_H_ 

