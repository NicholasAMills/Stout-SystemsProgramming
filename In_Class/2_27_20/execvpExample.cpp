#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <string>

using namespace std;

int main() { pid_t pid; char *commandString[2];
string command="./tryme"; // this is the ls unix command
string argument1 = "-l"; // this is an argument for the ls
commandString[0]=(char*)command.c_str(); //this is how to convert a string variable to c_string
commandString[1]=NULL;
pid = fork();
if(pid==0) { //a child was created and you are inside it
  if(execvp(commandString[0], commandString)<0){
    //here using the execvp, the image of execution will be replaced for the child by: ls -l. If it
   //returns a negative value that means something went wrong
    cout << "***ERROR:exec failed\n"; exit(1);
    }

   cout<<"A new child was created :) \n";
  } else if (pid<0)
	{cout<<"No new child was created :(\n"; return 0;}
   else
	{wait(0);
	cout <<"I am the parent\n";}
return 0;
}
