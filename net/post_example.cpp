//
// yum install libcurl-devel -y
// curl-config --cflags
// curl-config --libs
// g++44 -lcurl -o post_example post_example.cpp
// ./post_example
// Created by samlv on 2017/1/23.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include "curl/curl.h"

using namespace std;

static char error_buffer[CURL_ERROR_SIZE];
static int writer(char*, size_t, size_t, string*);
static bool init(CURL*&, const char*, string*, string headers[]);

static bool init(CURL*& conn, const char* url, string * p_buffer, string headers[])
{
    curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, error_buffer);
    curl_easy_setopt(conn, CURLOPT_URL, url);
    curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, writer);
    curl_easy_setopt(conn, CURLOPT_WRITEDATA, p_buffer);

    if(headers){
        struct curl_slist *chunk = NULL;
        for(int i = 0; i < sizeof(headers) / sizeof(string); i++){
            chunk = curl_slist_append(chunk, headers[i].c_str());
        }
        curl_easy_setopt(conn, CURLOPT_HTTPHEADER, chunk);
    }
    return true;
}

static int writer(char* data, size_t size, size_t nmemb, string* writer_data)
{
    unsigned long sizes = (unsigned long) (size * nmemb);

    if (NULL == writer_data)
    {
        return 0;
    }

    writer_data->append(data, sizes);

    return (int) sizes;
}

int libcurl_post(const char* url, const char* data, string& buffer, string headers[])
{
    CURL *conn = curl_easy_init();
    CURLcode code;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    if (!init(conn, url, &buffer,headers))
    {
        return -1;
    }

    code = curl_easy_setopt(conn, CURLOPT_POST, 1);

    if (code != CURLE_OK)
    {

        return -1;
    }

    code = curl_easy_setopt(conn, CURLOPT_POSTFIELDS, data);
    if (code != CURLE_OK)
    {
        return -1;
    }

    code = curl_easy_perform(conn);

    if (code != CURLE_OK)
    {
        return -2;
    }

    curl_easy_cleanup(conn);

    return 1;
}

int main() {
    string resp;
    string headers[] = {"apikey:87a8ea08-dbaa-11e6-b3f9-7056818a4db5","Content-Type:pplication/json"};
    libcurl_post("http://xxx.com",
                 "{\"interfaceName\":\"saveLog\", \"params\":{\"ips\": \"10.198.11.203\",\"operator\": \"henryjhuang\", \"logTime\": \"2017-01-23 10:05:00\", \"changeContent\": \"testing\"}}",
                 resp,headers);
    cout << resp << endl;
    return 0;
}