// Tovas Match Challenge
// Created by Ulf Hillbom

// TODO
// Write Leaderboard if user has a place in top 3.
// Read Leaderboard result

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <vector>

using namespace std;
using namespace chrono;

int MAX_LEVELS = 10U; // This could be extracted from vector
int LEVEL_CHECKS = 5U; // This could be age based

vector<vector<double>> levelMaxTime{
		{10.0F, 9.5F, 9.0F, 8.5F, 7.0F, 7.0F, 7.0F, 7.0F, 6.0F, 6.0F}, // Age 0 - 10 years
		{10.0F, 9.5F, 9.0F, 8.5F, 7.0F, 6.0F, 6.0F, 5.0F, 5.0F, 5.0F}, // Age 11 - 20 years
		{10.0F, 9.5F, 8.0F, 7.0F, 6.0F, 5.0F, 5.0F, 5.0F, 5.0F, 4.0F}, // Age 21 - 30 years
		{10.0F, 9.5F, 8.0F, 7.0F, 6.0F, 5.0F, 5.0F, 4.5F, 4.5F, 4.5F}, // Age 31 - 40 years
		{10.0F, 9.5F, 8.0F, 7.0F, 6.0F, 5.0F, 4.0F, 4.0F, 4.0F, 4.0F}  // Age 40+
		};

void gameHeader(){
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

void clearScreen()
{
	system("CLS");
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

int ageSelector(int age)
{
	if (age <= 9)
	{
		return 0;
	}
	else if (age <= 19 && age >= 10)
	{
		return 1;
	}
	else if (age <= 29 && age >= 20)
	{
		return 2;
	}
	else if (age <= 39 && age >= 30)
	{
		return 3;
	}
	else if (age >= 40)
	{
		return 4;
	}
	else
	{
		return -1; // exception handling.
	}
}

bool validateString(const string& s)
{
    for (const char c : s) {
        if (!isalpha(c) && !isspace(c))
            return false;
    }

    return true;
}

int get_age()
{
    int input;
    bool valid = false;
    while(! valid){ // repeat as long as the input is not valid
        cout << "Enter your age: " ;
        cin >> input;
        if(cin.fail() || input <= 0 || input > 120 ) // for exceptions validate age 0 to fail since that is the init value of age.
        {
            cout << "Wrong input, expect value between 1 - 120 years. " << endl;
            // clear error flags
            cin.clear();
        }
        else
        {
            valid = true;
        }
    }
    return input;
}

string get_name()
{
	bool validName = false;
	string firstName;
	while(!validName)
	{
		cout << "Hello, what's your Name: ";
		cin >> firstName; // get user input from the keyboard
		if(!validateString(firstName))
		{
			cout << "Wrong input" << endl;
			cin.clear();
		}
		else
		{
			validName = true;
		}
	}
	return firstName;
}

int main() {
	steady_clock sc;
	int firstNum, secondNum, addition;
	int expectedAns, answer;
	int age = {0};
	bool wrongAnswer = false;
	double waitTime;
	string firstName;
	char playAgain = {'N'};
	bool quit = false;

	std::cout << std::fixed << std::setprecision(1); // set precision of float to 1 digit

	/* initialize random seed: */
    srand (time(NULL));

	while (!quit)
	{
		clearScreen();

		gameHeader(); // Output welcome message to console

		if (firstName.empty())
		{
			firstName = get_name();
		}

		cout << "Welcome " << firstName << endl;

		if (age == 0) // Not set to the initialization value
		{
			age = get_age();
		}

		int ageLevel = {0};
		ageLevel = ageSelector(age); // get the level bases on the age.
		cout << ageLevel;
		for (int timeLevel = 0; timeLevel < MAX_LEVELS; timeLevel++)
		{
			if (wrongAnswer!=true)
			{
				cout << "\nThis is level " << timeLevel;
				cout << " of totally " << MAX_LEVELS;
				cout << " max time to answer is " << levelMaxTime.at(ageLevel).at(timeLevel) << "\n";
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
					auto time_span = static_cast<duration<double>>(end - start);   // measure time span between start & end
					waitTime = time_span.count();
					if (expectedAns == answer &&  waitTime <= levelMaxTime.at(ageLevel).at(timeLevel))
					{
						cout << "Correct!\n";
						cout << "Time was " << waitTime << " seconds \n";
					}
					else if (waitTime > levelMaxTime.at(ageLevel).at(timeLevel))
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
				cout << "\nYou came to level " << timeLevel-1 << "\n";
				wrongAnswer = false;
				break;
			}
		}

		system("pause");

		// Adding loop to end session of game
		bool correctFeedback = false;
		while(correctFeedback == false)
		{
			clearScreen();
			cout << "\nDo you want to play again? [Y/N] ";
			cin >> playAgain;
			if (playAgain == 'N' || playAgain =='n')
			{
				quit = true;
				correctFeedback = true;
			}
			else if (playAgain == 'Y' || playAgain == 'y')
			{
				quit = false;
				correctFeedback = true;
			}
			else
			{
				correctFeedback = false;
			}
		}
	}
	system("pause");
}