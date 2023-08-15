#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"
#include <fstream>
using namespace std;

int main(int argc, char** argv){
	if(argc!=3){
		fprintf(stdout,"bad number of inputs");
		exit(1);
		

	}
	string filez(argv[1]);
	string filez2(argv[2]);
	ifstream fp;
	ofstream outfp;
	fp.open(filez);
	outfp.open(filez2);
	string hold;
	int value=0;
	Dictionary D;
	while(getline(fp,hold)){
		value+=1;
		//cout<<hold<<endl;
		D.setValue(hold,value);
		hold.clear();
	
	}
	string s1=D.pre_string();
	outfp<<D<<endl;
	outfp<<s1;
	return 0;

}

