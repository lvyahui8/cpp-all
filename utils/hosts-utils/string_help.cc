#include "string_help.h"
#include <string>

using namespace std;

string trim(const string & str,const string chs){
	if ( str.empty() ) {
		return str;
	}
	string tmp=str;
  	for ( string::const_iterator it = chs.begin() ; 
			it < chs.end(); it++ ){
		string::size_type first_pos = tmp.find_first_not_of( * it);	
		if ( first_pos == string::npos ) {
				return "";
		}
		
		string::size_type last_post = tmp.find_last_not_of( * it);

		if (last_post != string::npos ){
			tmp = tmp.substr(first_pos,last_post - first_pos + 1);
		}

		tmp = tmp.substr(first_pos);
	}
	return str;
}


int split(const string & str,vector<string> ret,string dim  ){
	return 0;
}
