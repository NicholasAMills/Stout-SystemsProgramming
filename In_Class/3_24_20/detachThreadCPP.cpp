#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
void detachedThread()
{
cout << "Starting concurrent thread.\n";
for (int i = 0; i < 100; ++i) {
cout << "i= " << i << endl;
this_thread::sleep_for(chrono::seconds(1));
}
cout << "Exiting concurrent thread.\n";
}
void threadCreater()
{
cout << "Starting thread caller.\n";
thread t(detachedThread);
t.detach();
this_thread::sleep_for(  chrono::seconds(1));
cout << "Exiting thread caller.\n";
}
int main()
{
	cout << "Starting thread main.\n";
	threadCreater();
  	this_thread::sleep_for(  chrono::seconds(30)); 
  // as long as main thread is alive, 
 //the detached thread will work until it finisihes its task.
  	cout << "Exiting thread main.\n";
}
