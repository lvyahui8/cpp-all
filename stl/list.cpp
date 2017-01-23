#include <iostream>
#include <list>

using namespace std;

void testIterators(){
    list<string> names ;
    list<string>::iterator it;
    names.push_back("hello");
    names.push_back("stl");

    for(it = names.begin(); it != names.end(); it ++){
        cout << * it << " ";
    }
    cout << endl;
}

void testCapacity(){
    list<string> names;
    if(names.empty()){
        cout << stderr << " is empty" << endl << flush;
    }
    names.push_back("lv");
    names.push_back("yahui");

    cout << "size :" << names.size() << endl;
    cout << "max_size:" << names.max_size() << endl;
}


int main()
{
    testIterators();
    testCapacity();
    return 0;
}
