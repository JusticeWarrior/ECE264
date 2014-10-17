#include "answer06.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	char ** maze;
	int w;
	int h;
} Maze;

void Print_Directions_Recur(Maze* maze, int x, int y, int direction);
Maze* Create_Maze(char ** input, int w, int h);
void Dispose_Maze(Maze* maze);

Maze* Create_Maze(char ** input, int w, int h)
{
	Maze* maze = malloc(sizeof(Maze));
	maze ->maze = input;
	maze ->w = w;
	maze ->h = h;

	return maze;
}

void Dispose_Maze(Maze* maze)
{
	free(maze);
}

void print_directions(char** input, int w, int h)
{
	Maze* maze = Create_Maze(input, w, h);

	Print_Directions_Recur(maze, 4, 1, 1);

	Dispose_Maze(maze);
}

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

void Print_Directions_Recur(Maze* maze, int x, int y, int direction)
{
	switch (direction)
	{
		case UP:
			// Check to the right
			if (x + 1 < maze->w && maze->maze[y][x + 1] == ' ')
			{
				fprintf(stdout, "I can move Right");
			}
			break;
		case RIGHT:
			break;
		case DOWN:
			break;
		case LEFT:
			break;
	}
}