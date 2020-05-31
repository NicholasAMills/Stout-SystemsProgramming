#include <iostream>
#include <string>
using namespace std;

int main(){
	string s1;
	string s2;

	cout << "Enter your first string" << endl;
	getline(cin, s1);

	cout << "Enter your second string" << endl;
	cin >> s2;

	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;

	int found = s1.find(s2);


	if (found != -1)
		cout << "FOUND" << endl;
	else
		cout << "NOT FOUND" << endl;


return 0;
}
