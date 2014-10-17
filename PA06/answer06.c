#include "answer06.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	char ** maze;
	int w;
	int h;
} Maze;

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

	Dispose_Maze(maze);
}

//void Print_Directions_Recur(char** maze, int w, int h, )