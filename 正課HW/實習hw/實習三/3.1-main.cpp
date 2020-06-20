// Name: 張永承	
// Date: 2020.03.26
// Last Update: 2020.03.26
// Problem statement: Caesar Cipher

#include <iostream>
#include<string>
using namespace std;

int main() {
	string plaintext;
	while (getline(cin, plaintext)){
		long long int key = 0;
		cin >> key;
		key = key % 26;			
		for (int i = 0; i < plaintext.length(); i++) {
			if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
				int tmp = (int)plaintext[i] + key;
				if (((int)plaintext[i]+key )> 122) {				// 大於z
					plaintext[i] = 'a' + ((int)plaintext[i] + key - 122)-1;
				}
				else if (((int)plaintext[i]+key )< 97) {			// 小於a
					plaintext[i] = 'z' - (97 - ((int)plaintext[i] +key)-1);
				}
				else if((int)plaintext[i] + key <= 122   && (int)plaintext[i] + key >= 97){
					plaintext[i] = plaintext[i] + key;
				}
			}
		}
		std::cout << plaintext << endl;
		cin.ignore();
	}
    return 0;
}