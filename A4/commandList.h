#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include <iostream>
using namespace std;

class commandList
{
   public:
      bool isValidCommand(string cmd);
      bool isValidCommand(vector<string> vec, string cmd);
      void addToHistory(string cmd);
      int runCommand(vector<string> command_list);
      void printHistory();
      vector<string> splitSentence(string str);
      void runPipe(string command);
      void redirectOutput(string command);
      void redirectInput(string command);
}; // end commandList class

#endif
