/*
*   FOSS tic-tac-toe terminal game
*   Copyright (C) 2022 Wagner Bertholdo Bughausen
*   <https://github.com/wagner-b>, <wagb2b2@gmail.com>
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#define DIM 3

/*
*  This is a simple tic-tac-toe game (also known as noughts and crosses, or Xs and Os).
*  This game runs on the terminal (or cmd). It is meant to be human player vs
*  human player, the computer does not play.
*/

void intro();
void fillWithZeros(int matrix[][DIM]);
void printGrid(int matrix[][DIM]);
void play(int matrix[][DIM], int turn);
int checkRow(int matrix[][DIM]);
int checkColumn(int matrix[][DIM]);
int checkDiagonal(int matrix[][DIM]);
int checkDraw(int matrix[][DIM]);
int checkEnd(int matrix[][DIM]);
void gameLogic(int matrix[][DIM]);
void cleanTerminal();
void showScoreboard();
void menu();
void showLicense();

unsigned int victoriesO = 0;
unsigned int victoriesX = 0;

int main()
{
	menu();
	return 0;
}


void intro()
{
	printf("\tWelcome to tic-tac-toe!\n");
	printf("  Here, the player 1 (O) starts, ");
	printf("and take turns with player 2 (X).\n");
	printf("  The winner is the player who succeeds ");
	printf("to fill three of their marks in a ");
	printf("horizontal, vertical, or diagonal row.\n");
	printf("  In each turn, each player chooses a row ");
	printf("and a column to place their mark on the grid.\n");
	printf("  The upper row is row 1, the middle row ");
	printf("is row 2, and the bottom row is row 3.\n");
	printf("  The left column is column 1, the middle ");
	printf("column is column 2, and the right column ");
	printf("is column 3.\n\n");
}


void fillWithZeros(int matrix[][DIM])
{
	int row, column;

	for(row=0; row<DIM; row++)
		for(column=0; column<DIM; column++)
			matrix[row][column] = 0;

	printGrid(matrix);
}


void printGrid(int matrix[][DIM])
{
	int row, column, i;

	printf("\n");
	for(i = 0; i < 5; i++)
	{
		for(column = 0; column < 3; column++)
		{
			if(column == 0)
				printf("  ");

			if(i % 2 == 0)
			{
				row = i / 2;

				if(matrix[row][column] == 0)
					printf("     ");

				else if(matrix[row][column] == 1)
					printf("  O  ");

				else if(matrix[row][column] == -1)
					printf("  X  ");
			}
			else
				printf("-----");

			if(column < 2)
				printf("|");

		}
		printf("\n");
	}
	printf("\n");
}


void play(int matrix[][DIM], int turn)
{
	int row, column;

	printf("----> Player %d ", (turn % 2) + 1);

	if(turn % 2)
		printf("(X):\n");
	else
		printf("(O):\n");

	do
	{
		printf("Type a row [1 - 3]: ");
		scanf("%d", &row);
		printf("Type a column [1 - 3]: ");
		scanf("%d", &column);

		row--;
		column--;

		// checks if that position is already occupied
		if(matrix[row][column] != 0)
		{
			printf("Error! This position on the grid is already occupied!\n");
			printGrid(matrix);
		}
	}
	while(matrix[row][column] != 0);

	// adds -1 for the X (turn is odd) or 1 for the O (turn is pair)
	if(turn % 2)
		matrix[row][column] = -1;
	else
		matrix[row][column] = 1;

	printGrid(matrix);
}


int checkRow(int matrix[][DIM])
{
	int row, column, sum = 0;

	for(row=0; row<DIM; row++)
	{
		for(column=0; column<DIM; column++)
			sum += matrix[row][column];

		// checks if O won
		if(sum == 3)
		{
			printf("The winner is player 1 (O)!!!\n");
			victoriesO++;
			return 1;
		}
		// checks if X won
		if(sum == -3)
		{
			printf("The winner is player 2 (X)!!!\n");
			victoriesX++;
			return 1;
		}

		sum = 0;
	}
	return 0;
}


int checkColumn(int matrix[][DIM])
{
	int row, column, sum = 0;

	for(column=0; column<DIM; column++)
	{
		for(row=0; row<DIM; row++)
			sum += matrix[row][column];

		// checks if O won
		if(sum == 3)
		{
			printf("The winner is player 1 (O)!!!\n");
			victoriesO++;
			return 1;
		}
		// checks if X won
		if(sum == -3)
		{
			printf("The winner is player 2 (X)!!!\n");
			victoriesX++;
			return 1;
		}
		sum = 0;
	}
	return 0;
}


int checkDiagonal(int matrix[][DIM])
{
	int row, mainDiag = 0, secDiag = 0;

	for(row=0; row<DIM; row++)
	{
		// "main diagonal"
		mainDiag += matrix[row][row];
		// "secondary diagonal"
		secDiag += matrix[row][DIM-row-1];
	}
	// checks if O won
	if(mainDiag == 3 || secDiag == 3)
	{
		printf("The winner is player 1 (O)!!!\n");
		victoriesO++;
		return 1;
	}
	// checks if X won
	if(mainDiag == -3 || secDiag == -3)
	{
		printf("The winner is player 2 (X)!!!\n");
		victoriesX++;
		return 1;
	}
	return 0;
}


int checkDraw(int matrix[][DIM])
{
	int row, column;

	for(row=0; row<DIM; row++)
	{
		for(column=0; column<DIM; column++)
		{
			if(matrix[row][column] == 0)
				return 0;
		}
	}

	printf("The game ended in a draw!\n");
	return 1;
}


int checkEnd(int matrix[][DIM])
{
	if(checkRow(matrix))
		return 1;
	if(checkColumn(matrix))
		return 1;
	if(checkDiagonal(matrix))
		return 1;
	if(checkDraw(matrix))
		return 1;

	return 0;
}


void gameLogic(int matrix[][DIM])
{
	int i, turn = 0;
	printf("\tLet's start playing!!!\n\n");

	// no need to check whether the game ended in the first 4 turns
	for(i=0; i<4; i++)
	{
		play(matrix, turn);
		turn++;
	}

	// game loop
	do
	{
		play(matrix, turn);
		turn++;
	}
	while(checkEnd(matrix) == 0);
}


void cleanTerminal()
{
	int i;
	for(i = 0; i < 50; i++)
		printf("\n");
}


void showScoreboard()
{
	printf("\n\n    Scoreboard \n\n");
	printf("   O   v.s   X \n");
	printf("   %u         %u \n\n", victoriesO, victoriesX);
}


void menu()
{
	int option, matrix[DIM][DIM];
	do
	{
		printf("\n\t Menu: \n\n");
		printf("1 - Show help / tutorial \n");
		printf("2 - Play! \n");
		printf("3 - Show scoreboard \n");
		printf("4 - Show license notice \n");
		printf("0 - Exit \n\n");
		printf("Choose an option [0 - 4]: ");
		scanf("%d", &option);

		switch(option)
		{
			case 0:
				break;
			case 1:
				cleanTerminal();
				intro();
				break;
			case 2:
				cleanTerminal();
				fillWithZeros(matrix);
				gameLogic(matrix);
				break;
			case 3:
				showScoreboard();
				break;
			case 4:
				cleanTerminal();
				showLicense();
				break;
			default:
				cleanTerminal();
				printf("Invalid option, please try again.\n");
		}
	}
	while(option != 0);
}


void showLicense()
{
	printf(" FOSS tic-tac-toe terminal game \n");
	printf(" Copyright (C) 2022 Wagner Bertholdo Burghausen \n");
	printf(" <https://github.com/wagner-b>, <wagb2b2@gmail.com> \n\n");
	printf(" This program is free software: you can redistribute it and/or modify \n");
	printf(" it under the terms of the GNU General Public License as published by \n");
	printf(" the Free Software Foundation, either version 3 of the License, or \n");
	printf(" (at your option) any later version. \n\n");
	printf(" This program is distributed in the hope that it will be useful, \n");
	printf(" but WITHOUT ANY WARRANTY; without even the implied warranty of \n");
	printf(" MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the \n");
	printf(" GNU General Public License for more details. \n\n");
	printf(" You should have received a copy of the GNU General Public License \n");
	printf(" along with this program. If not, see <https://www.gnu.org/licenses/>. \n");
}
