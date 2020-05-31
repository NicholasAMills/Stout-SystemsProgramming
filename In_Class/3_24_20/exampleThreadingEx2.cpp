// CS442_CPP_Threading_Ex2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Simple program demostrates multiple thread creation
//Dr. Alnaeli
//CS442


#include <iostream>
#include <thread>
#include <vector>
using namespace std;
void runner(int threadNo) {

		cout << threadNo << ": Hello, CS442 Students!\n";
	cout << "This is thread " << this_thread::get_id() << endl;
}

int main(void) {

		vector <thread> greetingThreads; // a vector of threads
	//	int x = 100;
	for (int i = 0; i < 5; i++) // creates and starts 5 threads
		greetingThreads.push_back(thread(runner, (i + 1)));

	for (thread& t : greetingThreads) // loop with a range variable
		t.join();

	cout << "\nThis is main thread " << this_thread::get_id() << endl;
}
