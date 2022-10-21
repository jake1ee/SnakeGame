#include <iostream>
#include<conio.h>
#include<Windows.h>


using namespace std;
bool gameOver;
const int width = 40;
const int height = 20;
int x,
	y,
	fruitX,
	fruitY,
	Score;
int nTail = 0,
	TailX[100],
	TailY[100];



enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };	
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	Score = 0;
}

void Draw()
{
	system("cls");

	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			
				cout << "#";
			
			if (i == y && j == x)

				cout << "O";

			else if (i == fruitY && j == fruitX)
			
				cout << "F";
			
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (TailX[k] == j && TailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}

				if(!print)
					cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score :" << Score << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = TailX[0],
		prevY = TailY[0],
		prev2X, prev2Y;
	
	TailX[0] = x;
	TailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = TailX[i];
		prev2Y = TailY[i];
		TailX[i] = prevX;
		TailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x > width || x<0 || y>height || y < 0)
	{
		gameOver = true;
	}

	for (int i = 0; i < nTail; i++)
	{
		if (TailX[i] == x && TailY[i] == y)
		{
			gameOver = true;
		}
	}
	
	if (x == fruitX && y == fruitY)
	{
		nTail++;
		Score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}

}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(50);
	}

	return 0;
}