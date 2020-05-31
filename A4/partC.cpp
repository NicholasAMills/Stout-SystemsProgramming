/*
  Part C in the assignment:
  Refactor part A to not use read/write functions
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <iostream>
#include "part1Header.h"
using namespace std;

int main()
{
size_t Maxsize = 80;
int fd[2], nbytes;
pid_t childpid;
char readbuffer[80];
// messages to pass
char nameStr[] = "Nicholas Mills";
char depStr[] = "Computer Science";
char emailStr[] = "millsn1628@my.uwstout.edu";


if (pipe(fd) < 0)  //create a pipe
 exit(1);  // error. No pipe was created.

// save original input and output
int originalInputfd = dup(0);
int originalOutputfd = dup(1);

dup2(fd[1], 1); // change output to write side of pipe
close(fd[1]); // close read side of pipe

// check fork()
if ((childpid = fork()) == -1)
{
 perror("fork did not work; Sorry!");
 exit(1);
}

if (childpid == 0) // inside child
{
 // messages to pass through
 cout << nameStr << endl;
 cout << depStr << endl;
 cout << emailStr << endl;
}
else // back to parent
{
 wait(0);
 dup2(fd[0], 0); // change input to read side of pipe
 close(fd[1]); // close write side of pipe

 dup2(originalOutputfd, 1); //change output back to screen
 childpid = fork(); // second child
 if (childpid <0) {
  cout << "*** ERROR: exec failed" << endl;
  exit(1);
 }// end if

 if (childpid == 0) {
  // buffers
  string buffer1;
  string buffer2;
  string buffer3;

  // redirected stdinput
  getline(cin, buffer1);
  getline(cin, buffer2);
  getline(cin, buffer3);

  fflush(stdout);
  dup2(originalInputfd, 0);
  dup2(originalOutputfd, 1);
  // close the fd's
  close(originalInputfd);
  close(originalOutputfd);
  fflush(stdout);

  cout << buffer1 << endl;
  cout << buffer2 << endl;
  cout << buffer3 << endl;
 } // end if
else {
 wait(0);
 fflush(stdout);
 dup2(originalInputfd, 0);
 dup2(originalOutputfd, 1);
 // close fd's
 close(originalInputfd);
 close(originalOutputfd);
 fflush(stdout);
} // end else

} // end else
fflush(stdout);

return 0;
} // end Part_A()


