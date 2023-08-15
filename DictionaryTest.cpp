
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){
    Dictionary A;
    string s1[]={"Cattywampus","Bumfuzzle","Gardyloo","Taradiddle","Billingsgate","Snickersnee","Widdershins","Collywobbles","Conjubilant"};

    for(int x=0; x<9; x++){
        A.setValue(s1[x],x+10);

    }
    //bool truth=false;
    cout<<"size is "<<A.size()<<endl;
    cout<<A<<endl;
    if(A.contains(s1[1]))
        cout<<"contains Bumfuzzle is "<<"true"<<endl;


    cout<<"change cattywampus from 10 to 1 million"<<endl;
    A.setValue(s1[0],1000000);
    Dictionary B;
    B=A;
    cout<<"B and A are the same"<<endl;
    cout<<B<<endl;
    cout<<A<<endl;
    B.remove(s1[1]);
    cout<<"B removed Bumfuzzle"<<endl<<B<<endl;
    B.begin();
    cout<<"B set to the first key "<<B.currentKey()<<endl;
    B.end();
    cout<<"B set to the last key "<<B.currentKey()<<endl;
    B.prev();
    cout<<"Move B back "<<B.currentKey()<<endl;
    B.next();
    cout<<"move b forward and its value "<<B.currentKey() <<endl<<B.currentVal()<<endl;
	cout<<"assign B to A"<<endl;
    A=B;
    cout << "A==B is " << (A==B?"true":"false") << endl;
	cout<<"It's pre-order is"<<endl<<A.pre_string()<<endl;




    return 0;
}

