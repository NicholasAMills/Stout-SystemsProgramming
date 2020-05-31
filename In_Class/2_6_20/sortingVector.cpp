#include <iostream>
#include <ctime> // random
#include <vector>
#include <fstream>
#include <algorithm> // sort

using namespace std;

int main() {
srand(time(nullptr));
int len=rand()%101+100; // from 100 to 200
ofstream outFile;
outFile.open("fl10_30th.txt");
for (int i=0; i<len; ++i){
	outFile << rand()%20001 + 10000 << endl;// from 10,000 to 30,000.
} // end for
outFile.close(); // close file
cout << "Done" << endl;

// *************************************

vector<int> myVector;
ifstream inFile;
inFile.open("fl10_30th.txt");

if (inFile.fail()){
	cout << "Error: Cannot open the file" << endl;
	return 1; // don't return 0. Misleading.
} // end if

int current;
while(inFile>>current)
	myVector.push_back(current);
inFile.close();
/*cout << "\n******************* Printing the read numbers (Testing)********" << endl;
for (int i = 0; i < myVector.size(); ++i)
	cout << myVector[i] << endl; */
sort(myVector.begin(), myVector.end());
for(int i=0; i<myVector.size(); ++i)
	cout << myVector[i] << endl;


return 0;
} // end main
