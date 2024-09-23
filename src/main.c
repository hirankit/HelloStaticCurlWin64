#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#ifdef _WIN32
#include <windows.h>
#endif

// Struct to hold the dynamic buffer
struct MemoryStruct {
    char *memory;
    size_t size;
};

// Callback function to write data
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp; // Typecast the generic pointer to the struct type

    char *ptr = realloc(mem->memory, mem->size + total_size + 1);
    if(ptr == NULL) {
        // Out of memory
        fprintf(stderr, "Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, total_size);
    mem->size += total_size;
    mem->memory[mem->size] = '\0';  // Null-terminate the string

    return total_size;
}

int main() {
#ifdef _WIN32
    // Set console code page to UTF-8
    SetConsoleOutputCP(CP_UTF8);
#endif

    CURL *curl;
    CURLcode res;
    long response_code;
    char *url = "https://example.com";

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);  // Initial allocation - C standard doesn't gaurantee malloc(0) to return NULL or a unique pointer
    chunk.memory[0] = '\0';     // Empty string
    chunk.size = 0;            // No data at this point

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        printf("こんにちは, CURL initialized.\n"); // Debug print

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow HTTP 301 redirects

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Get the HTTP response code
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            printf("HTTP Response Code: %ld\n", response_code);
            // Print the HTML content
            printf("HTML Content:\n%s\n", chunk.memory);
        }

        curl_easy_cleanup(curl);
        free(chunk.memory);
    } else {
        fprintf(stderr, "Failed to initialize CURL.\n");
    }

    curl_global_cleanup();
    return 0;
}