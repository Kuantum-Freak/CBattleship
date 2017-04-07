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
 * @title 			Computer AI
 * @date			2017-02-16 (YYYY-MM-DD)
 * @fversion		7.2.0
 * @description 	
 * =============================================================================
 */
 
#include <cstdlib>
#include <iostream>
#include <array>
#include <vector>
using std::vector;
using std::cout;
using std::endl;
using std::out_of_range;

#include ".\h\computerAI.h"
#include ".\h\main.h"
#include ".\h\display.h"

#define LOG(a) if(_DEBUG_) {std::cout << a << std::endl;} // will be removed if false and optimizations is turned on
#define _DEBUG_ true

/* 
	@summary		Converts x and y to a cordinate structs
	
	@param			1: x cordinate
					2: y cordinate
	@return			cordinate
 */
cordinate convert(int x, int y) {
	return cordinate{x, y};
}

/*
	Randomizes the computers choice of where it will hit
	@intput: NULL
	@output: Cordinate (Cordinate of Computer AI)
*/
cordinate computerAI() {
	//return convert(rand() % difficulty, rand() % difficulty); // Dont want to use complicated algoritm
	
	cordinate cord;
	
	// displayBoards();
	displayCheatBoards();
	
	if(P2CHEAT) { // runs if the computer wants to cheat or not
		for(int o = 0; o < difficulty; o++) // go through the board of the other player and...
			for(int i = 0; i < difficulty; i++)
				if(p1PB[o][i] == SHIP) // find the first place where there is a ship
					return convert(i, o); // hit there
	}
	
	if       (difficulty == 5) { // if we are playing at a low difficulty
		return convert(rand() % difficulty, rand() % difficulty); // random value
	} else if(difficulty == 6) {
		return AI_easy();
	} else if(difficulty == 7) { // if we are playing at a high difficulty
		return AI_hard();
	}
	
	return cord;
}

cordinate AI_hard() {
	vector<possibleHit> poss = getReport();
	int points[poss.size()];
	
	if(poss.size() == 0) {
		LOG( "could not find a hit, adding random choice" );
		return convert(rand() % difficulty, rand() % difficulty); // random value
	}
	
	LOG("sending possible cordinates for analysis");
	for(unsigned i = 0; i < poss.size(); ++i) {
		points[i] = analyze(poss[i].c, poss[i].dir);
	}
	
	LOG("Results: ")
	for(unsigned i = 0; i < poss.size(); ++i) {
		LOG((char)(poss[i].c.x + 65) << poss[i].c.y << " " << poss[i].dir << " : " << points[i] << " ");
	}
	
	int maxI = 0;
	int max = 0;
	for(unsigned i = 0; i < poss.size(); ++i) {
		if(points[max] < points[i]) {
			maxI = i;
			max = points[i];
		}
	}
	
	/*if(max == 0) {
		LOG("We have sunk a ship and we dont know where to hit next so we will randomize")
		return convert(rand() % difficulty, rand() % difficulty);
	}*/
	
	LOG("found a good hit, aiming at " << (char)(poss[maxI].c.x + 65) << poss[maxI].c.y);
	return poss[maxI].c;
}

int analyze(const cordinate &c, const int dir) {
	LOG("\n\nChecking: " << (char)(c.x + 65) << c.y);
	LOG("Direction is: " << dir);
	int points = 0;
	if       (dir == 0) { // from up, go back down =======================================
		for(int i = 0; i < 4; ++i) {
			try {
				if(p2GB.at(c.y + i).at(c.x) == HIT)
					points += 1;
			} catch(out_of_range &e) {}
		}
		LOG("Cord is part of " << points);
		int numOfHitsP = 0;
		//p2GB.at(c.y - 1).at(c.x)
		for(int i = 1; i < 4; ++i) {
			try {
				if(p2GB.at(c.y - 1).at(c.x + i) == HIT) {
					LOG("Found Hit at: " << (char)(c.x + i) << c.y - 1);
					numOfHitsP++;
				}
			} catch(out_of_range &e) {}
			try {
				if(p2GB.at(c.y - 1).at(c.x - i) == HIT) {
					LOG("Found Hit at: " << (char)(c.x - i) << c.y - 1);
					numOfHitsP++;
				}
			} catch(out_of_range &e) {}
		}
		LOG("numOfHitsP is: " << numOfHitsP);
		if(numOfHitsP > 1) {
			LOG("numOfHitsP is greater than 2, resetting...")
			points = -5;
		}
	} else if(dir == 1) { // from down, go back up =========================================
		for(int i = 0; i < 4; ++i) {
			try {
				if(p2GB.at(c.y - i).at(c.x) == HIT)
					points += 1;
			} catch(out_of_range &e) {}
		}
		LOG("Cord is part of " << points);
		int numOfHitsP = 0;
		//p2GB.at(c.y - 1).at(c.x)
		for(int i = 1; i < 4; ++i) {
			try {
				if(p2GB.at(c.y + 1).at(c.x + i) == HIT) {
					LOG("Found Hit at: " << (char)(c.x + i) << c.y + 1);
					numOfHitsP++;
				}
			} catch(out_of_range &e) {}
			try {
				if(p2GB.at(c.y + 1).at(c.x - i) == HIT) {
					LOG("Found Hit at: " << (char)(c.x - i) << c.y + 1);
					numOfHitsP++;
				}
			} catch(out_of_range &e) {}
		}
		LOG("numOfHitsP is: " << numOfHitsP);
		if(numOfHitsP > 2) {
			LOG("numOfHitsP is greater than 2, resetting...")
			points = -5;
		}
	} else if(dir == 2) { // from right go back left ========================================
		for(int i = 0; i < 4; ++i) {
			try {
				if(p2GB.at(c.y).at(c.x - i) == HIT)
					points += 1;
			} catch(out_of_range &e) {}
		}
		LOG("Cord is part of " << points);
		int numOfHitsP = 0;
		for(int i = 1; i < 4; ++i) {
			try {
				if(p2GB.at(c.y + i).at(c.x + 1) == HIT) {
					LOG("Found Hit at: " << (char)(c.x + 1) << c.y + i);
					numOfHitsP++;
				}
			} catch(out_of_range &e) {}
			try {
				if(p2GB.at(c.y - i).at(c.x + 1) == HIT) {
					LOG("Found Hit at: " << (char)(c.x + 1) << c.y - i);
					numOfHitsP++;
				}
			} catch(out_of_range &e) {}
		}
		LOG("numOfHitsP is: " << numOfHitsP);
		if(numOfHitsP > 2) {
			LOG("numOfHitsP is greater than 2, resetting...")
			points = -5;
		}
	} else if(dir == 3) { // from left, going back right ==========================================
		for(int i = 0; i < 4; ++i) {
			try {
				if(p2GB.at(c.y).at(c.x + i) == HIT) // we want to go the other way of the direction we came from
					points += 1;
			} catch(out_of_range &e) {}
		}	
		LOG("Cord is part of " << points);
		int numOfHitsP = 0;
		//p2GB.at(c.y - 1).at(c.x)
		for(int i = 1; i < 4; ++i) {
			try {
				if(p2GB.at(c.y + i).at(c.x - 1) == HIT) {
					LOG("Found Hit at: " << (char)(c.x - 1) << c.y + i);
					numOfHitsP++;
				}
			} catch(out_of_range &e) {}
			try {
				if(p2GB.at(c.y - i).at(c.x - 1) == HIT) {
					LOG("Found Hit at: " << (char)(c.x - 1) << c.y - i);
					numOfHitsP++;
				}
			} catch(out_of_range &e) {}
		}
		LOG("numOfHitsP is: " << numOfHitsP);
		if(numOfHitsP > 2) {
			LOG("numOfHitsP is greater than 2, resetting...")
			points = -5;
		}
	} else {
		LOG("The World Broke");
	}
	return points;
}

std::vector<possibleHit> getReport() {
	typedef possibleHit PH;
	
	vector<PH> cords;
	
	for(int i = 0; i < difficulty; i++) { // go through the board
		for(int j = 0; j < difficulty; j++) {
			// LOG("Currently checking " << (char)(j + 65) << i);
			if(p2GB[i][j] == HIT) { // if the current board member is a hit
				// LOG("found hit at " << (char)(j + 65) << i);
				int length[4] = {1, 1, 1, 1};
				for(int k = 1; k < 4; k++) { // go outwards
				// START PRELIM ASSESMENT OF FIRST FOUND HIT ===========================================
					try {
						//LOG("Checking above by " << k);
						if(p2GB.at(i - k).at(j) == HIT) {// check up
							length[0]++;
							// LOG("found another hit above");
						} else if(k == 1 && p2GB.at(i - k).at(j) == MISS) {
							length[0] = -5;
						}
					} catch(out_of_range &e) {}
					
					try {
						//LOG("Checking below by " << k);
						if(p2GB.at(i + k).at(j) == HIT) {// check down
							// LOG( "Trying 2.1" );
							length[1]++;
							// LOG( "found another hit below" );
						} else if(k == 1 && p2GB.at(i + k).at(j) == MISS) {
							length[1] = -5;
						}
					} catch(out_of_range &e) {}
					
					try {
						//LOG("Checking right by " << k);
						if(p2GB.at(i).at(j + k) == HIT) {// check right
							// LOG( "Trying 3.1" );
							length[2]++;
							// LOG( "found another hit right" );
						} else if(k == 1 && p2GB.at(i).at(j + k) == MISS) {
							length[2] = -5;
						}
					} catch(out_of_range &e) {}
					
					try {
						//LOG( "Checking left by " << k );
						if(p2GB.at(i).at(j - k) == HIT) {// check left
							// LOG( "Trying 4.1" );
							length[3]++;
							// LOG( "found another hit left" );
						} else if(k == 1 && p2GB.at(i).at(j - k) == MISS) {
							length[3] = -5;
						}
					} catch(out_of_range &e) {}
				} // END ASSESMENT ========================================================
				
				if(length[0] < 5) { // max ship size
					try {
						// LOG( "length at 0: " << length[0] );
						for(int k = 3; k >= 1; --k) {
							// LOG( "k: " << k );
							if( length[0] == k &&
								p2GB.at(i - k).at(j) != MISS &&
								p2GB.at(i - k).at(j) != HIT
							) {
								// LOG( "Found possible hit upward of " << k << " length. Adding " << (char)(j + 65) << i - k);
								cords.push_back(PH{convert(j, i - k), 0});
							}
						}
					} catch(out_of_range &e) {}
				}
				
				if(length[1] < 5) {
					try {
						// LOG( "length at 1: " << length[1] );
						for(int k = 3; k >= 1; --k) {
							// LOG( "k: " << k );
							if( length[1] == k &&
								p2GB.at(i + k).at(j) != MISS && 
								p2GB.at(i + k).at(j) != HIT
							) {
								// LOG( "Found possible hit downward of " << k << " length. Adding " << (char)(j + 65) << i + k);
								cords.push_back(PH{convert(j, i + k), 1});
							}
						}
					} catch(out_of_range &e) {}
				}
				
				if(length[2] < 5) {
					try {
						// LOG( "length at 2: " << length[2] );
						for(int k = 3; k >= 1; --k) {
							// LOG( "k: " << k );
							if(	length[2] == k && 
								p2GB.at(i).at(j + k) != MISS &&
								p2GB.at(i).at(j + k) != HIT
							) {
								// LOG( "Found possible hit right of " << k << " length. Adding " << (char)(j + 65 + k) << i);
								cords.push_back(PH{convert(j + k, i), 2});
							}
						}
					} catch(out_of_range &e) {}
				}
				
				if(length[3] < 5) {
					try {
						// LOG( "length at 3: " << length[3] );
						for(int k = 3; k >= 1; --k) {
							// LOG( "k: " << k );
							if( length[3] == k &&
								p2GB.at(i).at(j - k) != MISS &&
								p2GB.at(i).at(j - k) != HIT
							) {
								// LOG( "Found possible hit left of " << k << " length. Adding " << (char)(j + 65 - k) << i);
								cords.push_back(PH{convert(j - k, i), 3});
							}
						}
					} catch(out_of_range &e) {}
				}
			}
		}
	}
	return cords;
}

cordinate AI_easy() {
	for(int i = 0; i < difficulty; i++) { // go through the board
		for(int j = 0; j < difficulty; j++) {
			LOG("Currently checking " << (char)(j + 65) << i);
			//TODO skip the ones we have alread cheaked for
			if(p2GB[i][j] == HIT) { // if the current board member is a hit
				LOG( "found hit" );
				int length[4] = {1, 1, 1, 1};
				for(int k = 1; k < 4; k++) { // go outwards
				// START PRELIM ASSESMENT OF FIRST FOUND HIT ===========================================
					try {
						LOG("Checking above by " << k);
						if(p2GB.at(i - k).at(j) == HIT) {// check up
							length[0]++;
							LOG("found another hit above");
						} else if(k == 1 && p2GB.at(i - k).at(j) == MISS) {
							length[0] = -5;
						}
					} catch(out_of_range &e) {}
					
					try {
						LOG("Checking below by " << k);
						if(p2GB.at(i + k).at(j) == HIT) {// check down
							LOG( "Trying 2.1" );
							length[1]++;
							LOG( "found another hit below" );
						} else if(k == 1 && p2GB.at(i + k).at(j) == MISS) {
							length[1] = -5;
						}
					} catch(out_of_range &e) {}
					
					try {
						LOG("Checking right by " << k);
						if(p2GB.at(i).at(j + k) == HIT) {// check right
							LOG( "Trying 3.1" );
							length[2]++;
							LOG( "found another hit right" );
						} else if(k == 1 && p2GB.at(i).at(j + k) == MISS) {
							length[2] = -5;
						}
					} catch(out_of_range &e) {}
					
					try {
						LOG( "Checking left by " << k );
						if(p2GB.at(i).at(j - k) == HIT) {// check left
							LOG( "Trying 4.1" );
							length[3]++;
							LOG( "found another hit left" );
						} else if(k == 1 && p2GB.at(i).at(j - k) == MISS) {
							length[3] = -5;
						}
					} catch(out_of_range &e) {}
				} // END ASSESMENT ========================================================
				
				LOG("length: " << length[0]  << " " << length[1] << " " << length[2] << " " << length[3]);
				int max = 0;
				for(int i = 0; i < 4; ++i) {
					if(length[i] > length[max] && length[i] < 5)
						max = i;
				}
				LOG("Max: " << length[max] << "  :  " << max);
				if(max == 0) { // max ship size
					try {
						LOG( "length at 0: " << length[0] );
						for(int k = 3; k >= 1; --k) {
							LOG( "k: " << k );
							if(length[0] == k && p2GB.at(i - k).at(j) != MISS) {
								LOG( "Found that there is an upward of " << k << " length. Firing at " << (char)(j + 65) << i - k);
								return convert(j, i - k);
							}
						}
					} catch(out_of_range &e) {}
				}
				
				if(max == 1) {
					try {
						LOG( "length at 1: " << length[1] );
						for(int k = 3; k >= 1; --k) {
							LOG( "k: " << k );
							if(length[1] == k && p2GB.at(i + k).at(j) != MISS) {
								LOG( "Found that there is an downward of " << k << " length. Firing at " << (char)(j + 65) << i + k);
								return convert(j, i + k);
							}
						}
					} catch(out_of_range &e) {}
				}
				
				if(max == 2) {
					try {
						LOG( "length at 2: " << length[2] );
						for(int k = 3; k >= 1; --k) {
							LOG( "k: " << k );
							if(length[2] == k && p2GB.at(i).at(j + k) != MISS) {
								LOG( "Found that there is an right of " << k << " length. Firing at " << (char)(j + 65 + k) << i);
								return convert(j + k, i);
							}
						}
					} catch(out_of_range &e) {}
				}
				
				if(max == 3) {
					try {
						LOG( "length at 3: " << length[3] );
						for(int k = 3; k >= 1; --k) {
							LOG( "k: " << k );
							if(length[3] == k && p2GB.at(i).at(j - k) != MISS) {
								LOG( "Found that there is an left of " << k << " length. Firing at " << (char)(j + 65 - k) << i);
								return convert(j - k, i);
							}
						}
					} catch(out_of_range &e) {}
				}
			}
		}
	}
	LOG( "could not find a hit, randomizing..." );
	return convert(rand() % difficulty, rand() % difficulty); // random value
}