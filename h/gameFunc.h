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
 * @title 			Game Functions Header
 * @date			2017-02-16 (YYYY-MM-DD)
 * @version			6.7.2
 * @description 	
 * =============================================================================
 */
 
#ifndef _GAME_FX_
#define _GAME_FX_

#include <string>
using std::string;

int getHits(int p);

string getWinner();

bool playerWin();

void turn();

void askContinue();

void changeTurn();

#endif