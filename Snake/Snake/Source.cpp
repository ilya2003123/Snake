#include <iostream>
#include <conio.h>

using namespace std;

bool gameOver;
const int a = 40;
const int b = 20;
int x, y, FruitX, FruitY, score;
int tailX[100], tailY[100];
int nTail;
enum Zmeya { STOP = 0, LEFT, RIGHT, UP, DOWN }; // ѕеречисление наших действий "STOP = 0" отвечает за то, что змейка будет сто€ть в начале
Zmeya dir;


void Setup() {
	gameOver = false;
	dir = STOP;
	x = a / 2;
	y = b / 2;
	FruitX = rand() % a - 1;
	FruitY = rand() % b - 1; // ¬ообще змейка должна по€вл€тьс€ на середине, но такого не получаетс€, отклонение на (1,1)
	score = 0;

}



void Draw() {
	system("cls");
	for (int i = 0; i < a + 1; i++) // потому что отн€ли тогда 1
		cout << "#";
	cout << endl;

	for (int i = 0; i < b; i++)
	{
		for (int j = 0; j < a; j++)
		{
			if (j == 0 || j == a - 1)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == FruitY && j == FruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						cout << "o";
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < a + 1; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}



void Input() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}



void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir) {
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

	}
	if (x > a || x<0 || y>b || y < 0)
		gameOver = true;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	if (x == FruitX && y == FruitY)
	{
		score += 10;
		FruitX = rand() % a;
		FruitY = rand() % b;
		nTail++;
	}
}


int main()
{
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
	}

	return 0;
}