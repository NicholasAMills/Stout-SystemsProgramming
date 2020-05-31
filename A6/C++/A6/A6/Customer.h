#pragma once
#include <iostream>
#include <string>

using namespace std;

class Customer {
	string ID;
	double balance;

public:
	Customer(string, double);

	string getID() {
		return ID;
	}

	void setID(string iD) {
		ID = iD;
	}

	double getBalance() {
		return balance;
	}

	void setBalance(double bal) {
		balance = bal;
	}

	string toString() {
		string strbalance = to_string(balance);
		return "Customer [ID=" + ID + ", balance=" + strbalance + "]";
	}
};

Customer::Customer(string iD, double bal) {
	ID = iD;
	balance = bal;
}