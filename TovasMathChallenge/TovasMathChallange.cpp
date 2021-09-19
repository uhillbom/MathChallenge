// Tovas Match Challenge
// Created by Ulf Hillbom

// TODO
// Write Leaderboard if user has a place in top 3.
// Adding new agelevels should rewrite file
// Calculate score

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <vector>
#include <fstream>


using namespace std;
using namespace chrono;

const int LEVEL_CHECKS = 5U; // This could be age based
const bool DEBUG = false; // When we debug set this to true
const string filename = "tovasScores.sb";

vector<vector<double>> levelMaxTime{
		{10.0F, 9.5F, 9.0F, 8.5F, 7.0F, 7.0F, 7.0F, 7.0F, 6.0F, 6.0F}, // Age 0 - 10 years
		{10.0F, 9.5F, 9.0F, 8.5F, 7.0F, 6.0F, 6.0F, 5.0F, 5.0F, 5.0F}, // Age 11 - 20 years
		{10.0F, 9.5F, 8.0F, 7.0F, 6.0F, 5.0F, 5.0F, 5.0F, 5.0F, 4.0F}, // Age 21 - 30 years
		{10.0F, 9.5F, 8.0F, 7.0F, 6.0F, 5.0F, 5.0F, 4.5F, 4.5F, 4.5F}, // Age 31 - 40 years
		{10.0F, 9.5F, 8.0F, 7.0F, 6.0F, 5.0F, 4.0F, 4.0F, 4.0F, 4.0F}  // Age 40 - 120 years.
		};

vector<vector<int>> ageLevels {
	{1, 9},
	{10, 19},
	{20, 29},
	{30, 39},
	{40, 120}
	};

// Function prototypes
bool ask_yesno_question(string);
void gameHeader();
void leaderBoardHeader();
void writeResult();
int createScoreFile(string);
void readResult(string, int ageLevel);
int getRandValue();
void clearScreen();
int askMultipleQuestion(int, int);
int askAdditionQuestion(int, int, int);
int ageSelector(int, vector<vector<int>>);
bool validateString(const string&);
int get_age();
string get_name();

int main() {
	steady_clock sc;
	int firstNum, secondNum, addition;
	int expectedAns, answer;
	int age = {0};
	bool wrongAnswer = false;
	double waitTime;
	string firstName;
	bool quit = false;
	bool show_scoreboard = false;

	std::cout << std::fixed << std::setprecision(1); // set precision of float to 1 digit

	/* initialize random seed: */
    srand (time(NULL));

	// Create ScoreFile //
	int fileCreated = 0;
	fileCreated  = createScoreFile(filename);

	// Extract the amount of levels from levelMaxTime vector
	int MAX_LEVELS = (int)levelMaxTime[0].size();

	while (!quit)
	{
		clearScreen();

		gameHeader(); // Output welcome message to console

		if (firstName.empty() && !DEBUG)
		{
			firstName = get_name();
		}
		else
		{
			firstName = "Test";
		}

		cout << "Welcome " << firstName << endl;

		if (age == 0 && !DEBUG) // Not set to the initialization value
		{
			age = get_age();
		}
		else
		{
			age = 120;
		}

		int ageLevel = {0};
		ageLevel = ageSelector(age, ageLevels); // get the level based on the age.

		if (DEBUG)
		{
			cout << ageLevel << endl;
		}

		show_scoreboard = ask_yesno_question("Do you want to see the scoreboard?");
		if (show_scoreboard)
		{
			clearScreen();
			leaderBoardHeader();
			readResult(filename, ageLevel);
			system("pause");
			clearScreen();
		}

		for (int timeLevel = 0; timeLevel < MAX_LEVELS; timeLevel++)
		{
			if (wrongAnswer!=true)
			{
				clearScreen();
				cout << "\nLevel " << timeLevel << " of totally " << MAX_LEVELS << " max time to answer is " << levelMaxTime.at(ageLevel).at(timeLevel) << "\n";
				system("pause");

				for (int i = 0; i < LEVEL_CHECKS; i++)
				{
					firstNum = getRandValue();
					secondNum = getRandValue();
					if (age <= 8) // TODO fix with more none explicit check.
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
			system("pause");
		}

		system("pause");

		quit = ask_yesno_question("Do you want to exit?"); // Check if user wants to play again.

	}
	system("pause");
}

bool ask_yesno_question(string question)
{
	char input = {'N'};
	bool correctFeedback = false;
	while(correctFeedback == false)
	{
		//clearScreen();
		cout << "\n" << question << " [Y/N] ";
		cin >> input;
		if (input == 'N' || input =='n')
		{
			return false;
			correctFeedback = true;
		}
		else if (input == 'Y' || input == 'y')
		{
			return true;
			correctFeedback = true;
		}
		else
		{
			correctFeedback = false;
		}
	}
}

void gameHeader()
{
	cout << "\n===============================\n";
	cout << "  This is Tovas Math Challenge";
	cout << "\n===============================\n";
}

void leaderBoardHeader()
{
	cout << "\n==============================\n";
	cout << "           SCORE BOARD";
	cout << "\n==============================\n";
}

void writeResult()
{
	// function to write the result if it was good enough.
}

void readResult(string fileName, int ageLevel)
{
	//function to read the highscore results
	int i = 0;
	string line;
	ifstream file(fileName);
	string lineStrTmp;
	int position = 0;
	bool found = false;
	if (file.is_open()) {
		while (! file.eof() )
    	{
			getline(file, line);
			lineStrTmp = "//" + to_string(ageLevel);
			if (line == lineStrTmp && !found)
			{
				found = true;
			}
			if (found)
			{
				if (position >= 1 && position < 4)
				{
					cout << "Place " << position << ": " << line << endl;
				}
				else if (position >= 4)
				{
					found = false;
				}
				position++;
			}
			i++;
		}
	file.close();
	}
}

int createScoreFile(string filename)
{
	// This function should create the leaderboard file if it's not yet created.
	if (ifstream(filename))
	{
		return true;
	}
	ofstream file(filename); // create  file
	if (!file)
	{
		return false;
	}
	else
	{
		return true;
	}
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
	cout << "\nWhat is " << val1 << " * " << val2 << " = ";
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
		cout << "\nWhat is " << val1 << " + " << val2 << " = ";
		retVal = val1 + val2;
	}
	else
	{
		cout << "\nWhat is " << val1 << " - " << val2 << " = ";
		retVal = val1 - val2;
	}
	return retVal;
}

int ageSelector(int age, vector<vector<int>> ageLevels)
{
	int minAge = 0;
	int maxAge = 0;
	for ( size_t ageLevel = 0; ageLevel < ageLevels.size(); ++ageLevel )
	{
		minAge = ageLevels[ageLevel][0];
		maxAge = ageLevels[ageLevel][1];
		if (age >= minAge && age <=maxAge)
		{
			return ageLevel;
		}
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
		cout << "Hello, what is your Name: ";
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