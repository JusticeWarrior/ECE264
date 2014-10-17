#include "answer06.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	
	int i;
	for (i = 0; i < (int)strlen(input[0]); i++)
	{
		if (input[0][i] == ' ')
		{
			Maze* maze = Create_Maze(input, w, h);
			Print_Directions_Recur(maze, i, 0, 3);
			Dispose_Maze(maze);
			return;
		}
	}

	fprintf(stdout, "There needs to be an entrance at the top of the maze dumbass!");
	
}

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

void Print_Directions_Recur(Maze* maze, int x, int y, int direction)
{
	maze->maze[y][x] = 'O';

	switch (direction)
	{
		case UP:
			// Check to the right
			if (x + 1 < maze->w && maze->maze[y][x + 1] == ' ')
			{
				fprintf(stdout, "E 1\n");
				Print_Directions_Recur(maze, x + 1, y, RIGHT);
				fprintf(stdout, "W 1\n");
			}
			// Check up
			if (y - 1 >= 0 && maze->maze[y - 1][x] == ' ')
			{
				fprintf(stdout, "N 1\n");
				Print_Directions_Recur(maze, x, y - 1, UP);
				fprintf(stdout, "S 1\n");
			}
			// Check to the left
			if (x - 1 >= 0 && maze->maze[y][x - 1] == ' ')
			{
				fprintf(stdout, "W 1\n");
				Print_Directions_Recur(maze, x - 1, y, LEFT);
				fprintf(stdout, "E 1\n");
			}
			break;
		case RIGHT:
			// Check down
			if (y + 1 < maze->h && maze->maze[y + 1][x] == ' ')
			{
				fprintf(stdout, "S 1\n");
				Print_Directions_Recur(maze, x, y + 1, DOWN);
				fprintf(stdout, "N 1\n");

			}
			// Check to the right
			if (x + 1 < maze->w && maze->maze[y][x + 1] == ' ')
			{
				fprintf(stdout, "E 1\n");
				Print_Directions_Recur(maze, x + 1, y, RIGHT);
				fprintf(stdout, "W 1\n");
			}
			// Check up
			if (y - 1 >= 0 && maze->maze[y - 1][x] == ' ')
			{
				fprintf(stdout, "N 1\n");
				Print_Directions_Recur(maze, x, y - 1, UP);
				fprintf(stdout, "S 1\n");
			}
			break;
		case DOWN:
			// Check to the right
			if (x + 1 < maze->w && maze->maze[y][x + 1] == ' ')
			{
				fprintf(stdout, "E 1\n");
				Print_Directions_Recur(maze, x + 1, y, RIGHT);
				fprintf(stdout, "W 1\n");
			}
			// Check to the left
			if (x - 1 >= 0 && maze->maze[y][x - 1] == ' ')
			{
				fprintf(stdout, "W 1\n");
				Print_Directions_Recur(maze, x - 1, y, LEFT);
				fprintf(stdout, "E 1\n");
			}
			// Check down
			if (y + 1 < maze->h && maze->maze[y + 1][x] == ' ')
			{
				fprintf(stdout, "S 1\n");
				Print_Directions_Recur(maze, x, y + 1, DOWN);
				fprintf(stdout, "N 1\n");
			}
			break;
		case LEFT:
			// Check to the left
			if (x - 1 >= 0 && maze->maze[y][x - 1] == ' ')
			{
				fprintf(stdout, "W 1\n");
				Print_Directions_Recur(maze, x - 1, y, LEFT);
				fprintf(stdout, "E 1\n");
			}
			// Check down
			if (y + 1 < maze->h && maze->maze[y + 1][x] == ' ')
			{
				fprintf(stdout, "S 1\n");
				Print_Directions_Recur(maze, x, y + 1, DOWN);
				fprintf(stdout, "N 1\n");

			}
			// Check up
			if (y - 1 >= 0 && maze->maze[y - 1][x] == ' ')
			{
				fprintf(stdout, "N 1\n");
				Print_Directions_Recur(maze, x, y - 1, UP);
				fprintf(stdout, "S 1\n");
			}
			break;
	}
}