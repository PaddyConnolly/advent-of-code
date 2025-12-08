#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>
#include <cmath>

size_t write_callback(void* data, size_t size, size_t nmemb, void* userp) {
  size_t totalSize = size * nmemb;
  std::string* str = static_cast<std::string*>(userp);
  str->append(static_cast<char*>(data), totalSize);
  return totalSize;
}

int safecrack(std::string& instructions) {
  std::istringstream stream(instructions);
  std::string line;
  int dial = 50;
  int zeroes = 0;
  while (std::getline(stream, line)) {
    int move = std::stoi(line.substr(1));
    int direction = line[0];
    if (direction == 'L') {
      dial -= move;

    } else {
      dial += move;

    }
    if (dial % 100 == 0) zeroes++;
  }

  stream.clear();
  stream.seekg(0);
  
  std::cout << "Old Password: " << zeroes << std::endl;
  
  dial = 50;
  zeroes = 0;
  while (std::getline(stream, line)) {
    // Handle full rotations, bound move 0<=m<=99
    int move = std::stoi(line.substr(1));
    zeroes += move / 100;
    move = move % 100;

    // If we land on the same spot, just count rotations and move on
    if (move == 0) continue;

    int prev = dial;
    int direction = line[0];
    if (direction == 'L') {
      dial -= move;
      if (dial < 0) dial += 100;
      // If dial has moved left but is bigger than previous, we must've crossed 0, also check if we landed on zero
      if ((prev != 0 && dial > prev) || dial == 0) zeroes++;
    } else {
      dial += move;
      if (dial > 99) dial -= 100;
      if ((prev != 0 && dial < prev) || dial == 0) zeroes++;
    }

  }
  std::cout << "New Password: " << zeroes << std::endl;
  return 1;
}

int fetchURL (const std::string& url, std::string& session_cookie, std::string& output) {
  CURL* curl;
  CURLcode res;

  curl = curl_easy_init();
  if (!curl) {
    std::cerr << "Error: Failed to initialise CURL" << std::endl;
    return false;
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
    return false;
  }

  long response_code;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

  if (response_code != 200) {
    std::cerr << "Warning: HTTP response code: " << response_code << std::endl;
  }

  curl_easy_cleanup(curl);

  return true;

}

int main (int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << std::endl;
    std::cerr << "Example: " << argv[0] << std::endl;
    return 1;
  }
  
  std::string url = argv[1];
  std::string content;
  std::string session_cookie = argv[2];

  curl_global_init(CURL_GLOBAL_DEFAULT);

  if (fetchURL(url, session_cookie, content)) {
    safecrack(content);
  } else {
    std::cerr << "Failed to fetch URL" << std::endl;
    curl_global_cleanup();
    return 1;
  }

  curl_global_cleanup();
  
  return 0;
}
