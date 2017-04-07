/* 
 * Original Work Copyright (c) 2016 Team 42
 * Modified Work Copyright (c) 2017 The Gupta Empire - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Aryan Gupta <me@theguptaempire.net>
 * 
 * =============================================================================
 * @author 			Aryan Gupta
 * @project 		Console BattleShip
 * @title 			Main
 * @date			2017-02-16 (YYYY-MM-DD)
 * @fversion			6.7.2
 * @description 	This is a game that lets you play battleship against the computer
 * =============================================================================
 */

#include "info.h"
#define _PRINTINFO std::cout << '\n' << R_PROJNAME << " v" << R_PVERSION << " by " << R_AUTHOR << '\n' << R_COPYRIGHT << '\n' << R_COMMENTS << "\n\n\n" // Legal and Informational

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

//HEADER
#include ".\h\updateBoardFunc.h"
#include ".\h\gameFunc.h"
#include ".\h\computerAI.h"
#include ".\h\setUp.h"
#include ".\h\display.h"
#include ".\h\main.h"

using namespace std;

//CONSTANT VARS
const bool USERCHEAT = false; // do u want to be a cheater?
const bool P2CHEAT = false; // how to lose 101

const char WATER = ' ';
const char SHIP = '#';
const char HIT = 'X';
const char MISS = 'O';
//END CONSTANT VARS

//WORKING VARS
int difficulty = 0;
bool userTurn = (time(0) % 2 == 0); // randomizes whos first turn it is (not really random but random enough)
vector< vector<char> > p1GB;
vector< vector<char> > p2GB;
vector< vector<char> > p1PB;
vector< vector<char> > p2PB;
//http://stackoverflow.com/questions/8666378/detect-windows-or-linux-in-c-c
    #if defined(__unix__) || defined(linux) //__unix__ is usually defined by compilers targeting Unix systems
        char CLEAR_SCREEN[] = "clear";
    #elif defined(_WIN32) || defined(WIN32) // _Win32 is usually defined by compilers targeting 32 or 64 bit Windows systems
        char CLEAR_SCREEN[] = "cls";
    #endif
//END WORKING VARS


/* ========================================================
	START HERE
===========================================================*/
/*
	main function
	@input: NULL
	@output: INT(EXIT CODE)
 */
int main() {
	_PRINTINFO;
	
	srand(time(0)); //seed this rand

	//ask for difficulty and instantize respective boards
	bool valid = false; // turns to true if the user inputed a valid character
	do {
		valid = oneTimeMessage(); // sets up the board and sets difficulty
	} while(!valid); // has the user put in a valid character?

	system(CLEAR_SCREEN);
	/*
		Checks to see if someone has won, if no one has won it will continue with the turns. if someon has won then it will end out of the while loop
	*/
	do { // check if some one has won
		if(userTurn) {
			displayBoards(); // display the current status of the board
			if(USERCHEAT == true)
				displayCheatBoards();
		}
		turn(); // does a turn
		askContinue(); // asks the player if s/he wants to continue
		changeTurn(); // changes turn to the other person
	} while(!playerWin()); // has a player won? if no then repeat

	displayBoards(); // displays the board one last time
	if(!USERCHEAT)
		displayCheatBoards(); // annd the oponent's board
	cout << getWinner() << endl; // gets the winner and outputs it
	
	cout << "Press enter to exit...";
	cin.ignore(1000, '\n');
	cin.get();
	
	return 0; // END
}