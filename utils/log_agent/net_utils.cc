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

char error_buffer[CURL_ERROR_SIZE]; 
int writer(char*, size_t, size_t, string*);
void init(CURL*&, const char*, string*, string headers[]);

int writer(char* data, size_t size, size_t nmemb, string* writer_data)
{
    unsigned long sizes = (unsigned long) (size * nmemb);

    if (NULL == writer_data)
    {
        return 0;
    }

    writer_data->append(data, sizes);

    return (int) sizes;
}

void init(CURL*& conn, const char* url, string * p_buffer, string headers[])
{
    curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, error_buffer);
    curl_easy_setopt(conn, CURLOPT_URL, url);
    curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, writer);
    curl_easy_setopt(conn, CURLOPT_WRITEDATA, p_buffer);

    if(headers){
        struct curl_slist *chunk = NULL;
        for(int i = 0; i < (sizeof(headers) / sizeof(string)); i++){
            chunk = curl_slist_append(chunk, headers[i].c_str());
        }
        curl_easy_setopt(conn, CURLOPT_HTTPHEADER, chunk);
    }
}

void libcurl_post(const char* url, const char* data, string& buffer, string headers[])
{
    CURL *conn = curl_easy_init();
    curl_global_init(CURL_GLOBAL_DEFAULT);

    init(conn, url, &buffer,headers);

    curl_easy_setopt(conn, CURLOPT_POST, 1);

    curl_easy_setopt(conn, CURLOPT_POSTFIELDS, data);

    curl_easy_perform(conn);

    curl_easy_cleanup(conn);
}

void libcurl_get(const char* url, string& buffer,string headers[] )
{
    CURL *conn = curl_easy_init();

    curl_global_init(CURL_GLOBAL_DEFAULT);

    init(conn, url, &buffer,headers);

    curl_easy_perform(conn);

    curl_easy_cleanup(conn);
}

