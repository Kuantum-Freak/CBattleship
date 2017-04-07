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
 * @title 			Set Up Header
 * @date			2017-02-16 (YYYY-MM-DD)
 * @version			6.7.2
 * @description 	
 * =============================================================================
 */
 
#ifndef _SETUP_H_
#define _SETUP_H_

void setUpComputerBoard();

void setUpPlayerBoard();

void makeBoards();

void setBoard();

void checkShips(int* r, int* c, bool* b);

#endif