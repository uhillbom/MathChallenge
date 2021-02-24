// Tovas Match Challenge
// Created by Ulf Hillbom
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

int MAX_LEVELS = 10U;
int LEVEL_CHECKS = 5U;

int main() {
	int firstNum, secondNum;
	int expectedAns, answer;
	bool wrongAnswer = false;
	string firstName;

	/* initialize random seed: */
    srand (time(NULL));

	cout << "\n===============================\n";
	cout << "  This is Tovas Math Challenge";
	cout << "\n===============================\n";

	cout << "Hello, what's your Name: ";
	cin >> firstName; // get user input from the keyboard
	cout << "Welcome " << firstName;
	for (int level = 0; level < MAX_LEVELS; level++)
	{
		if (wrongAnswer!=true)
		{
			cout << "\nThis is level " << level;
			cout << " of totally " << MAX_LEVELS;
			for (int i = 0; i < LEVEL_CHECKS; i++)
			{
				firstNum = rand() % 10;
				secondNum = rand() % 10;
				cout << "\nWhat's ";
				cout << firstNum;
				cout << " * ";
				cout << secondNum;
				cout << " = ";
				cin >> answer;
				expectedAns = firstNum * secondNum;
				if (expectedAns == answer) {
					cout << "Correct!\n";
				}
				else
				{
					cout << "\Not Correct!\n";
					wrongAnswer = true;
					break;
				}
			}
		}
		else
		{
			cout << "\nYou came to level " << level-1 << "\n";
			break;
		}
	}
	system("pause");
}


