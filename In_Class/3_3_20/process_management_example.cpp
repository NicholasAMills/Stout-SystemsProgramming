#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>
#include<unistd.h>  //getcwd
#include <sstream>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;
//public variables <- could make private and use getters and setters, but that may
//be a little much for this program.

int main()
{

	int fd[2];
  //runs the shell in a loop
{
		//prints current directory
		//pwd();

		{ //block 1

cout<<"Please enter an integer number"<<endl;
			int userEntry;
			cin>>userEntry;

			if(pipe(fd) < 0){
				cout<<"*** ERROR: exec failed"<<endl;

				exit(1);
			}

			//save original input and output
			int originalInputfd = dup(0);
			int originalOutputfd = dup(1);

			//change output to write side of pipe
			dup2( fd[1], 1);
			//close read side of pipe
			close(fd[1]);
		int 	pid = fork();   //first child
			if(pid < 0){
				cout<<"*** ERROR: exec failed-------------------------"<<endl;
				exit(1);
			}
			if (pid == 0){  //I am inside the child
				cout<<userEntry;
			}else{
				wait(0);
				//change input to read side of pipe
				dup2(fd[0],0);
				//close read side of pipe
				/*here */  // close(fd[0]);
				//close write side of pipe
				close(fd[1]);

				//change output back to screen
				dup2(originalOutputfd , 1);
				pid = fork();  //second child
				if(pid < 0){
					cout<<"*** ERROR: exec failed"<<endl;
					exit(1);
				}
				if(pid == 0){ //inside the second child

				 int buffer;
				 cin>>buffer;
				 fflush(stdout);
					dup2(originalInputfd,0);
					dup2( originalOutputfd, 1);
					//close the fd's
					close(originalInputfd);
					close(originalOutputfd);
					fflush(stdout);
				 if (buffer %2 ==0)
					 cout<<"\n Even"<<endl;
				 else
					  cout<<"\n Odd"<<endl;

				}else{ //parents is run
				  wait(0);
					//flush output and change input back to keyboard and ouput back to screen
					fflush(stdout);
					dup2(originalInputfd,0);
					dup2( originalOutputfd, 1);
					//close the fd's
					close(originalInputfd);
					close(originalOutputfd);
					fflush(stdout);
				}
			}

			//flush output and clear tokens vector
			fflush(stdout);

	  }
	  }
}
