/*
Author: Nicholas Mills
Class: CS 442

Desc: User will enter a string which will then be split into a vector. The vector will then be 
converted into a c_string. Finally, the function contains(string str) will return True or False depending
if the argument str is within the vector

references:
https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
http://www.cplusplus.com/reference/string/string/c_str/
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

/*
   function to check if token is inside vector
*/
bool contains(vector<string> vec, string search) {
for (string str : vec) {
   if (str == search)
	return true;
}

return false;

} // end contains1

/*
   overloaded function to check if token is inside string
*/
bool contains(string str, string search) {
   if (str.find(search) != -1)
	return true;
   else
	return false;

} // end contains2


/*
   Splits the sentence into individual parts and returns it as a vector
*/
vector<string> splitSentence(string str)
{
   vector<string> myVec; // vector to store tokens
   string word = "";
   for (auto x : str) // loop through string
   {
       if (x == ' ')
       {
	   myVec.push_back(word);
           //cout << word << endl;
           word = "";
       }
       else
       {
           word = word + x;
       }
   }
   myVec.push_back(word);
   return myVec;
} //end splitSentence

int main(){
string s1;
vector<string> myVector;

cout << "Enter a sentence" << endl;
getline(cin, s1);

vector<string> myStringTokens = splitSentence(s1); // result of splitSentence function

for (int i=0; i < myStringTokens.size(); ++i)
   cout << myStringTokens.at(i) << endl; // print vector


int length = myStringTokens.size() + 1;
char* c_string[length];
c_string[length] = nullptr;


for (int i = 0; i < length; ++i) {
   c_string[i] = (char*) myStringTokens[i].c_str(); // convert to c_string
} // end for

cout << "\nTo c_string" << endl;

// print out c_string
for (auto const& str : c_string) {
	if (str != nullptr)
		cout << str << endl;
	else
		cout << "NULL" << endl;
} // end for

string input;
cout << "Enter a token to search for: ";
cin >> input;

// search for tokens in vector
if (contains(myStringTokens, input))
   cout << "Vector: FOUND" << endl;
else
   cout << "Vector: NOT FOUND" << endl;

// search for tokens in string
if (contains(s1, input))
   cout << "String: FOUND" << endl;
else
   cout << "String: NOT FOUND" << endl;

return 0;
} // end main
