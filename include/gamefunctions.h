#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H
#include "player.h"
#include "gamedesign.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <algorithm>

int AgeSelector(int age);
void WriteHighScore(Player &p);
void SortPlayersByScore(std::vector<Player> &pv);
void SortPlayersById(std::vector<Player> &pv);
void ShowScoreBoard(std::vector<Player> &pv, int nums);
int GetNextPlayerId(std::vector<Player> &pv);
Player SearchPlayerInVector(std::vector<Player> &pv, std::string name);
void WaitOnEnter();
void ClearScreen();
std::vector<Player> ReadPlayersToVec();
#endif