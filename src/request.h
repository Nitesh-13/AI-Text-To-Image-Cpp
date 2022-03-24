#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>
using namespace std;


#ifndef REQUEST_H
#define REQUEST_H

class Request {
public:
    Request() {
        curl_ = curl_easy_init();
        if (!curl_) {
            cerr << "[Error] Failed to initialize libcurl." << endl;
        }
    }

    ~Request() {
        if (curl_) {
            curl_easy_cleanup(curl_);
        }
    }

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
        size_t totalSize = size * nmemb;
        output->append(static_cast<char*>(contents), totalSize);
        return totalSize;
    }

    bool post(const string& apiUrl, const string& postData, string& responseData, const string& authToken) {
        if (!curl_) {
            cerr << "[Error] libcurl is not initialized." << endl;
            return false;
        }

        curl_easy_setopt(curl_, CURLOPT_URL, apiUrl.c_str());

        curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, postData.c_str());

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + authToken).c_str());
        curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &responseData);

        CURLcode res = curl_easy_perform(curl_);
        if (res != CURLE_OK) {
            cerr << "[Error] Failed to send POST request: " << curl_easy_strerror(res) << endl;
            return false;
        }

        curl_slist_free_all(headers);

        return true;
    }

private:
    CURL* curl_;
};


#endif