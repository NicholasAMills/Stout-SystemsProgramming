#include <stdio.h>
#include<unistd.h>
#include <iostream>
#include <sys/wait.h>

using namespace std;

int main()
{
pid_t pid;
pid = fork();

if (pid == 0)
   for (int i = 0; i < 100; ++i)
      cout << "A new child was created :)" << endl;
else if (pid < 0)
   {    for (int i = 0; i < 100; ++i)
	cout << "No new child was created\n";
	return 0;
   }
else {
    wait(0); // must wait for a child finish
    cout << "I am the parent" << endl;
}

return 0;
} // end main
