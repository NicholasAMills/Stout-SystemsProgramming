#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

using namespace std;

int main() {
pid_t pid= fork();
	if(pid < 0) {
	cout << "Again :(. Unexpected issue" << endl;
	return 1;
	}
	else if (pid==0){
	cout << "University of Wisconsin" << endl;
	}
	else{
	wait(0);
	cout << " Stout" << endl;
	}
return 0;
}
