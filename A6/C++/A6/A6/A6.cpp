
#include "Customer.h"
#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
//#include "Customer.cpp"

using namespace std;

int arry [4] = { 0, 0, 0, 0 };

void parallelCounting(vector<Customer> myList, int start, int end, int pos) {
    for (int i = start; i < end; ++i) {
        if (myList[i].getBalance() < 1000)
            arry[pos] = arry[pos + 1];
    }
}

int main()
{
    cout << "NEW LINE" << endl;
    vector<Customer> custList;
    long currentRec = 0;
    cout << "Reading the file \"accounts.txt\" " << endl;
    ifstream inFile("accounts.txt");

	string currID, line;
	string currBalance;
    
    while (getline(inFile, currID)) {
        getline(inFile, currBalance);
        custList.push_back(Customer(currID, stod(currBalance)));

        if (++currentRec % 30000 == 0)
            cout << ">>";
        if (currentRec % 1000000 == 0)
            cout << endl;
    }
    inFile.close();

    

    int workload = custList.size() / 4;
    int sec1 = workload;
    int sec2 = workload * 2;
    int sec3 = workload * 3;
    int sec4 = custList.size() - 1;

    thread th1(parallelCounting, custList, 0, sec1, 0);
    thread th2(parallelCounting, custList, sec1+1, sec2, 1);
    thread th3(parallelCounting, custList, sec2+1, sec3, 2);
    thread th4(parallelCounting, custList, sec3+1, sec4, 3);
    th1.join(); th2.join(); th3.join(); th4.join();

    int total = 0;
    for (int i = 0; i < 4; ++i)
        total += arry[i];
    cout << "Number of accounts with less than $1,000: " << total << endl;

    return 0;
}

