#ifndef EMAIL_H
#define EMAIL_H
#include<iostream>
#include"Document.h"
using namespace std;

class Email :public Document {
private:
	string sender;
	string recipient;
	string title;
public:
	Email() { sender = ""; recipient = ""; title = ""; }
	Email(string t,string s, string r, string ti):Document(t) {
		sender = s; recipient = r; title = ti; 
	}
	void operator=(const Email& e) {
		setText(e.getText());
		//cout << "email == " << endl;
		sender = e.sender;
		recipient = e.recipient;
		title = e.title;
	}
	string getSender()const { return sender; }
	string getRecipient()const { return recipient; }
	string getTitle()const { return title; }
};



#endif // !EMAIL_H
