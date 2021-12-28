// Tovas Match Challenge
// Created by Ulf Hillbom

// TODO:
// Padding of the game layout
// Aligned scoreboard

#include "gamedesign.h"
#include "player.h"
#include "game.h"

int main() {
	Player thisPlayer;
	int nextId = 0;
	std::cout << std::fixed << std::setprecision(1); // set precision of float to 1 digit
	bool firstMenu = true;

	while(firstMenu)
	{

		// Display Main Menu
		DisplayFirstMenu();

		// Wait for correct input.
		int selection;
		std::cin >> selection;
		while(std::cin.fail()) {
		    std::cin.clear();
		    std::cin.ignore(256,'\n');
			ClearScreen();
			break;
		}

		// Get the player list
		std::vector<Player> players;
		players = ReadPlayersToVec();

		Player tmpPlayerObj;

		switch(selection) {
			case 1:
				{
					thisPlayer.setPlayerName(players);
					thisPlayer.setPlayerAge();
					// Check if this player allready exists.
					tmpPlayerObj = SearchPlayerInVector(players, thisPlayer.getPlayerName());
					if (tmpPlayerObj.getPlayerId() == "")
					{
						// the NameInVec returned a none set Player Id means that player does not exist previously.
						nextId = GetNextPlayerId(players);
						thisPlayer.setPlayerId(nextId);
					}
					else
					{
						// Player allready exists. Set the player ID to the existing one.
						thisPlayer.setPlayerId(std::stoi(tmpPlayerObj.getPlayerId()));
					}
					firstMenu = false;
					break;
				}
			case 2:
				{
					ClearScreen();
					SortPlayersByScore(players);
					ShowScoreBoard(players,10U);
					ClearScreen();
					break;
				}
			case 5:
				return 0;
			default:
				ClearScreen();
				continue;
        };
	}

	while(!firstMenu)
	{
		ClearScreen();

		// Display current player info
		DisplayCurrentPlayer(thisPlayer);

		// Display Main Menu
		DisplayMainMenu();

		// Wait for correct input.
		int selection;
		std::cin >> selection;
		while(std::cin.fail()) {
		    std::cin.clear();
		    std::cin.ignore(256,'\n');
			ClearScreen();
			break;
		}

		// Get the player list
		std::vector<Player> players;
		players = ReadPlayersToVec();

		Player tmpPlayerObj;

		switch(selection) {
			case 1:
				{
					thisPlayer.setPlayerName(players);
					thisPlayer.setPlayerAge();
					// Check if this player allready exists.
					tmpPlayerObj = SearchPlayerInVector(players, thisPlayer.getPlayerName());
					if (tmpPlayerObj.getPlayerId() == "")
					{
						// the NameInVec returned a none set Player Id means that player does not exist previously.
						nextId = GetNextPlayerId(players);
						thisPlayer.setPlayerId(nextId);
					}
					else
					{
						// Player allready exists. Set the player ID to the existing one.
						thisPlayer.setPlayerId(std::stoi(tmpPlayerObj.getPlayerId()));
					}
					break;
				}
			case 2:
				{
					ClearScreen();
					SortPlayersByScore(players);
					ShowScoreBoard(players,10U);
					ClearScreen();
					break;
				}
			case 3:
				{
					if (thisPlayer.pName != "")
						StartGame(thisPlayer);
					break;
				}
			case 5:
				return 0;
			default:
				continue;
        };
	}
	return 0;
}