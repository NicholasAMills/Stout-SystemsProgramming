/*
  Part A in the assignment:
  Passes 3 messages from child to parent
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

char nameStr[] = "Nicholas Mills\n";
char depStr[] = "Computer Science\n";
char emailStr[] = "millsn1628@my.uwstout.edu\n";


if (pipe(fd) < 0)  //create a pipe
 exit(1);  // error. No pipe was created.
if ((childpid = fork()) == -1)
{
 perror("fork did not work; Sorry!");
 exit(1);
}


if (childpid == 0) // inside child
{
 close(fd[0]); //Child process closes up input side of pipe
 write(fd[1], nameStr, (strnlen(nameStr, Maxsize))); // Send "string" through the output side of pip$
 write(fd[1], depStr, (strnlen(depStr, Maxsize)));
 write(fd[1], emailStr, (strnlen(emailStr, Maxsize)));
 exit(1);
}
else // back to parent
{
 wait(0);
 close(fd[1]); // Parent process closes up output side of pipe
 nbytes = read(fd[0], readbuffer, sizeof(readbuffer)); // read in string from pipe
 cout << "Parent says: Received string:\n" << readbuffer << endl;
} // end else

return 0;
} // end Part_A()

