#include <string>
#include <vector>
#include <ostream>

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
		out << obj.pID << "," << obj.pName << "," << obj.pAge << "," << obj.pScore << std::endl;
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
		return this->pID;
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
		return this->pScore;
	}

	void setPlayerName(std::vector<Player> & pv);

	std::string getPlayerName()
	{
		return this->pName;
	}

	void setPlayerAge();

	std::string getPlayerAge()
	{
		return this->pAge;
	}

	bool validateString(const std::string& s);

};