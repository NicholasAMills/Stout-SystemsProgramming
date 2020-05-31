#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <iostream>
using namespace std;
int main()
{
size_t Maxsize = 80;
int     fd[2], nbytes;
pid_t   childpid;
char    readbuffer[80];

char    sharedStr[] = "Hello, CS442!\n";

if (pipe(fd) < 0)  //create a pipe
 exit(1);  // error. No pipe was created.
if ((childpid = fork()) == -1)
{
 perror("fork did not work; Sorry!");
 exit(1);
}


if (childpid == 0)
{
 /* Child process closes up input side of pipe */
 close(fd[0]);
 /* Send "string" through the output side of pipe */
 write(fd[1], sharedStr, (strnlen(sharedStr, Maxsize)));

 exit(0);
}
else
{
 wait(NULL);
 /* Parent process closes up output side of pipe */
 close(fd[1]);
 /* Read in a string from the pipe */
 nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
 cout << "From Parent: Received string: " << readbuffer << endl;

}
return(0);
}
