/*
  takes the command from the user, processes it into c_strings, and then tries to run it
*/
#include "commandList.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sstream>
#include <algorithm>

#define INTEGER_MAX 2147483647
#define PATH_MAX_SIZE 256
#define HISTORY_DEPTH 20
#define STD_IN_FD 0
#define STD_OUT_FD 1

using namespace std;
// list of accepted commands
string cmdList[3] = {"exit", "pwd", "history"};

// vector to store typed data
vector<string> history;
char * commandString[2];
pid_t pid;

/*
  run command using execvp
*/
int commandList::runCommand(vector<string> command_list) {
  pid = fork();
  int length = command_list.size() + 1;
  char* commandString[length];
  commandString[length] = NULL;

  // convert vector tokens into c_string
  for (int i = 0; i < length; ++i)
    commandString[i] = (char*) command_list[i].c_str(); //convert to c_string

  if (pid == 0) {
    if (execvp(commandString[0], commandString) < 0) { // run execvp
	cout << "*** ERROR: execution failed" << endl;
	exit(1);
    } // end if (execvp)
    else if (pid < 0) {
	cout << "No new child" << endl;
	return 1;
    } // end else if
    else {
	wait(0);
	cout << "I am the parent" << endl;
    }// end nested else
  } // end if
} // end runCommand()


/*
  splits the command line into individual parts and returns the vector
*/
vector<string> commandList::splitSentence(string str)
{
   vector<string> myVec;
   //command_list.clear(); // vector to store string
   string word = "";
   for (auto x : str) // loop through string
   {
	if (x == ' ')
	{
	   myVec.push_back(word);
	   word = "";
	} // end if
	else
	{
	   word = word + x;
	} // end else
   } // end for
   myVec.push_back(word);
   return myVec;
} // end splitSentence


/*
  function to determine if command is valid
  returns true if cmd is in the cmdList
  returns false if cmd is not
  in both cases, cmd is added to the history vector
*/
bool commandList::isValidCommand(string cmd){
   for (string str: cmdList) {
      if (str == cmd) {
	addToHistory(cmd);
	return true;
	}
   } // end for
addToHistory(cmd);
return false;
} // end isValidCommand()



/*
  overloaded function to determine if command given is valid
  this takes the whole command as a set of tokens. This will go through all commands given
*/
bool commandList::isValidCommand(vector<string> vec, string cmd) {
for(string str : vec) {
  if (str == cmd)
    return true;
} // end for

return false;

} // end isValidCommand

/*
  function to add data to the "history" vector
*/
void commandList::addToHistory(string cmd) {
   history.push_back(cmd);
} // end addToHistory


/*
  function to print the history of all commands entered
*/
void commandList::printHistory() {
   for (string str: history) {
      cout << str << endl;
   } // end for
}

/*
  take in command and redirect its outut
  credit: function taken from Dr. Alnaeli's notes on Piazza
*/
void commandList::redirectOutput(string command) { //already working so it is complete

	int inputSeparatorIndex = -1;
	int outputSeparatorIndex = -1;

	int inputFileFd = -1;
	int outputFileFd = -1;

	int stdInCopyFd = -1;
	int stdOutCopyFd = -1;

	vector<string> tokens = splitSentence(command);

	char* commandString[tokens.size() + 1];

	int index = 0;

	for(auto tokenIter = tokens.begin(); tokenIter != tokens.end(); tokenIter++) {

		 if(*tokenIter == ">") {
			outputSeparatorIndex = index;
		}

		commandString[index++] = (char *)(*tokenIter).c_str();
	}

	commandString[index] = NULL;

	int pid = fork();

	if(pid == 0) {

		int lowestSeparatorIndex = INTEGER_MAX;

		if(outputSeparatorIndex > 0) {

			if(outputSeparatorIndex < lowestSeparatorIndex)
				lowestSeparatorIndex = outputSeparatorIndex;

			outputFileFd = open(commandString[outputSeparatorIndex + 1], O_WRONLY | O_CREAT);

			if(outputFileFd == -1) {
				cout << "Opening output file failed!" << endl;

				exit(1);
			}

			stdOutCopyFd = dup(STD_OUT_FD);

			if(dup2(outputFileFd, STD_OUT_FD) == -1) {
				cout << "Failed to move output file descriptor!" << endl;

				exit(1);
			}
		}

		char * commandToRun[lowestSeparatorIndex + 1];

		for(int i = 0; i < lowestSeparatorIndex; i++) {
			commandToRun[i] = commandString[i];
		}

		commandToRun[lowestSeparatorIndex] = NULL;

		execvp(commandToRun[0], commandToRun);
	}
	else if(pid>0){

	wait(0);

	fflush(stdout);
	fflush(stdin);

	dup2(stdOutCopyFd, STD_OUT_FD);
	dup2(stdInCopyFd, STD_IN_FD);

	close(outputFileFd);
	close(inputFileFd);
	}
}


/*
  redirecting input
*/
void commandList::redirectInput(string command) { //incomplete

	int inputSeparatorIndex = -1;
	int outputSeparatorIndex = -1;

	int inputFileFd = -1;
	int outputFileFd = -1;

	int stdInCopyFd = -1;
	int stdOutCopyFd = -1;

	vector<string> tokens = splitSentence(command);

	char* commandString[tokens.size() + 1];

	int index = 0;

	for(auto tokenIter = tokens.begin(); tokenIter != tokens.end(); tokenIter++) {

		 if(*tokenIter == ">") {
			outputSeparatorIndex = index;
		}

		commandString[index++] = (char *)(*tokenIter).c_str();
	}

	commandString[index] = NULL;

	int pid = fork();

	if(pid == 0) {

		int lowestSeparatorIndex = INTEGER_MAX;

		if(outputSeparatorIndex > 0) {

			if(outputSeparatorIndex < lowestSeparatorIndex)
				lowestSeparatorIndex = outputSeparatorIndex;

			outputFileFd = open(commandString[outputSeparatorIndex + 1], O_RDONLY | O_CREAT);

			if(outputFileFd == -1) {
				cout << "Opening output file failed!" << endl;

				exit(1);
			}

			stdOutCopyFd = dup(STD_IN_FD);

			if(dup2(outputFileFd, STD_IN_FD) == -1) {
				cout << "Failed to move output file descriptor!" << endl;

				exit(1);
			}
		}

		char * commandToRun[lowestSeparatorIndex + 1];

		for(int i = 0; i < lowestSeparatorIndex; i++) {
			commandToRun[i] = commandString[i];
		}

		commandToRun[lowestSeparatorIndex] = NULL;

		execvp(commandToRun[0], commandToRun);
	}
	else if(pid>0){

	wait(0);

	fflush(stdout);
	fflush(stdin);

	dup2(stdOutCopyFd, STD_OUT_FD);
	dup2(stdInCopyFd, STD_IN_FD);

	close(outputFileFd);
	close(inputFileFd);
	}
}

/*
  run pipe
  credit: function skeleton taken from Dr. Alnaeli's notes on Piazza
*/
void commandList::runPipe(string command) { //this is incomplete

	string separator = " |";
	int separatorIndex = command.find(separator);
	int fd[2];

	string cmd1 = command.substr(0, separatorIndex);
	string cmd2 = command.substr(separatorIndex + separator.length() + 1);

	if(pipe(fd) < 0) {
		cout << "Pipe failed!";
		exit(1);
	}

	int fdTempOut = dup(STD_OUT_FD);
	int fdTempIn = dup(STD_IN_FD);

	if(dup2(fd[1], STD_OUT_FD) == -1) {
		cout << "Moving of write-end file descriptor failed!" << endl;
	}


	//executeCommand(cmd1); //can be like this
	vector<string> tokens = splitSentence(cmd1);   //here

	char* commandString[tokens.size() + 1];

	int index = 0;
	for(auto tokenIter = tokens.begin(); tokenIter != tokens.end(); tokenIter++) {
		commandString[index++] = (char *)(*tokenIter).c_str();
	}

	commandString[index] = NULL;

	//fork here
	pid = fork();

	if(pid == 0) {
		//execvp here
	    if (execvp(commandString[0], commandString) < 0) { // run execvp
        	cout << "*** ERROR: execution failed" << endl;
        	exit(1);
	    }//end nested if
	}//end if
 	else if(pid >0) {
//1:make parent wait
	wait(0);
	//2:get the sdtout back to normal
	dup2(fdTempOut, 1);
	//3:make the stdin the reading end of the pipe
	dup2(fd[0],0);

	vector<string> tokens2 = splitSentence(cmd2);   //here
	char* commandString2[tokens.size() + 1];
	int index = 0;
	for(auto tokenIter = tokens2.begin(); tokenIter != tokens2.end(); tokenIter++) {
		commandString2[index++] = (char *)(*tokenIter).c_str();
	}

	commandString2[index] = NULL;
//make second for here
	pid = fork();

	if(pid == 0) {
		//execvp the second command for the child
	   if (execvp(commandString2[0], commandString2) < 0) { // run execvp
              cout << "*** ERROR: execution failed" << endl;
              exit(1);
    	   } // end if (execvp)

	}
	else if(pid >1) {

    //make the parent wait again
    wait(0);
	//get the std in and out back to normal using the dup2
	fflush(stdout);
	dup2(fdTempIn,0);
	dup2(fdTempOut,1);
	//close fd's
	close(fdTempIn);
	close(fdTempOut);
	fflush(stdout);



	}
	}
}
