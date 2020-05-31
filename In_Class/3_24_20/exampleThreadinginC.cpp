#include <iostream>
#include <thread>
using namespace std;

void greeting(void) { // this function will work as a runner and called by the new thread
	cout << "Hello, CS442 Students!\n";
	cout << "This is thread No " << this_thread::get_id() << endl;
}

int main(void) {
	thread myThread(greeting); // creates a thread and starts it with the specified function

	myThread.join();  // needed so that the program does not terminate before
	  // the stared thread finishes. That is, make the main thread wait for the new thread.
	cout << "by main thread  " << this_thread::get_id() << endl;
	return 0;
}
