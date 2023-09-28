#pragma once
#include <string>

//used to change the size of the board
#define WIDTH 5
#define HEIGHT 5

enum CellType
{
	Empty,
	Dug,
	Treasure,
	Found
};

extern std::string chosenColumn;
extern std::string chosenRow;
extern std::string nbTreasures;

extern int cells[WIDTH][HEIGHT];

extern int maxTries;
extern int nbTreasuresFound;
extern int tries;

extern bool restart;

int TreasureNear(int x, int y);

bool HitMiss();
bool PlayAgain();
bool ValidNumber();

void GetValue();
void PlaceTreasures();
void DrawPlayfield();
void AskPlayer();
void ResetGame();