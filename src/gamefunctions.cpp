#include "gamefunctions.h"

std::vector<std::vector<int>> ageLevels {
	{1, 9},
	{10, 19},
	{20, 29},
	{30, 39},
	{40, 120}
	};

int AgeSelector(int age)
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

void WriteHighScore(Player &p)
{
	// Open file and write the player object p
    std::ofstream out("players.txt", std::ios::app);
    out << p;
    out.close();
}

void SortPlayersByScore(std::vector<Player> &pv)
{
	std::sort(pv.begin(), pv.end(),
		[] (const Player& p1, const Player& p2)
		{
			return (std::stod(p1.pScore) > std::stod(p2.pScore));
		}
	);
}

void SortPlayersById(std::vector<Player> &pv)
{
	std::sort(pv.begin(), pv.end(),
		[] (const Player& p1, const Player& p2)
		{
			return (std::stod(p1.pID) > std::stod(p2.pID));
		}
	);
}

/**
 * Show scoreboard of top players
 *
 * @param nums integer value of how many players to show on scoreboard
 * @param pv Vector reference of all Players
 */

void ShowScoreBoard(std::vector<Player> &pv, int nums)
{
	std::cout << std::fixed << std::setprecision(2); // set precision of float to 1 digit
	int playerVecSize = pv.size();
	int iter = 0;
	iter = std::min(playerVecSize, nums);

	DisplayLeaderBoard();
	if (iter>0)
	{
		for (int i=0; i<iter; i++)
		{
			std::cout << std::setw(10) << std::right << std::to_string(i+1) << ": " << std::setw(20) << std::left << pv[i].pName << std::setw(20) << stod(pv[i].pScore) << std::endl;
		}
	}
	std::cin.clear();
	WaitOnEnter();
}

/**
 * function that returns next avaulable player ID
 *
 * @param pv Vector reference of all Players
 * @return nextId Next available player Id.
 */

int GetNextPlayerId(std::vector<Player> &pv)
{
	int nextId = 0;
	if (!pv.empty())
	{
		SortPlayersById(pv);
		nextId = std::stoi(pv[0].pID) + 1U;
	}
	return nextId;
}

Player SearchPlayerInVector(std::vector<Player> &pv, std::string name)
{
	Player tmpPlayer;
	auto name_exist = [&name](const Player& obj) {return obj.pName == name;}; // lambda
	auto it = std::find_if(pv.begin(), pv.end(), name_exist);
	(it != std::end(pv))
		? tmpPlayer = *it
		: tmpPlayer = tmpPlayer;
	return tmpPlayer;
}

void WaitOnEnter()
{
	std::cin.clear();
	std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
	do {
		std::cout << std::endl;
    	std::cout << "    Press the Enter key to continue.";
    } while (std::cin.get() != '\n');
}

void ClearScreen()
{
	system("cmd /c cls");
}

std::vector<Player> ReadPlayersToVec()
{
	// Open the source CSV file
    std::ifstream in("players.txt");

    // Here we will store all players that we read
    std::vector<Player> players{};

    // We will read a complete line and store it here
    std::string line{};

    // Read all lines of the source CSV file
    while (std::getline(in, line)) {

        // Now we read a complete line into our std::string line
        // Put it into a std::istringstream to be able to extract it with iostream functions
        std::istringstream iss(line);

        // We will use a vector to store the substrings
        std::string substring{};
        std::vector<std::string> substrings{};

        // Now, in a loop, get the substrings from the std::istringstream
        while (std::getline(iss, substring, ',')) {

            // Add the substring to the std::vector
            substrings.push_back(substring);
        }
        // Now store the data for one player in a Player struct
        Player player{};
        player.pID = substrings[0];
        player.pName = substrings[1];
        player.pAge = substrings[2];
        player.pScore = substrings[3];

        // Add this new player to our player list
        players.push_back(player);
    }
	return players;
}