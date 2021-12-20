#include <iostream>
#include <string>
#include "player.h"

void Player::setPlayerName(std::vector<Player> & pv)
{
	bool validName = false;
	std::string firstName;
	while(!validName)
	{
		std::cout << "    Hello, what is your Name: ";
		std::cin >> firstName; // get user input from the keyboard
		if(!validateString(firstName))
		{
			std::cout << "    Wrong input" << std::endl;
			std::cin.clear();
		}
		else
		{
			validName = true;
			break;
		}
	}
	pName = firstName;
}

void Player::setPlayerAge()
{
	int input;
	bool valid = false;
	while(! valid){ // repeat as long as the input is not valid
		std::cout << "    Enter your age: " ;
		std::cin >> input;
		if(std::cin.fail() || input <= 0 || input > 120 ) // for exceptions validate age 0 to fail since that is the init value of age.
		{
			std::cout << "    Wrong input, expect value between 1 - 120 years. " << std::endl;
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

bool Player::validateString(const std::string& s)
{
	for (const char c : s) {
		if (!isalpha(c) && !isspace(c))
			return false;
	}

	return true;
}