// User enters a number, and will print out that many random numbers between 1,000 and 2,000

#include <iostream>
#include <vector>
#include <ctime> // for random function

using namespace std;

//prototypes
void printArray(int*, int);

void generateRandomNumbers(int len_) {
int *array = new int [len_];
for (int i=0; i < len_; i++)
	array[i] = rand()%1001+1000; // number between 1,000 and 2,000
printArray(array, len_);

}

void printArray(int *myArray, int len_) {
int i=0;
while(i<len_){
	cout<<myArray[i++]<<endl;
} // end while

} // end printArray


int main() {
int len;
srand(time(nullptr));
cin >> len;

generateRandomNumbers(len);

return 0;
} // end main

