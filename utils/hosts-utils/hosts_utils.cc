#include <cstdio>
#include <tclap/CmdLine.h>

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

	cout << "hosts file :" << fileArg.getValue() << endl;
	cout << "uniq :" << uniqSw.getValue() << endl;

	//getchar();
	return 0;
}

