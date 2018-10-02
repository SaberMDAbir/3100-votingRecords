//MD Abir A. Choudhury
//040818
//CIS 3100 
//HW Assignment 8 - Voting Records

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

//Prototypes
void load(int issueNum[], int personOne[], int personTwo[]);
int performanceRating(int issueNum[], int personOne[], int personTwo[], int &numOfIssues);
void similar(int issueNum[], int personOne[], int personTwo[], int &numOfIssues);
void report(int personOne[], int personTwo[], int &numOfIssues);

const int NUMLINES = 100;

int main() {
	int issueNum[NUMLINES];
	int personOne[NUMLINES];
	int personTwo[NUMLINES];

	load(issueNum, personOne, personTwo);

	int numOfIssues = 0;
	int choice = 0;
	do {
		//display menu
		displayMenu();
		cin >> choice;
		//choice 1
		if (choice == 1) {
			performanceRating(issueNum, personOne, personTwo, numOfIssues);
		}
		//choice 2
		else if (choice == 2) {
			similar(issueNum, personOne, personTwo, numOfIssues);
		}
		//choice 3
		else if (choice == 3) {
			report(personOne, personTwo, numOfIssues);
		}
	} while (choice != 0);

	system("PAUSE");
	return 0;
}

//Function Definitions
void load(int issueNum[], int personOne[], int personTwo[]) {
	ifstream myFile;
	myFile.open("votes.txt");

	if (myFile.fail()) {
		cout << "Failed to open file.";
		exit;
	}
	int count = 0;
	while (myFile >> issueNum[count] >> personOne[count] >> personTwo[count]) {
		count++;
	}
	cout << count << endl;
	myFile.close();
}
void displayMenu() {
	cout << "Voting Record Analysis v1.2\n"
		<< "+++++++++++++++++++++++++++\n"
		<< "1: Performance Rating\n"
		<< "2: Similarity Rating\n"
		<< "3: Summary Report\n"
		<< "0: Exit\n"
		<< "Please choose an option: ";
}
int performanceRating(int issueNum[], int personOne[], int personTwo[], int &numOfIssues) {
	//find the number of issues in the file
	int numOfIssues = 0;
	for (int i = 0; i < NUMLINES; i++) {
		if (issueNum[i] == 0) {
			numOfIssues++;
		}
	}
	//Get the total number of times each congressman missed voting
	double totalOne = 0;
	double totalTwo = 0;
	for (int i = 0; i < numOfIssues; i++) {
		if (personOne[i] == 0) {
			totalOne++;
		}
		if (personTwo[i] == 0) {
			totalTwo++;
		}
	}
	//Do calculations
	double ratingOne, ratingTwo = 0;
	ratingOne = totalOne / numOfIssues;
	ratingTwo = totalTwo / numOfIssues;
	
	if (ratingOne > ratingTwo)
		cout << "Congressman A's performance is better than Congressman B.\n";
	else if (ratingTwo > ratingOne)
		cout << "Congressman B's performance is better than Congressman A.\n";

	//output results
	cout << "Congressman A Performance: " << ratingOne << endl;
	cout << "Congressman B Performance: " << ratingTwo << endl;
	
	return numOfIssues;
	
}
void similar(int issueNum[], int personOne[], int personTwo[], int &numOfIssues) {
	int total = 0;
	for (int i = 0; i < NUMLINES; i++) {
		if ((personOne[i] != 0) && (personTwo[i] != 0)) {
			if (personOne[i] == personTwo[i]) {
				total++;
			}
		}
	}
	cout << "The similarity rating is: " << total << endl;
}
void report(int personOne[], int personTwo[], int &numOfIssues) {
	int oneYea, twoYea, oneNay, twoNay, oneMiss, twoMiss = 0;
	for (int i = 0; i < numOfIssues; i++) {
		if (personOne[i] == 0) {
			oneMiss++;
		}
		if (personTwo[i] == 0) {
			twoMiss++;
		}
		if (personOne[i] == 1) {
			oneYea++;
		}
		if (personTwo[i] == 1) {
			twoYea++;
		}
		if (personOne[i] == -1) {
			oneNay++;
		}
		if (personTwo[i] == -1) {
			twoNay++;
		}
	}
	cout << "Congressman A: \n"
		<< "\tYea : " << oneYea << "\n"
		<< "\tNay : " << oneNay << "\n"
		<< "\tMiss: " << oneMiss << "\n"
		<< "Congressman B: \n"
		<< "\tYea : " << twoYea << "\n"
		<< "\tNay : " << twoNay << "\n"
		<< "\tMiss: " << twoMiss << "\n";
}