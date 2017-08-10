#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include "actions.h"
#include <map>
#include <fstream>
#include "string_help.h"
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <unistd.h>

using namespace std;
using namespace boost::algorithm;

// 
// template <class T>
// class DisnableCompare {
// public :
// 	int operator()(const T & x, const T &y) const {
// 		return -1;
// 	}
// };

bool hosts_format(string & hostfile)
{
	// > > 而不是 >>
	// map<string,string,DisnableCompare<string> > hostMap;
	map<string,string> hostMap;
	ifstream in(hostfile.c_str(), ios::in);
	if( ! in.is_open()){
		cerr << "oepn file error : " << hostfile << endl;	
		return 0;
	}
	string line;
	while( ! in.eof()){
		getline(in,line);
		line = lstring::trim(line);
		if( line.empty() || '#' == line[0] ) {
			continue;
		}
		vector<string> line_exp;
		split(line_exp,line,is_any_of(" \t"));		
		if(line_exp.size() < 2){
			continue;
		}
		// cout << line << endl;
		ostringstream oss ;
		for(int i = 1; i < line_exp.size(); i ++ ){
			oss << line_exp[i] << " ";	
		}
		string domain = oss.str();
		trim(domain);	
		hostMap[domain] = line_exp[0] ;
		line.clear();		
	}
	in.close();

	for (map<string,string>::iterator it = hostMap.begin();
		it != hostMap.end(); it ++){
		string domain = it->first;
		string ip = it->second;
		cout << left << setw(16) << ip << "\t\t" << domain << endl;
	}	

	return 1;
}


bool hosts_clear(string & hostfile){
	char hostname[100];
	gethostname(hostname,100);
	ofstream out(hostfile.c_str(), ios::out);
	if ( ! out.is_open()){
		cerr << "open file error : " << hostfile << endl;
		return 0;
	}
	out << left << setw(16) << "127.0.0.1" << "\t\t" << "localhost  localhost.localdomain " << hostname << endl;
	out << left << setw(16) << "::1" << "\t\t" 
		<< "localhost localhost.localdomain localhost6 localhost6.localdomain6" << endl;	
	out.close();
	return 1;	
}
