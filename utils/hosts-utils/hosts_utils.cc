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
		"f", //  ������־
		"file",// ������
		"hosts file path", // ��ϸ����
		false,	// �Ƿ����
		"/etc/hosts", // Ĭ��ֵ
		"std::string", // ��������
		cmd
		);

	SwitchArg uniqSw(
		"u", // ѡ���־
		"uniq", // ѡ����
		"distinct same item",// ѡ��˵��
		cmd,
		false // Ĭ��ֵ
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

