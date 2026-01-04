#include <iostream>
#include <curl/curl.h>
#include "requests.h"
#include "../other/other.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total = size * nmemb;
    std::string* str = (std::string*)userp;
    str->append((char*)contents, total);
    return total;
}


GetResponse SendGet(std::string url) {
    std::cout << "Attempting to send" << std::endl;
    GetResponse response;
    CURL* curl;
    curl = curl_easy_init();
    if (!curl) {
        ShowError("Failed to initalize Curl!");
    }
    std::cout << url.c_str() << std::endl;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_CAINFO, "resources/curl-ca-bundle.crt");


    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.html);
    CURLcode res = curl_easy_perform(curl);
    std::cerr << "curl failed: " << curl_easy_strerror(res) << std::endl;
    std::cout << response.html << std::endl;
    curl_easy_cleanup(curl);
    return response;
}