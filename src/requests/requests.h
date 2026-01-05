#pragma once
#include <curl/curl.h>
#include <string>
#include <vector>

#if defined(_WIN32) || defined(_WIN64)
    std::string os = "Windows NT 10.0";
#elif defined(__APPLE__) || defined(__MACH__)
    std::string os = "Macintosh; Intel Mac OS X 13_5_1";
#elif defined(__linux__)
    std::string os = "X11; Linux x86_64";
#else
    std::string os = "Unknown";
#endif

extern CURL* curl;

struct GetResponse {
    std::string html;
};

GetResponse SendGet(std::string url);