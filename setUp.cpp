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
 * @title 			Set Up Board
 * @date			2017-02-16 (YYYY-MM-DD)
 * @fversion			6.7.2
 * @description 	
 * =============================================================================
 */

#include <cstdlib>
#include <vector>

using std::vector;

#include ".\h\setUp.h"
#include ".\h\main.h"

/*
	sets up the computer's board
	@input: NULL
	@output: NULL
 */
void setUpComputerBoard() {
	/*
		INDEX 0: BATLESHIP
		INDEX 1: DYSTROYER
		INDEX 2: SUBMARINE
	*/
	int r[3] = {(rand() % (difficulty - 3)), (rand() % (difficulty - 2)), (rand() % (difficulty - 1))}; // set a starting y value for each ship
	int c[3] = {(rand() % (difficulty - 3)), (rand() % (difficulty - 2)), (rand() % (difficulty - 1))}; // set a starting x value for each ship
	bool b[3]; // set orientation for each ship

	for(int i = 0; i < 3; i++)
        if(rand() % 2 == 0)
            b[i] = true;
        else
            b[i] = false; // TRUE MEANS UP AND DOWN FALSE IF ITS GOING LEFT AND RIGHT
	
	checkShips(r, c, b);
	
	//placement
	//battleship
	if(b[0]) // If the battleship goes UP AND DOWN go through the ROWS
		for(int i = 0; i < 4; i++)
			p2PB[r[0] + i][c[0]] = SHIP;
	else // If the battleship goes UP AND DOWN go through the COLUMNS
		for(int i = 0; i < 4; i++)
			p2PB[r[0]][c[0] + i] = SHIP;
	//the dystroyer
	if(b[1]) // If the dystroyer goes UP AND DOWN go through the ROWS
		for(int i = 0; i < 3; i++)
			p2PB[r[1] + i][c[1]] = SHIP;
	else // If the dystroyer goes UP AND DOWN go through the COLUMNS
		for(int i = 0; i < 3; i++)
			p2PB[r[1]][c[1] + i] = SHIP;
	//the submarine
	if(b[2]) // If the submarine goes UP AND DOWN go through the ROWS
		for(int i = 0; i < 2; i++)
			p2PB[r[2] + i][c[2]] = SHIP;
	else // If the submarine goes UP AND DOWN go through the COLUMNS
		for(int i = 0; i < 2; i++)
			p2PB[r[2]][c[2] + i] = SHIP;
}

/*
	sets up the player board
	@input: NULL
	@output: NULL
 */
void setUpPlayerBoard() {
	/*
		INDEX 0: BATLESHIP
		INDEX 1: DYSTROYER
		INDEX 2: SUBMARINE
	*/
	int r[3] = {(rand() % (difficulty - 3)), (rand() % (difficulty - 2)), (rand() % (difficulty - 1))}; // set a starting y value for each ship
	int c[3] = {(rand() % (difficulty - 3)), (rand() % (difficulty - 2)), (rand() % (difficulty - 1))}; // set a starting x value for each ship
	bool b[3]; // set orientation for each ship
	
	for(int i = 0; i < 3; i++)
        if(rand() % 2 == 0)
            b[i] = true; // TRUE MEANS UP AND DOWN
        else
            b[i] = false;	//FALSE MEANS ITS GOING LEFT AND RIGHT

	checkShips(r, c, b);
	
	//PLACE THE SHIPS
	//th battleship
	if(b[0]) // If the battleship goes UP AND DOWN go through the ROWS
		for(int i = 0; i < 4; i++)
			p1PB[r[0] + i][c[0]] = SHIP;
	else // If the battleship goes UP AND DOWN go through the COLUMNS
		for(int i = 0; i < 4; i++)
			p1PB[r[0]][c[0] + i] = SHIP;

	//the dystroyer
	if(b[1]) // If the dystroyer goes UP AND DOWN go through the ROWS
		for(int i = 0; i < 3; i++)
			p1PB[r[1] + i][c[1]] = SHIP;
	else // If the dystroyer goes UP AND DOWN go through the COLUMNS
		for(int i = 0; i < 3; i++)
			p1PB[r[1]][c[1] + i] = SHIP;

	//the submarine
	if(b[2]) // If the submarine goes UP AND DOWN go through the ROWS
		for(int i = 0; i < 2; i++)
			p1PB[r[2] + i][c[2]] = SHIP;
	else // If the submarine goes UP AND DOWN go through the COLUMNS
		for(int i = 0; i < 2; i++)
			p1PB[r[2]][c[2] + i] = SHIP;
}

/*
	Make the actual board the right size and will it with water
	@input: NULL
	@output: NULL
*/
void makeBoards() {
	vector<char> vec (difficulty, WATER); // creates a row of water
	//set up board
	for(int i = 0; i < difficulty; i++) { // adds a row of water to the 2d array at the end
        p1GB.push_back(vec);
        p2GB.push_back(vec);
        p1PB.push_back(vec);
        p2PB.push_back(vec);
	}
}

/*
	Creates the board
	@input: NULL
	@output: NULL
*/
void setBoard() {
	makeBoards();
	setUpComputerBoard();
	setUpPlayerBoard();
}

void checkShips(int* r, int* c, bool* b) {
	//CROSSING ALGORITHM
	/*
		This algorithm determines if any of the ships are crossing each other. goes through all the x and y valuies of all the ships and makes sure that they arent the same. If they are the same then it will change the placement of the smaller ship
	*/
	
	//make sure ships arent crossing
	int crossing;
	do {
		crossing = -1;
		//BATLESHIP...
		for(int bs = 0; bs < 4; bs++) {// itteratir for the battleship
			//...AND DYSTROYER
			for(int dy = 0; dy < 3; dy++) { //itterator of the dystroyer
				if(b[0]) { // If the battleship goes UP AND DOWN change the ROWS
					if(b[1]) { // If the dystroyer goes UP AND DOWN change the ROWS
						if((r[0] + bs == r[1] + dy) && (c[0] == c[1])) {// check crossablity at point
							crossing = 1; //Distroyer needs to be reset
						}
					} else {// if the dystoyer goes LEFT AND RIGHT change the COLUMNS
						if((r[0] + bs == r[1]) && (c[0] == c[1] + dy)) { // check crossablity at point
							crossing = 1; //Distroyer needs to be reset
						}
					}
				} else { // If the BATTLESHIP goes LEFT AND RIGHT change the COLUMNS
					if(b[1]) { // If the dystroyer goes UP AND DOWN change the ROWS
						if((r[0] == r[1] + dy) && (c[0] + bs == c[1])) // check crossablity at point
							crossing = 1; //Distroyer needs to be reset
					} else { // if the dystoyer goes LEFT AND RIGHT change the COLUMNS
						if((r[0] == r[1]) && (c[0] + bs == c[1] + dy)) { // check crossablity at point
							crossing = 1; //Distroyer needs to be reset
						}
					}
				}
			}
			//...AND SUBMARINE
			for(int sm = 0; sm < 2; sm++) {
				if(b[0]) { // If the battleship goes UP AND DOWN change the ROWS
					if(b[2]) { // If the submarine goes UP AND DOWN change the ROWS
						if((r[0] + bs == r[2] + sm) && (c[0] == c[2])) { // check crossablity at point
							crossing = 2; //submarine needs to be reset
						}
					} else { // if the dystoyer goes LEFT AND RIGHT change the COLUMNS
						if((r[0] + bs == r[2]) && (c[0] == c[2] + sm)) { // check crossablity at point
							crossing = 2; //submarine needs to be reset
						}
					}
				} else { // If the BATTLESHIP goes LEFT AND RIGHT change the COLUMNS
					if(b[2]) { // If the submarine goes UP AND DOWN change the ROWS
						if((r[0] == r[2] + sm) && (c[0] + bs == c[2])) { // check crossablity at point
							crossing = 2; //submarine needs to be reset
						}
					} else { // if the dystoyer goes LEFT AND RIGHT change the COLUMNS
						if((r[0] == r[2]) && (c[0] + bs == c[2] + sm)) { // check crossablity at point
							crossing = 2; //submarine needs to be reset
						}
					}
				}
			}
		}
		//DYSTROYER AND SUBMARINE
		for(int dy = 0; dy < 3; dy++) { // itteratir for the Dystroyer
			for(int sm = 0; sm < 2; sm++) { //itterator of the submarine
				if(b[1]) { // If the dystoyer goes UP AND DOWN change the ROWS
					if(b[2]) { // If the submarine goes UP AND DOWN change the ROWS
						if((r[1] + dy == r[2] + sm) && (c[1] == c[2])) { // check crossablity at point
							crossing = 2; //submarine needs to be reset
						}
					} else { // if the submarine goes LEFT AND RIGHT change the COLUMNS
						if((r[1] + dy == r[2]) && (c[1] == c[2] + sm)) { // check crossablity at point
							crossing = 2; //submarine needs to be reset
						}
					}
				} else { // If the dystoyer goes LEFT AND RIGHT change the COLUMNS
					if(b[2]) { // If the submarine goes UP AND DOWN change the ROWS
						if((r[1] == r[2] + sm) && (c[1] + dy == c[2])) { // check crossablity at point
							crossing = 2; //submarine needs to be reset
						}
					} else { // if the submarine goes LEFT AND RIGHT change the COLUMNS
						if((r[1] == r[2]) && (c[0] + dy == c[2] + sm)) { // check crossablity at point
							crossing = 2; //submarine needs to be reset
						}
					}
				}
			}
		}
		switch(crossing) {
            case 1:// The destroyer is crossing the battleship, change battleship
                r[crossing] = (rand() % (difficulty - 2));
                c[crossing] = (rand() % (difficulty - 2));
                break;
            case 2: // if battleship and submarine are crossing, change submarine
                r[crossing] = (rand() % (difficulty - 1));
                c[crossing] = (rand() % (difficulty - 1));
                break;
		}
	} while(crossing != -1);
}