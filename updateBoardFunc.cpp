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
 * @title 			Update Board Funcions
 * @date			2017-02-16 (YYYY-MM-DD)
 * @fversion			6.7.2
 * @description 	This file contains functions that can update the board. For
					example, updating the board for a miss, or a hit etc.
 * =============================================================================
 */
 
#include ".\h\updateBoardFunc.h"
#include ".\h\main.h"

/*
	Updates the board with a miss
	@input: INT[2](Cordinate where to update the miss)
	@output: NULL
*/
void updateMiss(cordinate cord) {
	if(userTurn) { // if it is users turn
		if(p2PB[cord.y][cord.x] == WATER) { // it there is water then its a miss
			p1GB[cord.y][cord.x] = MISS; // update board | PLAYER 1 GUESS BOARD
			p2PB[cord.y][cord.x] = MISS; // this updates the other person that it was a miss, dont really need it | we will decided as a group meeting
		}
	} else {
		if(p1PB[cord.y][cord.x] == WATER) {
			p2GB[cord.y][cord.x] = MISS; // update board | PLAYER 2 GUESS BOARD
			p1PB[cord.y][cord.x] = MISS; // this updates the other person that it was a miss, dont really need it | we will decided as a group meeting
		}
	}
}

/*
	Updates the board by a hit
	@input: INT[2](Cordinate where to update the hit)
	@output: NULL
*/
void updateHit(cordinate cord) {
	if(userTurn) {  // if it is users turn
		if(p2PB[cord.y][cord.x] == SHIP) { // if there is a ship at location then it is a hit
			p1GB[cord.y][cord.x] = HIT; // update both boards | PLAYRER 1 GUESS BOARD
			p2PB[cord.y][cord.x] = HIT; // PLAYER 2 PLAYER BOARD
		}
	} else { // computer's turn
		if(p1PB[cord.y][cord.x] == SHIP) { // see above
			p1PB[cord.y][cord.x] = HIT;
			p2GB[cord.y][cord.x] = HIT;
		}
	}
}

/*
	Fires a missle, returns if hit or not
	@input: INT[2](Cordinate to test if hit or not)
	@output: BOOL(Was it a hit or not)
 */
bool hit(cordinate cord) {
	if(userTurn)
		if(p2PB[cord.y][cord.x] == SHIP) { // checks to see if there is a ship at the cordinate
			updateHit(cord); // updates the hit in the board
			return true; // returns that it was a hit
		} else {
			updateMiss(cord); // updates the board with a miss
			return false; // returns that the fire was a miss
		}
	else // see above
		if(p1PB[cord.y][cord.x] == SHIP) {
			updateHit(cord);
			return true;
		} else {
			updateMiss(cord);
			return false;
		}
}
