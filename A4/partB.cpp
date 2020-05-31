/*
  Part B of the assignment:
  send message from parent to child
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

int main() {
  size_t Maxsize = 80;
  int fd[2], nbytes;
  pid_t childpid;
  char readbuffer[80];
  // messages to pass
  char str1[] = "Message 1\n";
  char str2[] = "Message 2\n";
  char str3[] = "Message 3\n";

  if (pipe(fd) < 0) {
    exit(1); // No pipe created
  } // end if

  if ((childpid = fork()) == -1) {
    perror("fork did not work in part B");
    exit(1);
  } // end if

  if (childpid == 0) {
    close(fd[1]); // child closes up output side of pipe
    nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
    cout << "Child says: Received string:\n" << readbuffer << endl;
    close(fd[0]);
    exit(1);
  }// end if
  else {
    close(fd[0]); // parent closes up input side of pipe
    write(fd[1], str1, (strnlen(str1, Maxsize)));
    write(fd[1], str2, (strnlen(str2, Maxsize)));
    write(fd[1], str3, (strnlen(str3, Maxsize)));
    cout << "I am the parent" << endl;
  } // end else
return 0;
} // end Part_B()


