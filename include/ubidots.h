#ifndef _UBIDOTS_H_
#define _UBIDOTS_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


#define STRING_LENGTH		256
#define buffer_length		1024


// macros for communicating with ubidots
#define UBIDOTS_URL 			"http://things.ubidots.com/api/v1.6/devices"



// temporary for testing
#define UBIDOTS_TOKEN 			"8KfVzRUMD9hYk33A1H1dw1j1oUZVWy"
#define UBIDOTS_DATA_SOURCE		"health-monitor"
#define UBIDOTS_VARIABLE_NAME	"Temperature"
#define UBIDOTS_VARIABLE_DATA	"{\"temperature\":50, \"humidity\":20}"


typedef enum e_ubidotClientCommands {
	UBIDOT_COMMAND_SET 		= 0,
	UBIDOT_COMMAND_GET,
	UBIDOT_NUM_COMMANDS
} eUbidotClientCommands;


#endif // _UBIDOTS_H_ 

