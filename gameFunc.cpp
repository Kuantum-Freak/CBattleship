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
 * @title 			gameFunc
 * @date			2017-02-16 (YYYY-MM-DD)
 * @fversion		6.8.2
 * @description 	
 * =============================================================================
 */
 
#include <iostream>
#include <string>

using std::string;

#include ".\h\gameFunc.h"
#include ".\h\main.h"
#include ".\h\display.h"
#include ".\h\computerAI.h"
#include ".\h\updateBoardFunc.h"

/*
	Gets the number of hits || p is the player in question (1 for player one, 2 for player w)
	@input: INT(Which user's hot to get)
	@putput: INT(number of hits)
*/
int getHits(int p) {
	int val = 0; // val is the number of hits

	if(p == 1) { // if player one is in question then go thorugh player 1's board and add up all the hits
		for(int q = 0; q < difficulty; ++q) { // go through board
			for(int r = 0; r < difficulty; ++r) {
				if(p1PB[q][r] == HIT) { // if its a hit, add it up to val
					val++;
				}
			}
		}
	} else if(p == 2) { // player 2 (see above)
		for(int q = 0; q < difficulty; ++q) {
			for(int r = 0; r < difficulty; ++r) {
				if(p2PB[q][r] == HIT) {
					val++;
				}
			}
		}
	} else
		val = -1;
	return val;
}

/*
	Gets the winner of the match, because there are 9 spots where the ship resides, if we add up all of the hits and get 9 then the other player won
	@input: NULL
	@output: STRING(name of the player that won FORMATTED)
*/
string getWinner() {
	if(getHits(1) == 9) // if player 1's board has 9 hits then player 2 wins
		return "Player 2 wins!";
	else if(getHits(2) == 9) // if player 2's board has 9 hits then player 1 wins
		return "Player 1 wins!";
    return "No Winner";
}

/*
	returns true if a player has won
	@input: BOOL(has a player won)
	@output: NULL
*/
bool playerWin() {
	return (getHits(1) == 9) || (getHits(2) == 9); // if either board has 9 hits (4 from battleship, 3 from dystoyer, and 2 from sub) then a player has won
}

/*
	Does a turn
	@input: NULL
	@output: NULL
 */
void turn() {
	using std::cin;
	using std::cout;
	using std::endl;
	
	cordinate cord; // stored the coridatne that will be fired at
	string cordFull = ""; // temp var for user input
	bool valid = false; // is the users input valid
	if(userTurn) { // if its users turn
		do { // do loop START
			cout << "Where would you like to fire your missile?" << endl << "Fire Here!>>"; // set up asking for user input
			std::string buffer;
			getline(cin, buffer);
			if(buffer.empty()) {
				cout << "Randomizing..." << endl;
				do {
					cord.x = (rand() % difficulty);
					cord.y = (rand() % difficulty);
				} while(p1GB[cord.y][cord.x] == MISS || p1GB[cord.y][cord.x] == HIT);
				cout << "Firing at " << (char)(cord.x + 65) << cord.y << endl;
			} else {
				cordFull = std::string(buffer); // take user input
				if(cordFull.compare("cheat") == 0) {
					displayCheatBoards();
					continue;
				} 
				if(cordFull.size() > 2) { // makes sure that the sordinate is 2 characters long
					cout << "Please enter a valid cordinate. Cordinates are 2 characters long, You can enter it X0 or 0X." << endl;
					continue;
				}
				// convert user input to a char array
				if(cordFull.at(0) >= 65) { // This means the X cordinate is first
					cord.x = cordFull.at(0) - 65; // 1's Digit - X Digit - LETTER
					cord.y = cordFull.at(1) - 48; // 10's Digit - Y digit - NUMBER
				} else { // this means the Y cordinate is First
					cord.x = cordFull.at(1) - 65; // 10's Digit - X Digit - LETTER
					cord.y = cordFull.at(0) - 48; // 1's Digit - Y digit - NUMBER
				}
			}
			if(!((cord.y >= 0 && cord.y < difficulty) && (cord.x >= 0 && cord.x < difficulty))) { // makes sure the cordinate is within the bounds of the game map
				cout << "Your cordinate is outside the range of the battlefield, please enter a valid cordinate" << endl;
				continue;
			} else if(p1GB[cord.y][cord.x] == MISS || p1GB[cord.y][cord.x] == HIT) { // makes sure the use hasnt already played at this spot
				cout << "This cordinate is not valid, You may have already guessed this or hit it" << endl;
				continue;
			} else // everything is good continue with the hitting the board etc
				valid = true;
		} while(!valid);

		if(hit(cord)) { // checks if the cord is a hit or not
			cout << "Congrats that is a hit" << endl;
		} else {
			cout << "Sorry you missed" << endl;
		}
	} else {
		cout << "Computer is thinking..." << endl;
		cord = computerAI(); // run computer AI

		cout << "The computer has fired at " << (char)(cord.x + 65) << cord.y << endl; // output the cordinate where the comp fired
		if(hit(cord)) // is that it hit or a miss?
			cout << "The computer hit you!" << endl;
		else
			cout << "The computer missed!" << endl;
	}
}

/*
	Asks the player if he or she wants to continue or clear the board
	@input: NULL
	@output: NULL
*/
void askContinue() {
	char r = 0;
	std::cin.clear();
	std::cout << "Continue...";
	r = std::cin.get();
	if(r == '\n')
		system(CLEAR_SCREEN);
}

/*
	Takes the turn and flips it so the other players turn (userTurn is true if it is the user's turn)
	@input: NULL
	@output: NULL
 */
void changeTurn() {
	userTurn = !userTurn; // takes userTurn and flips it
}
