#include <main.h>
#include <curl-intf.h>

void usage(const char* progName) {
	printf("ubidots-client: interface with the ubidots server\n");
}

int main(int argc, char** argv) {
	const char *progname;
	int 	command = 200;
	int 	ch;
	char 	*data;
	char 	*url;
	char	*data_source;
	char	*token;


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
	for (int i = 1; i < argc; i++) {
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
		curlGet(url, data);
		printf("%s values: ", data);
	}
	else if (command == UBIDOT_COMMAND_GET_ALL) {
		sprintf(url, UBIDOTS_GET_ALL_URL, UBIDOTS_URL, data_source, data, token);
		curlGet(url, data);
		printf("%s value: ", data);
	}

	// close the curl guy
	curlCleanup();

	// clean-up
	free(data);
	free(url);
	// free(data_source);
	// free(token);

	return 0;
}


size_t writeData(void *ptr, size_t size, size_t nmemb, void *userdata) {
	int status;
	size_t realSize = size *nmemb;

	if (isJson(ptr, realSize) == 1) {
		status = processWriteData(ptr);
	}
	return realSize;
}

int processWriteData (char* receivedData) {
	int status = EXIT_FAILURE;
	char cmd[STRING_LENGTH];
	json_object *jObj;
	char returnValue;

	pthread_t pth;
	pthread_attr_t attr;

	jObj = json_tokener_parse(receivedData);

	if (jObj != NULL) {
		returnValue = json_object_get_string(json_object_object_get(new_obj, "value"));
	}
	printf("%s\n", returnValue)
}

