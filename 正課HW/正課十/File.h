#ifndef FILE_H
#define FILE_H
#include<iostream>
#include"Document.h"
using namespace std;

class File :public Document {
private:
	string pathname;
public:
	File() { pathname = ""; }
	File(string t, string p) :Document(t) {
		pathname = p;
	}
	void operator=(File& f) {
		setText(f.getText());
		//cout << "file==           "<<pathname<<" = "<<f.pathname << endl;
		pathname = f.pathname;
	}
	void setPathname(string p) { pathname = p; }
	string getPathname ()const{ return pathname; }

};



#endif // !FILE_H
