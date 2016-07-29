#include <curl-intf.h>
#include "curl/curl.h"


int curlInit () {
	curl_global_init(CURL_GLOBAL_SSL);

	return EXIT_SUCCESS;
}

int curlCleanup () {
	curl_global_cleanup();

	return EXIT_SUCCESS;
}

int curlPost (char* url, char* postData) {
	int status = EXIT_SUCCESS;
	CURL *curl;
	CURLcode res;
	struct curl_slist *headers = NULL;

	printf(">> Sending POST to %s,  post data: %s\n", url, postData);

	// Get the handle
	curl = curl_easy_init();

	// Check that the handle is okay
	if(curl) {
		// Set the header content
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");

		// Set the URL that will receive the POST
		curl_easy_setopt(curl, CURLOPT_URL, url);

		// Set headers
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		// Specify the POST data
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);

		// Perform the request, res will get the return code
		res = curl_easy_perform(curl);

		// Check for errors
		// printf(">> Post Sent via url: %s\n", url);

		if (res != CURLE_OK) {
			printf("Error: %s\n", curl_easy_strerror(res));
			status = EXIT_FAILURE;
		} 
		else {
			status = EXIT_SUCCESS;
		}

		// Cleanup
		if (headers != NULL) {
			curl_slist_free_all(headers);
		}
		curl_easy_cleanup(curl);
	}
	return status;
}

int curlGet (char* url, char* getVariable) {
	int status = EXIT_SUCCESS;
	CURL *curl;
	CURLcode res;
	struct curl_slist *headers = NULL;

	// printf(">> Sending GET to %s, get variable: %s\n", url, getVariable);

	// Get the handle
	curl = curl_easy_init();

	if(curl) {
		// Set the URL that will receive the GET
		curl_easy_setopt(curl, CURLOPT_URL, url);

		// Specify the GET data
		curl_easy_setopt(curl, CURLOPT_HTTPGET, getVariable);

		// Direct the function to print the result
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);

		// Perform the request, res will get the return code
		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			printf("Error: %s\n", curl_easy_strerror(res));
			status = EXIT_FAILURE;
		}
		else {
			status = EXIT_SUCCESS;
		}
		curl_easy_cleanup(curl);
	}
	return status;
}

size_t writeData(void *ptr, size_t size, size_t nmemb, void *userdata) {
	int status;
	size_t realSize = size *nmemb;

	// printf("%s\n", ptr);

	if (isJson(ptr, realSize) == 1) {
		status = writeJsonData(ptr);
	}
	else {
		status = writeMultipleJsonData(ptr);
	}
	return realSize;
}

int writeJsonData (char* receivedData) {
	int status = EXIT_FAILURE;
	json_object *jObj;
	json_object *innerjObj;
	json_object *returnValueNode;
	char *returnValue;
	int i;

	jObj = json_tokener_parse(receivedData);
	innerjObj = json_object_object_get(jObj, "last_value");
	returnValueNode = json_object_object_get(innerjObj, "value");
	returnValue = json_object_get_string(returnValueNode);
	printf("%s\n", returnValue);
	
}

int writeMultipleJsonData (char* receivedData) {
	// This value is just in one object called "value" (ignore last_value_)


	// int status = EXIT_FAILURE;
	// json_object *jObj;
	// struct array_list *jObjArray;
	// json_object *innerjObj;
	// json_object *returnValueNode;
	// int arrayLength;
	// char *returnValue;
	// int i;

	// printf("multiple json data\n");
	// jObj = json_tokener_parse(receivedData);
	// printf("finished tokener parse\n");
	// jObjArray = json_object_get_array(jObj);
	// printf("got the array\n");
	// printf(" length is %d\n", jObjArray->length);


	// arrayLength = json_object_array_length(jObj);
	// printf("array length: %s\n", arrayLength);


	// for (i = 0; i < (json_object_array_length - 1); i++) {
	// 	returnValue = json_object_get_string(json_object_object_get(json_object_object_get((json_object_get_array(jObj)[i]), "last_value"), "value"));
	// 	printf("%s\n", returnValue);
	// }
	return 0;
}

int isJson (char* text, int size) {
	int bJson 	= 0;
	if (size > 0 && text[0] == '{' && text[size-1] == '}') {
		bJson 	= 1;
	}
	return bJson;
}
