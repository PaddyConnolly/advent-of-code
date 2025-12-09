#include "get.h"
#include <iostream>
#include <curl/curl.h>

size_t write_callback(void* data, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* str = static_cast<std::string*>(userp);
    str->append(static_cast<char*>(data), totalSize);
    return totalSize;
}
std::string get (const std::string& url, const std::string& session_cookie, std::string& output) {
  CURL* curl;
  CURLcode res;

  curl = curl_easy_init();
  if (!curl) {
    std::cerr << "Error: Failed to initialise CURL" << std::endl;
    return "Error";
  }


  std::string cookie = "session=" + session_cookie;
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); 
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "001/1.0");
  curl_easy_setopt(curl, CURLOPT_COOKIE, cookie.c_str());

  res  = curl_easy_perform(curl);

  if (res != CURLE_OK) {
    std::cerr << "Error: curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    curl_easy_cleanup(curl);
    return "Error";
  }

  long response_code;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

  if (response_code != 200) {
    std::cerr << "Warning: HTTP response code: " << response_code << std::endl;
  }

  curl_easy_cleanup(curl);

  return output;

}

