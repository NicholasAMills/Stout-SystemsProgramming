/*
  desc: custom shell program driver
*/
#include <iostream>
#include <vector>
#include <string>
#include "commandList.cpp"

using namespace std;

/*
  main():
  in an infinite loop that will quit upon the "exit" command. The user enters a command,
  if the command is a predefined custom one, it will execute that one. Otherwise, it will
  check for piping and input/output redirection. If neither exist, then it will execvp
  the command as is.
*/
int main() {
  string cmd; // user command
  commandList cmdList;

  cout << "\nBegin command: "; // one-time visual to show program is running
  // loop to continue through program
  while (true) {
  getline(cin, cmd); // user types in command

  // check if user entered a custom command and if so, run the appropriate command.
  if (cmdList.isValidCommand(cmd)) {
	  if (cmd == "exit")
	    exit(0);
	  else if (cmd == "pwd")
	    cout << get_current_dir_name() << endl;
	  else if (cmd == "history")
	    cmdList.printHistory();
  } // end if
  else if (cmd.find("|") != string::npos) {
	cmdList.runPipe(cmd);
  }// end else if
  else if (cmd.find(">") != string::npos) {
	cmdList.redirectOutput(cmd);
  }//end else if
  else if (cmd.find("<") != string::npos) {
	cmdList.redirectInput(cmd);
  }//end else if
  else  { // if command is a full line, try running it
	vector<string> command = cmdList.splitSentence(cmd);
	cmdList.runCommand(command);
	} // end else

  } // end while
return 0;
} // end main()
