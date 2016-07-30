#include <main.h>
#include "curl/curl.h"

void usage(const char* progName) {
	printf("ubidots-client: interface with the ubidots server\n");
	// clement: add instructions on using the set and get commands
}

int main(int argc, char** argv) {
	const char *progname;
	int 	command = 200;
	int 	ch;
	char 	*data;
	char 	*url;
	char	*data_source;
	char	*token;
	int 	i;


	// allocate memory
	data 				= malloc(STRING_LENGTH * sizeof *data);
	url 				= malloc(STRING_LENGTH * sizeof *url);
	data_source 		= malloc(STRING_LENGTH * sizeof *data_source);
	token 				= malloc(STRING_LENGTH * sizeof *token);

	progname = argv[0];

	while ((ch = getopt(argc, argv, "d:t:")) != -1) {
		switch (ch) {
		case 'd':	
			data_source = optarg;
			break;
		case 't':
			token = optarg;
			break;
		default:
			usage(progname);
			return 0;
		}
	}
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i],"set") == 0) {
			if (argc > i) {
				strcpy(data, argv[i+1]);
			}
			command = UBIDOT_COMMAND_SET;
		}
		else if (strcmp(argv[i],"get") == 0) {
			if (argc > i) {
				strcpy (data, argv[i+1]);
			}
			command = UBIDOT_COMMAND_GET;
		}
		else if (strcmp(argv[i], "get-all") == 0) {
			if (argc > i) {
				strcpy (data, argv[i+1]);
			}
			command = UBIDOT_COMMAND_GET_ALL;
		}
	}

	curlInit();

	// craft the url
	if (command == UBIDOT_COMMAND_SET) {
		sprintf(url, UBIDOTS_POST_URL, UBIDOTS_URL, data_source, token);
		curlPost(url, data);
	}
	else if (command == UBIDOT_COMMAND_GET) {
		sprintf(url, UBIDOTS_GET_URL, UBIDOTS_URL, data_source, data, token);
		printf("Last %s value: ", data);
		curlGet(url, data);
	}
	else if (command == UBIDOT_COMMAND_GET_ALL) {
		sprintf(url, UBIDOTS_GET_ALL_URL, UBIDOTS_URL, data_source, data, token);
		printf("%s values: ", data);
		curlGet(url, data);
	}

	printf("Done!\n");

	// close the curl guy
	curlCleanup();

	// clean-up
	free(data);
	free(url);
	// free(data_source);
	// free(token);

	return 0;
}

