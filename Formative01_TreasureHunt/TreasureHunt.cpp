#include <iostream>
#include "TreasureHunt.h"

std::string chosen_column;
std::string chosen_row;
std::string nb_treasures;

int cells[WIDTH][HEIGHT];

int max_tries;
int nb_treasures_found = 0;
int tries = 0;

bool restart;

bool hit_miss() //compares the value of the tile hit by the player with the Cell_type enum to determine what happens to said value
{
	system("cls");
	const int target_value = cells[std::stoi(chosen_row) - 1][std::stoi(chosen_column) - 1];
	switch (target_value)
	{
	case EMPTY: //the tile is empty, its value is changed to DUG
		cells[std::stoi(chosen_row) - 1][std::stoi(chosen_column) - 1] = DUG;
		tries++;
		std::cout << "Nope, nothing here." << std::endl << std::endl;
		return false;
	case DUG:
	case FOUND: //the two cases where the tile has already been checked
		std::cout << "You've already checked this spot, pick another one." << std::endl << std::endl;
		return false;
	case TREASURE: //the tile contains a treasure, its value is changed to FOUND
		cells[std::stoi(chosen_row) - 1][std::stoi(chosen_column) - 1] = FOUND;
		tries++;
		nb_treasures_found++;
		if (nb_treasures_found < std::stoi(nb_treasures)) //depending on whether or not it is the last chest, continue the game by returning false or stops it by returning true
		{
			std::cout << "You found a treasure chest! Keep digging to find the other ones!" << std::endl << std::endl;
			return false;
		}
		std::cout << "You found the last chest!" << std::endl << std::endl;
		return true;
	default:
		return false;
	}
}
bool play_again() //asks the player if they want to play another round
{
	do
	{
		bool restart = true;
		char answer;
		std::cout << "Would you like to play again? Y/N" << std::endl;
		std::cin >> answer;
		switch (tolower(answer)) { //compares the answer to determine the outcome
		case 'y':
			return true;
		case 'n':
			exit(0);
		default:
			std::cout << std::endl << "Please enter a valid answer: Y/N" << std::endl << std::endl;
			restart = false;
		}
	} while (!restart);
}
bool valid_number(const std::string& input_string, const int min, const int max) //global function used in other ones to determine if a number is a valid option for a specific player input
{
	bool is_input_valid = true;
	do
	{
		is_input_valid = true;
		for (int i = 0; i < input_string.size(); i++) //checks every character of the string
		{
			if (!isdigit(input_string[i])) //if it is not a digit, returns false
			{
				return false;
			}
			if (is_input_valid && i == input_string.size() - 1) //makes sure that it checks the whole string, and does not consider all the numbers before the first letter as a valid option
			{
				if (std::stoi(input_string) > max || std::stoi(input_string) < min) //checks if the number is in the specified range and returns true if it is
				{
					return false;
				}
				return true;
			}
		}
	} while (!is_input_valid);
	return false;
}

void draw_playfield() //function that gives the player information and draws the board
{
	std::cout << "Remaining tries: " << max_tries - tries << "/" << max_tries << "\t\t Chests found: " << nb_treasures_found << "/" << nb_treasures << std::endl << std::endl;
	for (int row = 0; row < HEIGHT; row++)
	{
		for (int column = 0; column < WIDTH; column++)
		{
			switch (cells[row][column])
			{
			case EMPTY:
				std::cout << "-\t";
				break;
			case DUG:
				std::cout << "o\t";
				break;
			case TREASURE:
				//std::cout << "!\t"; //uncomment this line and comment the next one to have the chests be visible from the start
				std::cout << "-\t";
				break;
			case FOUND:
				std::cout << "X\t";
				break;
			default:
				std::cout << "-\t";
				break;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
}
void reset_game() //resets the variables and arrays
{
	tries = 0;
	nb_treasures_found = 0;
	for (int row = 0; row < HEIGHT; row++) {
		for (int column = 0; column < WIDTH; column++) {
			cells[row][column] = 0;
		}
	}
	system("cls");
}
void place_treasures()
{
	std::cout << "Pick how many treasures you want on the map, from 1 to " << HEIGHT * WIDTH << ":" << std::endl;
	std::cin >> nb_treasures; //asks the player how many chests they want
	while (!valid_number(nb_treasures, 1, HEIGHT * WIDTH)) //checks if their answer is a valid one
	{
		std::cout << std::endl;
		std::cout << "Please enter a valid number." << std::endl;
		std::cin >> nb_treasures;
	}
	std::cout << std::endl;
	if (std::stoi(nb_treasures) == WIDTH * HEIGHT) //just a little easter egg if the player decides to have each tile be a chest
	{
		system("cls");
		std::cout << std::endl << "There's no shame in picking the easy mode..." << std::endl << std::endl;
		system("pause");
		system("cls");
		std::cout << std::endl << "I mean, I would never. But you do you." << std::endl << std::endl;
		system("pause");
		system("cls");
		std::cout << std::endl << "Really, I promise, there's no judgment here!" << std::endl << std::endl;
		system("pause");
	}

	for (int i = 0; i < std::stoi(nb_treasures); i++) //replaces random values of the array with treasure chests, also checks that it is not already a chest
	{
		const int temp_rand_width = rand() % WIDTH;
		const int temp_rand_height = rand() % HEIGHT;
		if (cells[temp_rand_width][temp_rand_height] == TREASURE)
		{
			i--;
		}
		else
		{
			cells[temp_rand_width][temp_rand_height] = TREASURE;
		}

	}
	max_tries = (WIDTH * HEIGHT + std::stoi(nb_treasures)) / 2; //determines the maximum number of tries allowed for this specific board. I'm not really satisfied with the ratio.
}
void ask_player() //asks the player for the coordinates where they want to dig and checks if they are valid options
{
	std::cout << "Pick a row in which to dig:" << std::endl;
	std::cin >> chosen_row;

	while (!valid_number(chosen_row, 1, HEIGHT))
	{
		std::cout << std::endl << "This row does not exist." << std::endl << std::endl;
		std::cout << "Pick a row in which to dig:" << std::endl;
		std::cin >> chosen_row;
	}
	std::cout << std::endl;


	std::cout << "Pick a column in which to dig:" << std::endl;
	std::cin >> chosen_column;

	while (!valid_number(chosen_column, 1, WIDTH))
	{
		std::cout << std::endl << "This column does not exist." << std::endl << std::endl;
		std::cout << "Pick a column in which to dig:" << std::endl;
		std::cin >> chosen_column;
	}
	std::cout << std::endl;
}