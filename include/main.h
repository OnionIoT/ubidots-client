#ifndef _UBIDOTS_MAIN_H_
#define _UBIDOTS_MAIN_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>


#define STRING_LENGTH			256
#define buffer_length			1024


// macros for communicating with ubidots
#define UBIDOTS_URL 			"http://things.ubidots.com/api/v1.6/devices"
#define UBIDOTS_POST_URL		"%s/%s?token=%s"
#define UBIDOTS_GET_URL			"%s/%s/%s/?&token=%s"
#define UBIDOTS_GET_ALL_URL		"%s/%s/%s/values/?token=%s"


typedef enum e_ubidotClientCommands {
	UBIDOT_COMMAND_SET 			= 0,
	UBIDOT_COMMAND_GET,
	UBIDOT_COMMAND_GET_ALL,
	UBIDOT_NUM_COMMANDS
} eUbidotClientCommands;


#endif // _UBIDOTS_H_ 