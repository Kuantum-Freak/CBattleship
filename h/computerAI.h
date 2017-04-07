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
 * @title 			Computer AI Header
 * @date			2017-02-16 (YYYY-MM-DD)
 * @version			6.7.2
 * @description 	
 * =============================================================================
 */
 
#ifndef _COMP_AI_
#define _COMP_AI_

#include <vector>
#include "main.h"

struct possibleHit {
	cordinate c;
	int dir;
};

cordinate computerAI();

cordinate AI_hard();

cordinate convert(int x, int y);

int analyze(const cordinate &c, const int dir);

std::vector<possibleHit> getReport();

cordinate AI_easy();

#endif