// Tovas Match Challenge
// Created by Ulf Hillbom

// TODO
// Output continues score
// Nicer scoreboard
// Break out inte .h
// fix that the answer of the math is validated to numbers.

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <vector>
#include <fstream>
#include <thread>
#include <algorithm>
#include <math.h>
#include <limits>

using namespace std::chrono;
using namespace std::this_thread;     // sleep_for, sleep_until

const int LEVEL_CHECKS = 5U; // This could be age based
const bool DEBUG = false; // When we debug set this to true

class Player
{
	public:
	std::string pID;
	std::string pScore;
	std::string pName;
	std::string pAge;

	Player(std::string id = "", std::string score = "0.0", std::string name = "", std::string age = "0") : pID(id), pScore(score), pName(name), pAge(age)
	{}

	bool operator==(const Player & obj)
	{
		return (pName == obj.pName); //&& (pAge == obj.pAge);
	}
	/*
	* Write the member variables to stream objects
	*/
	friend std::ostream & operator << (std::ostream &out, const Player & obj)
	{
		out << obj.pID << " " << obj.pName << " " << obj.pAge << " " << obj.pScore << std::endl;
		return out;
	}
	/*
	* Read data from stream object and fill it in member variables
	*/
	friend std::istream & operator >> (std::istream &in,  Player &obj)
	{
		in >> obj.pID;
		in >> obj.pName;
		in >> obj.pAge;
		in >> obj.pScore;
		return in;
	}

	std::string getPlayerId()
	{
		return pID;
	}

	void setPlayerId(int ID)
	{
		pID = std::to_string(ID);
	}

	void setPlayerScore(double score)
	{
		pScore = std::to_string(score);
	}

	std::string getPlayerScore()
	{
		return pScore;
	}

	void setPlayerName(std::vector<Player> & pv)
	{
		bool validName = false;
		std::string firstName;
		while(!validName)
		{
			std::cout << "Hello, what is your Name: ";
			std::cin >> firstName; // get user input from the keyboard
			if(!validateString(firstName))
			{
				std::cout << "Wrong input" << std::endl;
				std::cin.clear();
			}
			else
			{
				if (nameInVec(pv, firstName))
					validName = true;
			}
		}
		pName = firstName;
	}

	void setPlayerAge()
	{
		int input;
		bool valid = false;
		while(! valid){ // repeat as long as the input is not valid
			std::cout << "Enter your age: " ;
			std::cin >> input;
			if(std::cin.fail() || input <= 0 || input > 120 ) // for exceptions validate age 0 to fail since that is the init value of age.
			{
				std::cout << "Wrong input, expect value between 1 - 120 years. " << std::endl;
				// clear error flags
				std::cin.clear();
			}
			else
			{
				valid = true;
			}
		}
		pAge = std::to_string(input);
	}

	bool validateString(const std::string& s)
	{
		for (const char c : s) {
			if (!isalpha(c) && !isspace(c))
				return false;
		}

		return true;
	}

	bool nameInVec(std::vector<Player> &pv, std::string name)
	{
		bool found = false;
		auto name_exist = [&name](const Player& obj) {return obj.pName == name;}; // lambda
		auto it = std::find_if(pv.begin(), pv.end(), name_exist);
		(it != std::end(pv))
			? found = true
			: found = false;
		return found;
	}

};

std::vector<std::vector<double>> levelMaxTime{
		{10.0F, 9.5F, 9.0F, 8.5F, 7.0F, 7.0F, 7.0F, 7.0F, 6.0F, 6.0F}, // Age 0 - 10 years
		{10.0F, 9.5F, 9.0F, 8.5F, 7.0F, 6.0F, 6.0F, 5.0F, 5.0F, 5.0F}, // Age 11 - 20 years
		{10.0F, 9.5F, 8.0F, 7.0F, 6.0F, 5.0F, 5.0F, 5.0F, 5.0F, 4.0F}, // Age 21 - 30 years
		{10.0F, 9.5F, 8.0F, 7.0F, 6.0F, 5.0F, 5.0F, 4.5F, 4.5F, 4.5F}, // Age 31 - 40 years
		{10.0F, 9.5F, 8.0F, 7.0F, 6.0F, 5.0F, 4.0F, 4.0F, 4.0F, 4.0F}  // Age 40 - 120 years.
		};

std::vector<std::vector<int>> ageLevels {
	{1, 9},
	{10, 19},
	{20, 29},
	{30, 39},
	{40, 120}
	};

// Function prototypes
std::vector<Player> readPlayersToVec();
void writeHighScore(Player &p);
void showScoreBoard(std::vector<Player> &pv, int nums);
void gameHeader();
void leaderBoardHeader();
void readResult(std::string, int ageLevel);
int getRandValue();
void clearScreen();
int askMultipleQuestion(int, int);
int askAdditionQuestion(int, int, int);
int ageSelector(int);
bool validateString(const std::string&);
void wait_on_enter();
void startGame(Player &p);
void sortPlayersByScore(std::vector<Player> &pv);
int getNextPlayerId(std::vector<Player> &pv);
bool validateString(const std::string& s);

// menu
int DisplayMainMenu();

int main() {
	Player thisPlayer;
	int nextId = 0;
	std::cout << std::fixed << std::setprecision(1); // set precision of float to 1 digit

	clearScreen();

	while(1)
	{
		// Display Main Menu
		int selection = DisplayMainMenu();
		//int selection = 1;

		// Get the player list
		std::vector<Player> players;
		players = readPlayersToVec();

		switch(selection) {
			case 1:
				{
					thisPlayer.setPlayerName(players);
					thisPlayer.setPlayerAge();
					nextId = getNextPlayerId(players);
					thisPlayer.setPlayerId(nextId);
					break;
				}
			case 2:
				{
					clearScreen();
					showScoreBoard(players,10U);
					clearScreen();
					break;
				}
			case 3:
				{
					if (thisPlayer.pName != "")
						startGame(thisPlayer);
					break;
				}
			case 5:
			default:
			return 0;
        };
	}
	return 0;
}

void startGame(Player &p)
{
	/* initialize random seed: */
    srand (time(NULL));

	steady_clock sc;
	int firstNum, secondNum, addition;
	bool wrongAnswer = false;
	double cumTime, score, waitTime = 0;
	int expectedAns, answer;
	int ageLevel;

	clearScreen();

	gameHeader(); // Output welcome message to console

	// Reset eventual score and accum time to 0
	cumTime = 0;
	score = 0;

	// Extract the amount of levels from levelMaxTime vector
	int MAX_LEVELS = (int)levelMaxTime[0].size();

	ageLevel = ageSelector(std::stoi(p.pAge));

	for (int timeLevel = 0; timeLevel < MAX_LEVELS; timeLevel++)
	{
		if (wrongAnswer!=true)
		{
			if(timeLevel > 0)
				clearScreen();

			std::cout << "\nLevel " << timeLevel << " of totally " << MAX_LEVELS << " max time to answer is " << levelMaxTime.at(ageLevel).at(timeLevel) << "\n";
			std::cout << "Question comes in 5 seconds..." << std::endl;
			sleep_for(5s);

			for (int i = 0; i < LEVEL_CHECKS; i++)
			{
				firstNum = getRandValue();
				secondNum = getRandValue();
				if (ageLevel == 0)
				{
					addition = getRandValue(); // get a random value to check for subtraction or not.
					expectedAns = askAdditionQuestion(firstNum,secondNum, addition);
				}
				else
				{
					expectedAns = askMultipleQuestion(firstNum,secondNum);
				}
				auto start = sc.now();     // start timer
				std::cin >> answer;  // wait for answer
				auto end = sc.now();
				auto time_span = static_cast<duration<double>>(end - start);   // measure time span between start & end
				waitTime = time_span.count();
				cumTime += waitTime;
				score += levelMaxTime.at(ageLevel).at(timeLevel) - waitTime;
				if (expectedAns == answer &&  waitTime <= levelMaxTime.at(ageLevel).at(timeLevel))
				{
					std::cout << "Correct!\n";
					std::cout << "Time was " << waitTime << " seconds \n";
				}
				else if (waitTime > levelMaxTime.at(ageLevel).at(timeLevel))
				{
					std::cout << "You were to slow!\n";
					std::cout << "Correct answer is " << expectedAns << "\n";
					std::cout << "Time was " << waitTime << " seconds \n";
					wrongAnswer = true;
					break;
				}
				else
				{
					std::cout << "Not Correct!\n";
					std::cout << "Correct answer is " << expectedAns;
					wrongAnswer = true;
					break;
				}
			}
		}
		else
		{
			std::cout << "\nYou came to level " << timeLevel-1 << "\n";
			wrongAnswer = false;
			wait_on_enter();
			break;
		}
	}
	p.setPlayerScore(score); // sets score.
	writeHighScore(p);
	return;
}

int DisplayMainMenu()
{
    std::cout << "Welcome to the math game Tovas Math Challenge" << std::endl;
    std::cout << "___________________________________________" << std::endl;
    std::cout << "1. Set Player Name" << std::endl;
    std::cout << "2. See the highscores" << std::endl;
	std::cout << "3. Start game" << std::endl;
	std::cout << "___________________________________________" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "___________________________________________" << std::endl;
    std::cout << "Enter your Selection: " << std::endl;
    int m = -1;
    std::cin >> m;
    return m;
}

void gameHeader()
{
	std::cout << "\n===============================\n";
	std::cout << "   This is Tovas Math Challenge";
	std::cout << "\n===============================\n";
}

void leaderBoardHeader()
{
	std::cout << "\n==============================\n";
	std::cout << "        TOP 10 SCORE BOARD";
	std::cout << "\n==============================\n";
}

void wait_on_enter()
{
	std::cin.clear();
	std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
	do {
    std::cout << '\n' << "Press the Enter key to continue.";
    } while (std::cin.get() != '\n');
}

void clearScreen()
{
	std::cout << "\033[2J\033[1;1H"; // from searching.. platform independent compare to system('CLS')
}

int getRandValue()
{
	return rand() % 10;
}

int askMultipleQuestion(int val1, int val2)
{
	std::cout << "\nWhat is " << val1 << " * " << val2 << " = ";
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
		std::cout << "\nWhat is " << val1 << " + " << val2 << " = ";
		retVal = val1 + val2;
	}
	else
	{
		std::cout << "\nWhat is " << val1 << " - " << val2 << " = ";
		retVal = val1 - val2;
	}
	return retVal;
}

int ageSelector(int age)
{
	int minAge = 0;
	int maxAge = 0;
	unsigned int ageLevelsMax = (int)ageLevels.size();
	unsigned int ageLevel = 0;
	for (unsigned int i=0; i < ageLevelsMax; ++i )
	{
		ageLevel = i;
		minAge = ageLevels[i][0];
		maxAge = ageLevels[i][1];
		if (age >= minAge && age <=maxAge)
		{
			return ageLevel;
		}
	}
	return ageLevel; // Default return if nothing was found
}

std::vector<Player> readPlayersToVec()
{
	// Open the File
    std::ifstream in("players.txt");

	std::vector<Player> players;

	while (in.good()) {
        Player temp;
		in >> temp.pID;
		in >> temp.pName;
		in >> temp.pAge;
		in >> temp.pScore;
        if (temp.pName != "" && temp.pAge != "")
    	    players.push_back(temp);
	}
    in.close();
	return players;
}

void writeHighScore(Player &p)
{
	// Open file and write the player object p
    std::ofstream out("players.txt", std::ios::app);
    out << p;
    out.close();
}

void sortPlayersByScore(std::vector<Player> &pv)
{
	std::sort(pv.begin(), pv.end(),
		[] (const Player& p1, const Player& p2)
		{
			return (std::stod(p1.pScore) > std::stod(p2.pScore));
		}
	);
}

void sortPlayersById(std::vector<Player> &pv)
{
	std::sort(pv.begin(), pv.end(),
		[] (const Player& p1, const Player& p2)
		{
			return (std::stod(p1.pID) > std::stod(p2.pID));
		}
	);
}

void showScoreBoard(std::vector<Player> &pv, int nums)
{

	sortPlayersByScore(pv);

	int playerVecSize = pv.size();
	int iter = 0;
	iter = std::min(playerVecSize, nums);

	leaderBoardHeader();
	if (iter>0)
	{
		for (int i=0; i<iter; i++)
		{
			std::cout << pv[i].pName << " " << pv[i].pScore << std::endl;
		}
	}
	std::cin.clear();
	wait_on_enter();
}

int getNextPlayerId(std::vector<Player> &pv)
{
	sortPlayersById(pv);

	return std::stoi(pv[0].pID) + 1U;
}