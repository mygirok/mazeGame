﻿#include <iostream>
#include <conio.h>

using namespace std;

/*
0 : wall
1 : way
2 : starting point
3 : end point
4 : bomb
5 : bomb effect 
*/

struct _tagPoint
{
	int x;
	int y;
};

// typedef : redefine the type
typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

typedef struct _tagPlayer
{
	_tagPoint	tPos;
	bool		bWallPush;
	bool		bTransparency;
	int			iBombPower;
}PLAYER, *PPLAYER;

void SetMaze(char Maze[21][21], PPLAYER pPlayer, PPOINT pStartPos,
	PPOINT pEndPos)
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	pPlayer->tPos = *pStartPos;

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

void Output(char Maze[21][21], PPLAYER pPlayer)
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (Maze[i][j] == '4')
				cout << "♨";

			else if (pPlayer->tPos.x == j && pPlayer->tPos.y == i)
				cout << "☆";

			else if (Maze[i][j] == '0')
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

	cout << "Bomb power : " << pPlayer->iBombPower << endl;
	cout << "Pass wall : ";
	if (pPlayer->bTransparency)
		cout << "ON\t";

	else
		cout << "OFF\t";

	cout << "Push wall : ";
	if (pPlayer->bWallPush)
		cout << "ON" << endl;

	else
		cout << "OFF" << endl;
}

void MoveUp(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y - 1 >= 0)
	{
		// check wall
		if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '0' &&
			Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4')
		{
			--pPlayer->tPos.y;
		}
	}
}

void MoveDown(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y + 1 < 20)
	{
		// check wall
		if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '0' &&
			Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4')
		{
			++pPlayer->tPos.y;
		}
	}
}

void MoveRight(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x + 1 < 20)
	{
		// check wall
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '0' &&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4')
		{
			++pPlayer->tPos.x;
		}
	}
}

void MoveLeft(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x - 1 < 20)
	{
		// check wall
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0' &&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4')
		{
			--pPlayer->tPos.x;
		}
	}
}


void MovePlayer(char Maze[21][21], PPLAYER pPlayer, char cInput)
{
	switch (cInput)
	{
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayer);
		break;
	case 's':
	case 'S':
		MoveDown(Maze, pPlayer);
		break;
	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayer);
		break;
	case 'd':
	case 'D':
		MoveRight(Maze, pPlayer);
		break;
	}
}

void CreateBomb(char Maze[21][21], const PPOINT pPlayer,
	PPOINT pBombArr, int* pBombCount)
{
	if (*pBombCount == 5)
		return;
	
	for (int i = 0; i < *pBombCount; ++i)
	{
		if (pPlayer->x == pBombArr[i].x &&
			pPlayer->y == pBombArr[i].y)
			return;
	}

	pBombArr[*pBombCount] = *pPlayer;
	++(*pBombCount);

	Maze[pPlayer->y][pPlayer->x] = '4';
}

void Fire(char Maze[21][21], PPOINT pPlayer, PPOINT pBombArr,
	int* pBombCount)
{
	for (int i = 0; i < *pBombCount; ++i)
	{
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';

		// Move player to start point if hit by bomb
		if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y)
		{
			pPlayer->x = 0;
			pPlayer->y = 0;
		}
		if (pBombArr[i].y - 1 >= 0)
		{
			if (Maze[pBombArr[i].y - 1][pBombArr[i].x] == '0')
				Maze[pBombArr[i].y - 1][pBombArr[i].x] = '1';

			// Move player to start point if hit by bomb
			if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y - 1)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}

		if (pBombArr[i].y + 1 < 20)
		{
			if (Maze[pBombArr[i].y + 1][pBombArr[i].x] == '0')
				Maze[pBombArr[i].y + 1][pBombArr[i].x] = '1';

			// Move player to start point if hit by bomb
			if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y + 1)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}

		if (pBombArr[i].x - 1 >= 0)
		{
			if (Maze[pBombArr[i].y][pBombArr[i].x - 1] == '0')
				Maze[pBombArr[i].y][pBombArr[i].x - 1] = '1';

			// Move player to start point if hit by bomb
			if (pPlayer->x == pBombArr[i].x - 1 && pPlayer->y == pBombArr[i].y)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}

		if (pBombArr[i].x + 1 < 20)
		{
			if (Maze[pBombArr[i].y][pBombArr[i].x + 1] == '0')
				Maze[pBombArr[i].y][pBombArr[i].x + 1] = '1';

			// Move player to start point if hit by bomb
			if (pPlayer->x == pBombArr[i].x + 1 && pPlayer->y == pBombArr[i].y)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}
	}

	*pBombCount = 0;
}

int main()
{
	// 20 X 20 maze
	char strMaze[21][21];

	PLAYER tPlayer = {};
	POINT  tStartPos;
	POINT  tEndPos;
	
	tPlayer.iBombPower = 1;

	int iBombCount = 0; 

	POINT tBombPos[5];

	// maze setting
	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	while (true)
	{
		system("cls");
		// maze output
		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			cout << "Arrived" << endl;
			break;
		}

		cout << "t : set bomb, u : bomb attak, i : push wall" << endl;
		cout << "w : up, s : down, a : left, d : right, q : quit ";
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		else if (cInput == 't' || cInput == 'T')
			CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCount);

		else if (cInput == 'u' || cInput == 'U')
		{
			Fire(strMaze, &tPlayer, tBombPos, &iBombCount);
		}

		else
			MovePlayer(strMaze, &tPlayer, cInput);
	}

	return 0;
}
