#ifndef DOCUMENT_H
#define DOCUMENT_H
#include<iostream>
using namespace std;

class Document{
private:
	string text;
public:
	Document() { text = ""; }
	Document(string s) { text = s; }
	void operator=(const Document& d) {
		//cout << "text==           " << text << " = " << d.text << endl;
		this->text = d.text; }
	string getText() const{ return text; }
	void setText(string t) { text = t; }
};



#endif // !DOCUMENT_H
