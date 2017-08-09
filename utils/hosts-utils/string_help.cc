#include "string_help.h"
#include <string>

using namespace std;

string trim(const string & str,const string chs = "\r\n\t\0"){
	if ( str.empty() ) {
		return str;
	}
  	for (string::iterator it=str.begin() ; it < str.end(); it++ ){
		string::size_type pos = str.find_first_not_of( * it);	
		if ( pos == string::n_pos ) {
				
		}
	}
	
}
