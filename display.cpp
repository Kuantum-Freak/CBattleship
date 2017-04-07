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
 * @title 			Display Stuff
 * @date			2017-02-16 (YYYY-MM-DD)
 * @fversion			6.7.2
 * @description 	
 * =============================================================================
 */
 
#include <iostream>
using std::cout;
using std::endl;

#include ".\h\display.h"
#include ".\h\main.h"
#include ".\h\setUp.h"
#include ".\h\gameFunc.h"


/*
	Diplays the one time message, does things such as get difficulty, position of the ships and stuff like that
	@input: NULL
	@output: NULL
*/
bool oneTimeMessage() {
	char dif; // Difficulty temp var
	cout << "What difficulty would you like to play at? (type ? for help and how to play)" << endl << "e for Easy :: m for Medium :: h for Hard" << endl << "Level>>";
	cin >> dif;
	cin.ignore(1);
	switch(dif) {  // sets up difficulty
		case 'e': // easy '5'
			difficulty = 5;
			setBoard();
			return true;
		case 'm': // medium '6'
			difficulty = 6;
			setBoard();
			return true;
		case 'h': // hard '7'
			difficulty = 7;
			setBoard();
			return true;
		case '?': // help text
			help();
			return false;
		default:
			cout << "Please enter a valid difficulty" << endl;
			return false;
	}
}

/*
	Displays the current configuration of the board
	@input: NULL
	@output: NULL
*/
void displayBoards() {
	cout << "This is the current configuration of your board: " << endl;
	cout << HIT << " means hit :: " << MISS << " means miss :: " << WATER << " means water :: " << SHIP << " means unhit" << endl; // output standard message
	cout << endl << " ";
	for(int i = 0; i < difficulty; ++i) // displays the cordinate system for the left right direction (x)
		cout << " " << (char)(i + 65);
	cout << endl;
	for(int o = 0; o < difficulty; ++o) { // display players hitboard
		cout << o << " "; // output row number (y cordinate)
		for(int i = 0; i < difficulty; ++i) {
			cout << p1PB[o][i] << " ";
		}
		cout << endl;
	}

	cout << endl;
	cout << "This is the current configuration of your guess board: " << endl;
	cout << HIT << " means hit :: " << MISS << " means miss :: " << WATER << " means water :: " << SHIP << " means unhit" << endl; // output standard message
	cout << endl << " ";
	for(int i = 0; i < difficulty; ++i)
		cout << " " << (char)(i + 65);
	cout << endl;
	for(int o = 0; o < difficulty; ++o) { // Display the players Guessboard
		cout << o << " ";
		for(int i = 0; i < difficulty; ++i)
			cout << p1GB[o][i] << " ";
		cout << endl;
	}
}

/*
	Displays the other player's board to cheat
	@input: NULL
	@output: NULL
*/
void displayCheatBoards() {
	cout << "\n\n" << "TIME TO CHEAT: COMPUTER PLAYER BOARD" << endl << " ";
	for(int i = 0; i < difficulty; ++i)
		cout << " " << (char)(i + 65);
	cout << endl;
	for(int o = 0; o < difficulty; ++o) { // Display the computer's Playerboard
		cout << o << " ";
		for(int i = 0; i < difficulty; ++i)
			cout << p2PB[o][i] << " ";
		cout << endl;
	}

	cout << endl;
	cout << "TIME TO CHEAT: COMPUTER GUESS BOARD" << endl << " ";;
	for(int i = 0; i < difficulty; ++i)
		cout << " " << (char)(i + 65);
	cout << endl;
	for(int o = 0; o < difficulty; ++o) { // Display the computer's Guessboard
		cout << o << " ";
		for(int i = 0; i < difficulty; ++i)
			cout << p2GB[o][i] << " ";
		cout << endl;
	}

}

/*
	help script
	@input: NULL
	@output: NULL
 */
void help() {
	cout << "HELP!" << endl;
	cout << "During your turn, "
		 << "please enter a cordinate, the order of the cordinate wont matter. X0 or 0X works. "
		 << "This is where your ship will fire the missile at that location. "
		 << "Your Guess board will be updated showing whether that was a hit or a miss."
		 << "When your openent fires, your player board will be updated inticating if the computer missed you or hit you."
		 << "Heep playing untill all the ships are sunk.\n";
	cout << "\n\n";
	cout << "This is typically a two player game each person has a grid that is similar to the images below where the columns are denoted by a letter and the rows a number"
		 << "Each person has a fleet of three ships (Battleship, Submarine, and Destroyer). Each of the ships are assigned a number of holes. The image below illustrates the breakdown of the number of holes for each type of ship."
		 << "Each player will randomly distribute the three ships. The player is allowed the place ships horizontally or vertically but not diagonally. An example placement of both player’s ships is shown below"
		 << "Each player takes a turn by giving a row and column combination to try to sink the opposing persons ship(s). After each player call the opposing player indicates a correctly guessed row and column (R & C) combination that contains part(s) of a ship by saying the word “Hit” (User gets unlimited turns so long as they continue to guess correct R & C combination that result in a “Hit”) or “Miss” if the player’s R & C combination did not contain any part of a ship(s). An example of a “Miss” would be if player one gives the R & C combination of “B1”, this would result in player 2 saying “Miss” since that combination did not impact any of their fleet. Likewise, a “Hit” example would be if the same player would have given the R & C combination of “A1”. Player 2 would have said “Hit” and player 1 would have been given another turn to try to give a R & C combination that would result in another “Hit”."
		 << "The game continuous until one player has sunk all the other players’ fleet (three ships). At the conclusion of the game the looser concedes defeat and the two players shake hands.\n\n";
}
