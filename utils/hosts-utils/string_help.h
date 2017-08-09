#ifndef __STRING_HELP_H_
#define __STRING_HELP_H_

#include <string>
using namespace std;

string trim(const string & str,const string chs = "\r\n\t\0");
int split(const string & str,vector<string> ret,string dim = " ");

#endif // __STRING_HELP_H_
