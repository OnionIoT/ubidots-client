#include <ubidots.h>
#include "curl/curl.h"

int main(int argc, char** argv) {
	int 	command;
	char 	*data;
	char 	*url;

	// allocate memory
	data = malloc(STRING_LENGTH * sizeof *data);
	url = malloc(STRING_LENGTH * sizeof *url);

	for (int i = 1; i < argc; i++) {
		// if (argv[i] == "-t")
		// 	UBIDOTS_TOKEN = argv[i+1];
		// else if (argv[i] == "-d")
		// 	UBIDOTS_DATA_SOURCE = argv[i+1];
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
	}

	curlInit();

	if (command == UBIDOT_COMMAND_SET) {
		// craft the url
		sprintf(url, "%s/%s?token=%s", UBIDOTS_URL, UBIDOTS_DATA_SOURCE, UBIDOTS_TOKEN);

		curlPost(url, UBIDOTS_VARIABLE_DATA);
	}

	// close the curl guy
	curlCleanup();

	// clean-up
	free(data);
	free(url);


	return 0;
}