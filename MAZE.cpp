/*
 * MAZE.cpp
 * Author:Yun Pei Chao 
 */
#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#define size 8
#define startX 0
#define startY 1

void searchpath(char array[size][size], int x, int y, int step[size*size][2], int *goal, int n);
void printpath(char array[size][size], int step[size*size][2], int *goal, int n);

int main()
{
	char maze[size][size] = { { ' ', ' ', 'X', 'X', 'X', 'X', 'X', ' ' },
							{ ' ', 'X', ' ', ' ', ' ', 'X', 'X', ' ' },
							{ ' ', 'X', ' ', 'X', ' ', 'X', 'X', ' ' },
							{ ' ', 'X', ' ', 'X', ' ', ' ', ' ', ' ' },
							{ ' ', ' ', ' ', 'X', 'X', 'X', 'X', ' ' },
							{ ' ', 'X', ' ', ' ', ' ', 'X', 'X', ' ' },
							{ ' ', 'X', 'X', 'X', ' ', 'X', 'X', ' ' },
							{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' } };

	int i, j, goal = 0, n = 0;
	int step[size*size][2] = { 0 };

	for (i = 0; i < size; i++)
	{

		for (j = 0; j < size; j++)
		{
			if (maze[i][j] == ' ')
				printf("□");
			else
				printf("Ⅹ");
		}
		printf("\n");


	}
	printf("\n");

	searchpath(maze, startX, startY, step, &goal, n);


	if (goal == 0)
		printf("There is no path to the end.\n ");
	else
		printf("There are %d paths to the end.\n", goal);


	system("pause");
	return(0);
}
void searchpath(char array[size][size], int x, int y, int step[size*size][2], int *goal, int n)
{
	array[x][y] = 's';                                                         //路徑
	step[n][0] = x;                                                            //路徑座標
	step[n][1] = y;
	n += 1;                                                                    //步數

	if (x < size&&y < size)
	{
		
		if (array[x - 1][y] == ' ' &&x != 0)                                   //向左
			searchpath(array, x - 1, y, step, goal, n);
		if (array[x + 1][y] == ' '&& x != size - 1)                            //向右
			searchpath(array, x + 1, y, step, goal, n);
		if (array[x][y - 1] == ' '&&y != 0)                                    //向上
			searchpath(array, x, y - 1, step, goal, n);
		if (array[x][y + 1] == ' ' && y != size - 1)                           //向下 
			searchpath(array, x, y + 1, step, goal, n);

	}
	if (x == size - 1 && y == size - 1)
	{
		*goal += 1;                                                            //路徑數
		printpath(array, step, goal, n);

	}

	array[x][y] = ' ';
	n -= 1;

}
void printpath(char array[size][size], int step[size*size][2], int *goal, int n)
{
	int i, j;
	printf("Path %d:", *goal);
	for (i = 0; i < n; i++)
	{
		printf("(%d,%d)", step[i][0], step[i][1]);                               //印出走過座標      
		if (step[i][0] != 7 || step[i][1] != 7)
			printf("->");
	}
	printf("\n");
	for (i = 0; i < size; i++)
	{

		for (j = 0; j < size; j++)                                                //印出路徑地圖
		{
			if (array[i][j] == 's')
				printf("■");
			else if (array[i][j] == ' ')
				printf("□");
			else
				printf("Ⅹ");
		}
		printf("\n");
	}
	printf("--------------------------\n");
}
