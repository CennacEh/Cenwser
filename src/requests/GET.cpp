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
    GetResponse response;
    CURL* curl;
    curl = curl_easy_init();
    if (!curl) {
        ShowError("Failed to initalize Curl!");
    }
    std::cout << url.c_str() << std::endl;
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
    headers = curl_slist_append(headers, "Accept-Language: en-US,en;q=0.9");
    std::string userAgent = "User-Agent: Cenwser/0.1 (" + os + ")";
    headers = curl_slist_append(headers, userAgent.c_str());
    headers = curl_slist_append(headers, "Connection: keep-alive");
    headers = curl_slist_append(headers, "Upgrade-Insecure-Requests: 1");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_CAINFO, "resources/curl-ca-bundle.crt");


    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.html);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) response.html = curl_easy_strerror(res);
    std::cout << response.html << std::endl;
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return response;
}