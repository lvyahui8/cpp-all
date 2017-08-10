#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;
int main(int argc , char * argv [] ){	
	string s(" lvyahui ");
	trim(s);
	cout << s << endl;	
	return 0;
}
