
//Madison Sawvel

#include <iostream>
#include <string>
#include <cstdlib>
#include "RBTree.h"
#include "DRT.h"
#include "PG5.h"
#include "Database.h"

using namespace std;

Database* Studs;

int main(int argc, char** argv) {
	Studs = new RBTree();
	while (ProcessCommand());
	delete Studs;
	return 0;
}
bool ProcessCommand() {
	string cmd;
	getline(cin, cmd);
	if (cmd == "EXIT") return false;
	if (cmd == "PRINT") {
		Print();
		if (((RBTree*)Studs)->Valid()) {
			cout << "Valid Tree" << endl;
		}
		else {
			cout << "Invalid Tree" << endl;
		}
	}
	else if (cmd == "RPRINT") {
		RPrint();
		if (((RBTree*)Studs)->Valid()) {
			cout << "Valid Tree" << endl;
		}
		else {
			cout << "Invalid Tree" << endl;
		}
	}
	else if (cmd.substr(0, 3) == "ADD") {
		AddCommand(cmd);
		if (((RBTree*)Studs)->Valid()) {
			cout << "Valid Tree" << endl;
		}
		else {
			cout << "Invalid Tree" << endl; 
		}
	}
	else if (cmd.substr(0, 6) == "REMOVE") {
		RemoveCommand(cmd);
		if (((RBTree*)Studs)->Valid()) {
			cout << "Valid Tree" << endl;
		}
		else {
			cout << "Invalid Tree" << endl;
		}
	}
	else if (cmd.substr(0, 6) == "LOOKUP") {
		LookupCommand(cmd);
		if (((RBTree*)Studs)->Valid()) {
			cout << "Valid Tree" << endl;
		}
		else {
			cout << "Invalid Tree" << endl;
		}
	}
	else if (cmd.substr(0, 4) == "EDIT") {
		EditCommand(cmd);
		if (((RBTree*)Studs)->Valid()) {
			cout << "Valid Tree" << endl;
		}
		else {
			cout << "Invalid Tree" << endl;
		}
	}
	else cout << "Invalid Command" << endl;
	return true;
}
void Print() {
	cout << "Printing list forwards: " << endl;
	DRT* T = Studs->search("");
	string k = T->getnext();
	while (k != "") {
		delete T;
		T = Studs->search(k);
		cout << "Name: " << k << "\t GPA: " << T->getdata() << endl;
		k = T->getnext();
	}
	delete T;
	cout << endl;
}
void RPrint() {
	cout << "Printing list backwards: " << endl;
	DRT* T = Studs->search("");
	string k = T->getprev();
	while (k != "") {
		delete T;
		T = Studs->search(k);
		cout << "Name: " << k << "\t Copies: " << T->getdata() << endl;
		k = T->getprev();
	}
}

void AddCommand(string cmd) {
	int q1, q2;
	for (q1 = 0; cmd[q1] != '\"'; q1++);
	for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
	string k = cmd.substr(q1 + 1, q2 - q1 - 1);
	string d = cmd.substr(q2 + 1, cmd.length());
	DRT* T = Studs->search(k);
	if (T->getdata() != "") {
		cout << "\"" << k << "\" already exists in database" << endl;
	}
	else {
		delete T;
		T = Studs->modify(k, d);
		cout << "\"" << k << "\" has been added to database" << endl;
	}
	delete T;
}

void RemoveCommand(string cmd) {
	int q1, q2;
	for (q1 = 0; cmd[q1] != '\"'; q1++);
	for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
	string k = cmd.substr(q1 + 1, q2 - q1 - 1);
	DRT* T = Studs->search(k);
	if (T->getdata() == "") {
		cout << "\"" << k << "\" does not exist in the database." << endl;
	}
	else {
		delete T;
		T = Studs->modify(k, "");
		cout << "\"" << k << "\" has been removed from the database." << endl;
	}
	delete T;
}
void LookupCommand(string cmd) {
	int q1, q2;
	for (q1 = 0; cmd[q1] != '\"'; q1++);
	for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
	string k = cmd.substr(q1 + 1, q2 - q1 - 1);
	DRT* T = Studs->search(k);
	if (T->getdata() != "") {
		cout << "Name: " << k << "\t GPA: " << T->getdata() << endl;
	}
	else {
		cout << "Not found, but would be close to " << T->getprev() << " and " << T->getnext() << endl;
	}
}
void EditCommand(string cmd) {
	int q1, q2;
	for (q1 = 0; cmd[q1] != '\"'; q1++);
	for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
	string k = cmd.substr(q1 + 1, q2 - q1 - 1);
	string d = cmd.substr(q2 + 1, cmd.length());
	DRT* T = Studs->search(k);
	if (T->getdata() == "") {
		cout << "\"" << k << "\" does not exist in database" << endl;
	}
	else {
		delete T;
		T = Studs->modify(k, d);
		cout << "\"" << k << "\" has been edited in database" << endl;
	}
	delete T;
}

/*
To fix:
You're not using the validity code correctly, and so you may have bugs in your tree of which you are unaware.

In your ProcessCommand method, after each command do something like:

if (((RBTree *)Studs)->Valid()) {
 cout << "Valid Tree" << endl;
} else {
 cout << "Invalid Tree" << endl;
}
*/