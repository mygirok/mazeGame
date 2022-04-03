#include <iostream>
#include <conio.h>

using namespace std;

/*
0 : wall
1 : way
2 : starting point
3 : end point
*/

void SetMaze(char Maze[21][21])
{
	strcpy_s(Maze[0],  "21100000000000000000");
	strcpy_s(Maze[1],  "00111111111100000000");
	strcpy_s(Maze[2],  "00100010000111111100");
	strcpy_s(Maze[3],  "01100010000000000100");
	strcpy_s(Maze[4],  "01000011111000111100");
	strcpy_s(Maze[5],  "01000000000111100000");
	strcpy_s(Maze[6],  "01100000000100000000");
	strcpy_s(Maze[7],  "00100000000111111000");
	strcpy_s(Maze[8],  "00001110000000001000");
	strcpy_s(Maze[9],  "01111011111111111000");
	strcpy_s(Maze[10], "01000000000000000000");
	strcpy_s(Maze[11], "01111100111111100000");
	strcpy_s(Maze[12], "00000111100000111110");
	strcpy_s(Maze[13], "01111100000000000010");
	strcpy_s(Maze[14], "01000000001111111110");
	strcpy_s(Maze[15], "01111110011000000000");
	strcpy_s(Maze[16], "00000010010000000000");
	strcpy_s(Maze[17], "01111110011111000000");
	strcpy_s(Maze[18], "01000000000001100000");
	strcpy_s(Maze[19], "11000000000000111113");
	Maze =
	{
	};
}

void Output(char Maze[21][21])
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (Maze[i][j] == '0')
				cout << "■";

			else if (Maze[i][j] == '1')
				cout << "  ";

			else if (Maze[i][j] == '2')
				cout << "★";

			else if (Maze[i][j] == '3')
				cout << "◎";
		}

		cout << endl;
	}
}

int main()
{
	// 20 X 20 maze
	char strMaze[21][21];
	
	// maze setting
	SetMaze(strMaze);

	while (true)
	{
		system("cls");
		// maze output
		Output(strMaze);
		cout << "w : up, s : down, a : left, d : right, q : quit ";
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;
	}

	return 0;
}
