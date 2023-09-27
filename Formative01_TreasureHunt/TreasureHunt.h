#pragma once
#include <string>

//used to change the size of the board
#define WIDTH 5
#define HEIGHT 5

enum Cell_type
{
	EMPTY,
	DUG,
	TREASURE,
	FOUND
};

extern std::string chosen_column;
extern std::string chosen_row;
extern std::string nb_treasures;

extern int cells[WIDTH][HEIGHT];

extern int max_tries;
extern int nb_treasures_found;
extern int target_value;
extern int tries;

extern bool restart;

int treasure_near(int x, int y);

bool hit_miss();
bool play_again();
bool valid_number();

void get_value();
void place_treasures();
void draw_playfield();
void ask_player();
void reset_game();