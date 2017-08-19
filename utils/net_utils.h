#ifndef __NET_UTILS_H_
#define __NET_UTILS_H_
#include <string>
using namespace std;

void libcurl_post(const char* url, const char* data, string& buffer, string headers[]);
void libcurl_get(const char* url, string& buffer,string headers[] );

#endif //__NET_UTILS_H_
