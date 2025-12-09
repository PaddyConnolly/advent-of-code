#ifndef GET_H
#define GET_H

#include <string>

size_t write_callback(void* data, size_t size, size_t nmemb, void* userp);
std::string get(const std::string& url, const std::string& session_cookie, std::string& output);

#endif
