#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

using namespace std;

int main() {
fork();
fork();
fork();
cout << "good luck" << endl;

return 0;
}
