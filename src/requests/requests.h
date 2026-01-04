#pragma once
#include <curl/curl.h>
#include <string>
#include <vector>

extern CURL* curl;

struct GetResponse {
    std::string html;
};

GetResponse SendGet(std::string url);