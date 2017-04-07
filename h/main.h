/* 
 * Original Work Copyright (c) 2016 Team 42
 * Modified Work Copyright (c) 2017 The Gupta Empire - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Aryan Gupta <me@theguptaempire.net>, February 2017
 * 
 * =============================================================================
 * @author 			Aryan Gupta
 * @project 		Console BattleShip
 * @title 			Main Header
 * @date			2017-02-16 (YYYY-MM-DD)
 * @version			6.7.2
 * @description 	
 * =============================================================================
 */
 
#ifndef _MAIN_
#define _MAIN_

#include <vector>
using std::vector;

extern const bool USERCHEAT;
extern const bool P2CHEAT;

extern const char WATER;
extern const char SHIP;
extern const char HIT;
extern const char MISS;

extern int difficulty;
extern bool userTurn;

extern vector<vector<char> > p1GB;
extern vector<vector<char> > p2GB;
extern vector<vector<char> > p1PB;
extern vector<vector<char> > p2PB;

extern char CLEAR_SCREEN[];

struct cordinate {
	int x;
	int y;
};

int main();

#endif