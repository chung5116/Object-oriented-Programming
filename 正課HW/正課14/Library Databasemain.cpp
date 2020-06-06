//Name: b10706009 張永承
//data: 2020/06/04
//last update: 2020/06/06
//problem subject: Library Database
#include <iostream>
#include<vector>
#include<sstream>
#include<set>	
#include<string>
#include<algorithm>
using namespace std;

class Book {
private:
public:
	string title;
	string author;
	set<string>editions;
	Book(string t, string a, string e) :title(t), author(a) { editions.insert(e); }

};


vector<string>splitString(string buffer, char s);
void insert(string title, string author, string edition, vector<Book>& book);
void deleteEdition(string title, string author, string edition, vector<Book>& book);
void deleteBook(string title, string author, vector<Book>& book);
void findBook(string title, string author, vector<Book>& book);
void findAuthor(string author, vector<Book>& book);
void sortByTitle(vector<Book>& book);
void sortByAuthor(vector<Book>& book);
bool sortByTitle2(Book& a, Book& b);
bool sortByAuthor2(Book& a, Book& b);

void incomplete() {
	cout << "Incomplete Command.\n";
}


int main() {
	string command;
	vector<Book>book;
	while (cin >> command) {
		if (command == "Insert") {
			char comma;
			string title;
			string author;
			int edition;
			// ' " '
			cin >> comma;
			if (comma != '"') {
				cout << "Incomplete Command.\n";
				continue;
			}
			// Harry"
			getline(cin, title, '"');
			cin >> comma;
			if (comma != '"') {
				cout << "Incomplete Command.\n";
				continue;
			}
			// JK"
			getline(cin, author, '"');
			cin >> edition;
			string seditions = to_string(edition);
			insert(title, author, seditions, book);
		}
		else if (command == "Find") {
			string type;
			char comma;
			string title;
			string author;
			cin >> type;
			if (type == "Book") {
				// ' " '
				cin >> comma;
				if (comma != '"') {
					cout << "Incomplete Command.\n";
					continue;
				}
				// Harry"
				getline(cin, title, '"');
				cin >> comma;
				if (comma != '"') {
					cout << "Incomplete Command.\n";
					continue;
				}
				// JK"
				getline(cin, author, '"');
				findBook(title, author, book);
			}
			else if (type == "Author") {
				// ' " '
				cin >> comma;
				if (comma != '"') {
					cout << "Incomplete Command.\n";
					continue;
				}
				// Unknown"
				getline(cin, author, '"');
				findAuthor(author, book);
			}
			else {
				cout << "Incomplete Command.\n";
				continue;
			}
		}
		else if (command == "Delete") {
			string type;
			char comma;
			string title;
			string author;
			int edition;
			cin >> type;
			if (type == "Edition") {
				// ' " '
				cin >> comma;
				if (comma != '"') {
					cout << "Incomplete Command.\n";
					continue;
				}
				// Harry"
				getline(cin, title, '"');
				cin >> comma;
				if (comma != '"') {
					cout << "Incomplete Command.\n";
					continue;
				}
				// JK"
				getline(cin, author, '"');
				cin >> edition;
				string sedition = to_string(edition);
				deleteEdition(title, author, sedition, book);
			}
			else if (type == "Book") {
				// ' " '
				cin >> comma;
				if (comma != '"') {
					cout << "Incomplete Command.\n";
					continue;
				}
				// Harry"
				getline(cin, title, '"');
				cin >> comma;
				if (comma != '"') {
					cout << "Incomplete Command.\n";
					continue;
				}
				// JK"
				getline(cin, author, '"');
				deleteBook(title, author, book);
			}
			else {
				cout << "Incomplete Command.\n";
				continue;
			}
		}
		else if (command == "Sort") {
			string by, type;
			cin >> by;
			if (by != "by") {
				cout << "Incomplete Command.\n";
				continue;
			}
			cin >> type;
			if (type == "Title") {
				sortByTitle(book	);
			}
			else if (type == "Author") {
				sortByAuthor(book);
			}
		}
		else {
			cout << "Unknown Command.\n";
		}
	}
}


void insert(string title, string author, string edition, vector<Book>& book) {

	for (int i = 0; i < book.size(); i++) {
		if (book[i].title == title && book[i].editions.find(edition) != book[i].editions.end() && book[i].author == author) {
			cout << "Datum already exist.\n";
			return;
		}
		else if (book[i].title == title && book[i].editions.find(edition) == book[i].editions.end() && book[i].author == author) {
			book[i].editions.insert(edition);
			cout << "Insert " << author << "'s " << title << ", Edition: " << edition << ".\n";
			return;
		}
	}
	book.push_back(Book(title, author, edition));
	cout << "Insert " << author << "'s " << title << ", Edition: " << edition << ".\n";
}


void deleteEdition(string title, string author, string edition, vector<Book>& book) {
	for (int i = 0; i < book.size(); i++) {
		if (book[i].title == title && book[i].author == author) {
			if (book[i].editions.find(edition) == book[i].editions.end()) {		//no this edition
				cout << "Datum doesn't exist.\n";
				return;
			}
			else {
				book[i].editions.erase(book[i].editions.find(edition));
				cout << "Delete " << author << "'s " << title << ", Edition: " << edition << ".\n";
				return;
			}
		}
	}
}


void deleteBook(string title, string author, vector<Book>& book) {
	//vector<Book>tmp;  //把不須刪除的push
	for (int i = 0; i < book.size(); i++) {
		if (book[i].title == title && book[i].author == author) {
			book.erase(book.begin() + i);
			cout << "Delete " << author << "'s " << title << ".\n";
			return;
		}
	}
	cout << "Book doesn't exist.\n";
}


void findBook(string title, string author, vector<Book>& book) {
	vector<int>editions;
	for (int i = 0; i < book.size(); i++) {
		if (book[i].title == title && book[i].author == author) {
			for (auto e : book[i].editions) {
				editions.push_back(stoi(e));
			}
		}
	}
	if (editions.empty()) {
		cout << "Book doesn't exist.\n";
	}
	else {
		sort(editions.begin(), editions.end());
		/*for (auto e : editions)
			ed.push_back(stoi(e));
		cout << "Title: " << title << "\tAuthor: " << author << "\tEdition: " << ed[0];
		for (int i = 1; i < ed.size(); i++) {
			cout << ", " << ed[i];
		}*/
		cout << "Title: " << title << "\tAuthor: " << author << "\tEdition: " << editions[0];
		for (int i = 1; i < editions.size(); i++) {
			cout << ", " << editions[i];
		}
		//cout << " title's size:" << title.size() << " author's size:" << author.size();
		cout << endl;
	}
}


void findAuthor(string author, vector<Book>& book) {
	vector<string>title;
	for (int i = 0; i < book.size(); i++) {
		if (book[i].author == author) {
			title.push_back(book[i].title);
		}
	}
	if (title.empty()) {
		cout << "No book found.\n";
	}
	else {
		sort(title.begin(), title.end());
		cout << author << "'s Books: " << title[0];
		for (int i = 1; i < title.size(); i++) {
			cout << ", " << title[i];
		}
		cout << endl;
	}
}



void sortByTitle(vector<Book>& book) {
	sort(book.begin(), book.end(), sortByTitle2);
	for (int i = 0; i < book.size(); i++) {
		if (book[i].editions.size() > 1) {

			vector<string>editions;
			for (auto e : book[i].editions) {
				editions.push_back(e);
			}

			sort(editions.begin(), editions.end());
			cout << "Title: " << book[i].title << "\tAuthor: " << book[i].author << "\tEdition: " << editions[0];
			for (int j = 1; j < editions.size(); j++) {
				cout << ", " << editions[j];
			}
			//cout << " title's size:" << book[i].title.size() << " author's size:" << book[i].author.size();
			cout << endl;
		}
		else if (book[i].editions.size() == 1) {
			set<string>::iterator it = book[i].editions.begin();
			cout << "Title: " << book[i].title << "\tAuthor: " << book[i].author << "\tEdition: " << (*it) << endl;
			//cout << " title's size:" << book[i].title.size() << " author's size:" << book[i].author.size();
		}
	}
}


void sortByAuthor(vector<Book>& book) {
	sort(book.begin(), book.end(), sortByAuthor2);
	//cout << "SORTBYAUTHOR\n";
	for (int i = 0; i < book.size(); i++) {
		if (book[i].editions.size() > 1) {

			vector<string>editions;
			for (auto e : book[i].editions) {
				editions.push_back(e);
			}

			sort(editions.begin(), editions.end());
			cout << "Title: " << book[i].title << "\tAuthor: " << book[i].author << "\tEdition: " << editions[0];
			for (int j = 1; j < editions.size(); j++) {
				cout << ", " << editions[j];
			}
			//cout << " title's size:" << book[i].title.size() << " author's size:" << book[i].author.size();
			cout << endl;
		}
		else if (book[i].editions.size() == 1) {
			set<string>::iterator it = book[i].editions.begin();
			cout << "Title: " << book[i].title << "\tAuthor: " << book[i].author << "\tEdition: " << (*it) << endl;
			//cout << " title's size:" << book[i].title.size() << " author's size:" << book[i].author.size();
		}
	}

}




bool sortByTitle2(Book& a, Book& b) {
	if (a.title != b.title) {
		return a.title < b.title;
	}
	else
		return a.author < b.author;
}


bool sortByAuthor2(Book& a, Book& b) {
	if (a.author != b.author) {
		return a.author < b.author;
	}
	else
		return a.title < b.title;
}

//Intent : 把string 依照s切割
vector<string>splitString(string buffer, char s) {
	istringstream ss(buffer);
	string token;
	vector<string>res;
	while (getline(ss, token, s)) {
		res.push_back(token);
	}
	return res;
}