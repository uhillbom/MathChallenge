#include "gamedesign.h"

void DisplayMainMenu()
{
	std::cout << "                                               " << std::endl;
	std::cout << "    ###########################################" << std::endl;
    std::cout << "      Welcome to Math Challenge                " << std::endl;
    std::cout << "    ###########################################" << std::endl;
    std::cout << "      1. Change player" << std::endl;
    std::cout << "      2. See the highscores" << std::endl;
	std::cout << "      3. Start game" << std::endl;
	std::cout << "    ___________________________________________" << std::endl;
    std::cout << "      5. Exit" << std::endl;
    std::cout << "    ###########################################" << std::endl;
    std::cout << "    Enter your Selection: ";
}

void DisplayFirstMenu()
{
	std::cout << "                                               " << std::endl;
	std::cout << "    ###########################################" << std::endl;
    std::cout << "      Welcome to Math Challenge                " << std::endl;
    std::cout << "    ###########################################" << std::endl;
    std::cout << "      1. Set player" << std::endl;
    std::cout << "      2. See the highscores" << std::endl;
	std::cout << "    ___________________________________________" << std::endl;
    std::cout << "      5. Exit" << std::endl;
    std::cout << "    ###########################################" << std::endl;
    std::cout << "    Enter your Selection: ";
}

void DisplayCurrentPlayer(Player &p)
{
	std::cout << "                                               " << std::endl;
	std::cout << "    ###########################################" << std::endl;
    std::cout << "      Player Information                       " << std::endl;
    std::cout << "    ###########################################" << std::endl;
    std::cout << std::setw(14) << std::left << "      Name:" << std::setw(20) << std::left << p.getPlayerName() << std::endl;
    std::cout << std::setw(14) << std::left << "      Age: " << std::setw(20) << std::left << p.getPlayerAge() << std::endl;
	std::cout << "    ###########################################" << std::endl;
    std::cout << "                                               " << std::endl;
}

void DisplayGameHeader()
{
	std::cout << "                                               " << std::endl;
	std::cout << "    ###########################################" << std::endl;
	std::cout << "      Math Challenge                           " << std::endl;
	std::cout << "    ###########################################" << std::endl;
	std::cout << "                                               " << std::endl;
}

void DisplayLeaderBoard()
{
	std::cout << "                                               " << std::endl;
	std::cout << "    ###########################################" << std::endl;
	std::cout << "      TOP 10 SCORE BOARD                       " << std::endl;
	std::cout << "    ###########################################" << std::endl;
	std::cout << "                                               " << std::endl;
}