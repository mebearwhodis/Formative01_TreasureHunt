// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TreasureHunt.h"

/*
 Issues:
 If the user enters a number that is too big, the program crashes
 Could not find a(n accessible at our level) way to make the board dynamic and have the player choose the size
*/
int main()
{
	do { //base game loop, used to ask the player if they want to play another round
		srand(time(nullptr)); //gets a random seed
		reset_game(); //resets the variables and arrays
		place_treasures(); //asks the player how many chests they want and places them randomly on the board, also calculates the max number of tries allowed

		bool all_treasures; //used by the following do...while to determine if there are still hidden chests on the board

		do //base gameplay loop once the board is initialised
		{
			draw_playfield(); //draws the board
			ask_player(); //asks the player what tile they want to dig at
			all_treasures = hit_miss(); //all_treasures is true only if all the treasure chests are found
		} while (all_treasures == false && tries < max_tries); //as long as there are treasures chests and tries remaining, the game continues
		draw_playfield();
		if (all_treasures == true) //if all the treasures are found before the player runs out of tries, they win
		{
			std::cout << "Good job, you won!" << std::endl << std::endl;
		}
		else //if not, they lose
		{
			std::cout << "Aww shucks, you ran out of tries! Better luck next time... :(" << std::endl << std::endl;
		}
	} while (play_again());
}