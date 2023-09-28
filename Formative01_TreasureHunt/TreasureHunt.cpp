#include <iostream>
#include "TreasureHunt.h"

std::string chosenColumn = "0";
std::string chosenRow = "0";
std::string nbTreasures;

int cells[WIDTH][HEIGHT];

int maxTries;
int nbTreasuresFound = 0;
int tries = 0;

bool restart;

int TreasureNear(int x, int y)
{
	int treasureAround = 0;
	for (int row = y - 1; row < y + 2; row++)
	{
		for (int column = x - 1; column < x + 2; column++)
		{
			if(row >= 0 && row <= HEIGHT - 1 && column >= 0 && column <= WIDTH - 1)
			{
				if (cells[row][column] == Treasure)
				{
					treasureAround++;
				}
			}
		}
	}
	return treasureAround;
}

bool HitMiss() //compares the value of the tile hit by the player with the Cell_type enum to determine what happens to said value
{
	system("cls");
	const int targetValue = cells[std::stoi(chosenRow) - 1][std::stoi(chosenColumn) - 1];
	switch (targetValue)
	{
	case Empty: //the tile is empty, its value is changed to DUG
		cells[std::stoi(chosenRow) - 1][std::stoi(chosenColumn) - 1] = Dug;
		tries++;
		std::cout << "Nope, nothing here." << std::endl << std::endl;
		return false;
	case Dug:
	case Found: //the two cases where the tile has already been checked
		std::cout << "You've already checked this spot, pick another one." << std::endl << std::endl;
		return false;
	case Treasure: //the tile contains a treasure, its value is changed to FOUND
		cells[std::stoi(chosenRow) - 1][std::stoi(chosenColumn) - 1] = Found;
		tries++;
		nbTreasuresFound++;
		if (nbTreasuresFound < std::stoi(nbTreasures)) //depending on whether or not it is the last chest, continue the game by returning false or stops it by returning true
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
bool PlayAgain() //asks the player if they want to play another round
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
	return false;
}

bool ValidNumber(const std::string& inputString, const int min, const int max) //global function used in other ones to determine if a number is a valid option for a specific player input
{
	bool isInputValid = true;
	do
	{
		isInputValid = true;
		for (int i = 0; i < inputString.size(); i++) //checks every character of the string
		{
			if (!isdigit(inputString[i])) //if it is not a digit, returns false
			{
				return false;
			}
			if (isInputValid && i == inputString.size() - 1) //makes sure that it checks the whole string, and does not consider all the numbers before the first letter as a valid option
			{
				if (std::stoi(inputString) > max || std::stoi(inputString) < min) //checks if the number is in the specified range and returns true if it is
				{
					return false;
				}
				return true;
			}
		}
	} while (!isInputValid);
	return false;
}


void DrawPlayfield() //function that gives the player information and draws the board
{
	std::cout << "Remaining tries: " << maxTries - tries << "/" << maxTries << "\t\t Chests found: " << nbTreasuresFound << "/" << nbTreasures << std::endl << std::endl;
	for (int row = 0; row < HEIGHT; row++)
	{
		for (int column = 0; column < WIDTH; column++)
		{
			switch (cells[row][column])
			{
			case Empty:
				std::cout << "-\t";
				break;
			case Dug:
				std::cout << TreasureNear(column, row) << "\t";
				break;
			case Treasure:
				//std::cout << "!\t"; //uncomment this line and comment the next one to have the chests be visible from the start
				std::cout << "-\t";
				break;
			case Found:
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
void ResetGame() //resets the variables and arrays
{
	tries = 0;
	nbTreasuresFound = 0;
	for (int row = 0; row < HEIGHT; row++) {
		for (int column = 0; column < WIDTH; column++) {
			cells[row][column] = 0;
		}
	}
	system("cls");
}
void PlaceTreasures()
{
	std::cout << "Pick how many treasures you want on the map, from 1 to " << HEIGHT * WIDTH << ":" << std::endl;
	std::cin >> nbTreasures; //asks the player how many chests they want
	while (!ValidNumber(nbTreasures, 1, HEIGHT * WIDTH)) //checks if their answer is a valid one
	{
		std::cout << std::endl;
		std::cout << "Please enter a valid number." << std::endl;
		std::cin >> nbTreasures;
	}
	std::cout << std::endl;
	if (std::stoi(nbTreasures) == WIDTH * HEIGHT) //just a little easter egg if the player decides to have each tile be a chest
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

	for (int i = 0; i < std::stoi(nbTreasures); i++) //replaces random values of the array with treasure chests, also checks that it is not already a chest
	{
		const int tempRandWidth = rand() % WIDTH;
		const int tempRandHeight = rand() % HEIGHT;
		if (cells[tempRandWidth][tempRandHeight] == Treasure)
		{
			i--;
		}
		else
		{
			cells[tempRandWidth][tempRandHeight] = Treasure;
		}

	}
	maxTries = (WIDTH * HEIGHT + std::stoi(nbTreasures)) / 2; //determines the maximum number of tries allowed for this specific board. I'm not really satisfied with the ratio.
}
void AskPlayer() //asks the player for the coordinates where they want to dig and checks if they are valid options
{
	std::cout << "Pick a row in which to dig:" << std::endl;
	std::cin >> chosenRow;

	while (!ValidNumber(chosenRow, 1, HEIGHT))
	{
		std::cout << std::endl << "This row does not exist." << std::endl << std::endl;
		std::cout << "Pick a row in which to dig:" << std::endl;
		std::cin >> chosenRow;
	}
	std::cout << std::endl;


	std::cout << "Pick a column in which to dig:" << std::endl;
	std::cin >> chosenColumn;

	while (!ValidNumber(chosenColumn, 1, WIDTH))
	{
		std::cout << std::endl << "This column does not exist." << std::endl << std::endl;
		std::cout << "Pick a column in which to dig:" << std::endl;
		std::cin >> chosenColumn;
	}
	std::cout << std::endl;
}