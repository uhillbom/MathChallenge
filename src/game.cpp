#include "game.h"

using namespace std::chrono;
using namespace std::this_thread;     // sleep_for, sleep_until

const int LEVEL_CHECKS = 5U; // This could be age based

std::vector<std::vector<double>> levelMaxTime{
		{10.0F, 9.5F, 9.0F, 8.5F, 7.0F, 7.0F, 7.0F, 7.0F, 6.0F, 6.0F}, // Age 0 - 10 years
		{10.0F, 9.5F, 9.0F, 8.5F, 7.0F, 6.0F, 6.0F, 5.0F, 5.0F, 5.0F}, // Age 11 - 20 years
		{10.0F, 9.5F, 8.0F, 7.0F, 6.0F, 5.0F, 5.0F, 5.0F, 5.0F, 4.0F}, // Age 21 - 30 years
		{10.0F, 9.5F, 8.0F, 7.0F, 6.0F, 5.0F, 5.0F, 4.5F, 4.5F, 4.5F}, // Age 31 - 40 years
		{10.0F, 9.5F, 8.0F, 7.0F, 6.0F, 5.0F, 4.0F, 4.0F, 4.0F, 4.0F}  // Age 40 - 120 years.
		};

int GetRandValue();
int AskMultipleQuestion(int, int);
int AskAdditionQuestion(int, int, int);

void StartGame(Player &p)
{
	/* initialize random seed: */
    srand (time(NULL));

	std::cout << std::fixed << std::setprecision(2); // set precision of float to 1 digit

	steady_clock sc;
	int firstNum, secondNum, addition;
	bool wrongAnswer = false;
	double cumTime, score, waitTime = 0;
	int expectedAns, answer;
	int ageLevel;

	ClearScreen();

	DisplayGameHeader(); // Output welcome message to console

	// Reset eventual score and accum time to 0
	cumTime = 0;
	score = 0;

	// Extract the amount of levels from levelMaxTime vector
	int MAX_LEVELS = (int)levelMaxTime[0].size();

	ageLevel = AgeSelector(std::stoi(p.pAge));

	for (int timeLevel = 0; timeLevel < MAX_LEVELS; timeLevel++)
	{
		if (wrongAnswer!=true)
		{
			if(timeLevel > 0)
				ClearScreen();

			std::cout << std::endl;
			std::cout << "    Your score " << p.getPlayerName() << " is " << score << std::endl;
			std::cout << "    Level " << timeLevel << " of totally " << MAX_LEVELS << " max time to answer is " << levelMaxTime.at(ageLevel).at(timeLevel) << std::endl;
			std::cout << "    Question comes in 5 seconds..." << std::endl;
			sleep_for(5s);

			for (int i = 0; i < LEVEL_CHECKS; i++)
			{
				firstNum = GetRandValue();
				secondNum = GetRandValue();
				if (ageLevel == 0)
				{
					addition = GetRandValue(); // get a random value to check for subtraction or not.
					expectedAns = AskAdditionQuestion(firstNum,secondNum, addition);
				}
				else
				{
					expectedAns = AskMultipleQuestion(firstNum,secondNum);
				}
				auto start = sc.now();     // start timer
				std::cin >> answer;  // wait for answer
				while(std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(256,'\n');
					std::cin >> answer;  // wait for answer
				}
				auto end = sc.now();
				auto time_span = static_cast<duration<double>>(end - start);   // measure time span between start & end
				waitTime = time_span.count();
				cumTime += waitTime;
				score += levelMaxTime.at(ageLevel).at(timeLevel) - waitTime;
				if (expectedAns == answer &&  waitTime <= levelMaxTime.at(ageLevel).at(timeLevel))
				{
					std::cout << "    Correct!" << std::endl;
					std::cout << "    Time was " << waitTime << " seconds " << std::endl;
				}
				else if (waitTime > levelMaxTime.at(ageLevel).at(timeLevel))
				{
					std::cout << std::endl;
					std::cout << "    You were to slow!" << std::endl;
					std::cout << "    Correct answer is " << expectedAns << std::endl;
					std::cout << "    Time was " << waitTime << " seconds" << std::endl;
					wrongAnswer = true;
					break;
				}
				else
				{
					std::cout << std::endl;
					std::cout << "    Not Correct!" << std::endl;;
					std::cout << "    Correct answer is " << expectedAns;
					wrongAnswer = true;
					break;
				}
			}
		}
		else
		{
			std::cout << std::endl;
			std::cout << "    You came to level " << timeLevel-1 << std::endl;
			wrongAnswer = false;
			WaitOnEnter();
			break;
		}
	}
	p.setPlayerScore(score); // sets score.
	WriteHighScore(p);
	p.setPlayerScore(0.0); // reset the score for next game event.
	return;
}

int GetRandValue()
{
	return rand() % 10;
}

int AskMultipleQuestion(int val1, int val2)
{
	std::cout << std::endl;
	std::cout << "    What is " << val1 << " * " << val2 << " = ";
	return val1 * val2;
}

int AskAdditionQuestion(int val1, int val2, int addition)
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
		std::cout << std::endl;
		std::cout << "    What is " << val1 << " + " << val2 << " = ";
		retVal = val1 + val2;
	}
	else
	{
		std::cout << std::endl;
		std::cout << "    What is " << val1 << " - " << val2 << " = ";
		retVal = val1 - val2;
	}
	return retVal;
}