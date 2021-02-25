// Tovas Match Challenge
// Created by Ulf Hillbom

// TODO
// Write Leaderboard if user has a place in top 3.
// Read Leaderboard result
// input checks of keyboard.. name is string and so on.

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <iomanip>

using namespace std;

int MAX_LEVELS = 10U;
int LEVEL_CHECKS = 5U;

double levelMaxTime[10] = {10.F, 9.F, 8.F, 7.F, 6.F, 5.F, 4.F, 4.F, 4.F, 4.F};

void welcome(){
	cout << "\n===============================\n";
	cout << "  This is Tovas Math Challenge";
	cout << "\n===============================\n";
}
void writeResult()
{
	// function to write the result if it was good enough.
}

void readResult()
{
	// function to read the highscore results
}

int getRandValue()
{
	return rand() % 10;
}

int askMultipleQuestion(int val1, int val2)
{
	cout << "\nWhat's ";
	cout << val1;
	cout << " * ";
	cout << val2;
	cout << " = ";
	return val1 * val2;
}

int askAdditionQuestion(int val1, int val2, int addition)
{
	bool add;
	int retVal, val1_tmp;
	add = (addition % 2) == 0;
	if (val2 > val1)
	{
		val1_tmp = val1;
		val1 = val2;
		val2 = val1_tmp;
	}
	if (add)
	{
		cout << "\nWhat's ";
		cout << val1;
		cout << " + ";
		cout << val2;
		cout << " = ";
		retVal = val1 + val2;
	}
	else
	{
		cout << "\nWhat's ";
		cout << val1;
		cout << " - ";
		cout << val2;
		cout << " = ";
		retVal = val1 - val2;
	}
	return retVal;
}

int main() {
	chrono::steady_clock sc;
	int firstNum, secondNum, addition;
	int expectedAns, answer;
	int age;
	bool wrongAnswer = false;
	double waitTime;
	string firstName;
	char playAgain;
	bool quit = false;

	std::cout << std::fixed << std::setprecision(1); // set precision of float to 1 digit

	/* initialize random seed: */
    srand (time(NULL));

	while (!quit)
	{

		welcome(); // Output welcome message to console

		cout << "Hello, what's your Name: ";
		cin >> firstName; // get user input from the keyboard
		cout << "Welcome " << firstName;
		cout << "\nTell me your age: ";
		cin >> age; // get user input from the keyboard
		for (int level = 0; level < MAX_LEVELS; level++)
		{
			if (wrongAnswer!=true)
			{
				cout << "\nThis is level " << level;
				cout << " of totally " << MAX_LEVELS;
				cout << " max time to answer is " << levelMaxTime[level] << "\n";

				system("pause");

				for (int i = 0; i < LEVEL_CHECKS; i++)
				{
					firstNum = getRandValue();
					secondNum = getRandValue();
					if (age <= 8)
					{
						addition = getRandValue(); // get a random value to check for subtraction or not.
						expectedAns = askAdditionQuestion(firstNum,secondNum, addition);
					}
					else
					{
						expectedAns = askMultipleQuestion(firstNum,secondNum);
					}
					auto start = sc.now();     // start timer
					cin >> answer;  // wait for answer
					auto end = sc.now();
					auto time_span = static_cast<chrono::duration<double>>(end - start);   // measure time span between start & end
					waitTime = time_span.count();
					if (expectedAns == answer &&  waitTime <= levelMaxTime[level]) {
						cout << "Correct!\n";
						cout << "Time was " << waitTime << " seconds \n";
					}
					else if (waitTime > levelMaxTime[level])
					{
						cout << "You were to slow!\n";
						cout << "Correct answer is " << expectedAns << "\n";
						cout << "Time was " << waitTime << " seconds \n";
						wrongAnswer = true;
						break;
					}
					else
					{
						cout << "Not Correct!\n";
						cout << "Correct answer is " << expectedAns;
						wrongAnswer = true;
						break;
					}
				}
			}
			else
			{
				cout << "\nYou came to level " << level-1 << "\n";
				wrongAnswer = false;
				break;
			}
		}
		cout << "\nDo you want to play again? [Y/N] ";
		cin >> playAgain;
		if (playAgain == 'N')
		{
			quit = true;
		}
	}
	system("pause");
}