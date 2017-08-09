#include <cstdio>
#include <tclap/CmdLine.h>
#include "actions.h"

#define ACTION_FORMAT "format"
#define ACTION_CLEAN "clean"

using namespace std;
using namespace TCLAP;


template<class T> 
string toString(const T & t){
	ostringstream oss; 
	oss<<t;
	return oss.str();   
}

template <class T>  
T stringToNumber(const std::string & str){  
	istringstream iss(str);  
	T num;  
	iss >> num;  
	return num;      
}  

int main(int argc ,char * argv []){
	CmdLine cmd("hosts file tools",' ',"1.0");

	vector<string> actionAllowed;

	actionAllowed.push_back(ACTION_FORMAT);
	actionAllowed.push_back(ACTION_CLEAN);

	ValuesConstraint<string> allowedActions(actionAllowed);

	ValueArg<string> actionArg("a","action","excute action",false, ACTION_FORMAT,& allowedActions);

	cmd.add(actionArg);

	ValueArg<string> fileArg(
		"f", //  参数标志
		"file",// 参数名
		"hosts file path", // 详细介绍
		false,	// 是否必须
		"/etc/hosts", // 默认值
		"std::string", // 参数类型
		cmd
		);

	SwitchArg uniqSw(
		"u", // 选项标志
		"uniq", // 选项名
		"distinct same item",// 选项说明
		cmd,
		false // 默认值
		);

	try{	
		
		cmd.parse(argc,argv);

	} catch(ArgException &e){
		cerr << "errro:" << e.error() << " for argument " << e.argId() << endl;
	}

	string action = actionArg.getValue();
	string hostfile = fileArg.getValue();

	if (action.compare(ACTION_FORMAT) == 0)
	{
		hosts_format(hostfile);
	}

	//getchar();
	return 0;
}

