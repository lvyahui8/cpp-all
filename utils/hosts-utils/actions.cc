#include <cstdio>
#include <iostream>
#include <string>
#include "actions.h"
#include <map>
#include <fstream>
#include "string_help.h"

using namespace std;

bool hosts_format(string & hostfile)
{
	map<string,string> hostMap;
	ifstream in(hostfile.c_str(), ios::in);
	if( ! in.is_open()){
		cerr << "oepn file error : " << hostfile << endl;	
		return 0;
	}
	string line;
	while( ! in.eof()){
		getline(in,line);
		line = trim(line);
		if( ! line.empty()) {
			cout << line << endl;		
		}
		line.clear();		
	}
	in.close();
	return 1;
}
