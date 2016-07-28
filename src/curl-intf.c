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
		printf(">> Post Sent via url: %s\n", url);

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

	printf(">> Sending GET to %s, get variable: %s\n", url, getVariable);

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
