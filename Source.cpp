#include <iostream>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <time.h>
#include <vector>

#define MAXSNAKESIZE 100

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

class Map {
	const int BORDER = 100;
	const int EMPTY_CELL = 0;
	int size;
	vector <vector<int>> map;

	Map() {
		size = 20;
	}

	void initMap() {
		for (int i = 0; i < size; i++) {
			vector <int> temp;
			for (int j = 0; j < size; j++) {
				if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
					temp.push_back(BORDER);
				else
					temp.push_back(EMPTY_CELL);
			}
			map.push_back(temp);
		}
	}

	void show() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (map[j][i] == BORDER)
					cout << "#";
				else if (map[j][i] == EMPTY_CELL)
					cout << " ";
			}
			
			cout << "#" << endl;
		}
	}
};

class Point {
private:
	int x;
	int y;
public:
	Point() {
		x = y = 10;
	}
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void SetPoint(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int GetX() {
		return x;
	}
	int GetY() {
		return y;
	}
	void MoveUp() {
		y--;
	}
	void MoveDown() {
		y++;
	}
	void MoveLeft() {
		x--;
	}
	void MoveRight() {
		x++;
	}
	void Draw() {
		gotoxy(x, y);
		cout << "*";
	}
	void Erase() {
		gotoxy(x, y);
		cout << " ";
	}
	void CopyPos(Point* p) {
		p->x = x;
		p->y = y;
	}
	void Debug() {
		cout << "(" << x << "," << y << ") ";
	}
};

class Snake {
private:
	Point* cell[MAXSNAKESIZE]; // массив точек для представления змеи
	int size; // текущий размер змеи
	char dir; //текущее направление змеи
	Point fruit;
public:
	Snake() {
		size = 1; // размер по умолчанию
		cell[0] = new Point(20, 20); // 20,20 - позиция по умолчанию
		for (int i = 1; i < MAXSNAKESIZE; i++) {
			cell[i] = NULL;
		}
		fruit.SetPoint(rand() % 50, rand() % 25);
	}
	void AddCell(int x, int y) {
		cell[size++] = new Point(x, y);
	}
	void TurnUp() {
		dir = 'w'; // w - клавиша управления для поворота вверх
	}
	void TurnDown() {
		dir = 's'; //w - клавиша управления для поворота вниз
	}
	void TurnLeft() {
		dir = 'a'; //w - клавиша управления для поворота налево
	}
	void TurnRight() {
		dir = 'd'; // w - клавиша управления для поворота направо	
	}
	void Move() {
		// Очисти экран
		system("cls");

		// заставить тело змеи следовать за головой
		for (int i = size - 1; i > 0; i--) {
			cell[i - 1]->CopyPos(cell[i]);
		}

		// поворот головы змеи
		switch (dir) {
		case 'w':
			cell[0]->MoveUp();
			break;
		case 's':
			cell[0]->MoveDown();
			break;
		case 'a':
			cell[0]->MoveLeft();
			break;
		case 'd':
			cell[0]->MoveRight();
			break;
		}

		//Столкновение с фруктами
		if (fruit.GetX() == cell[0]->GetX() && fruit.GetY() == cell[0]->GetY()) {
			AddCell(0, 0);
			fruit.SetPoint(rand() % 50, rand() % 25);
		}

		//рисунок змея
		for (int i = 0; i < size; i++)
			cell[i]->Draw();
		fruit.Draw();

		//Debug();

		Sleep(100);
	}
	void Debug() {
		for (int i = 0; i < size; i++) {
			cell[i]->Debug();
		}
	}
};

int main() {
	//рандом без генерации
	srand((unsigned)time(NULL));
	map.show();
	// Тестовая змея
	Snake snake;
	char op = 'l';
	do {
		if ( _kbhit() ) {
			op = _getch();
		}
		switch (op) {
		case 'w':
		case 'W':
			snake.TurnUp();
			break;

		case 's':
		case 'S':
			snake.TurnDown();
			break;

		case 'a':
		case 'A':
			snake.TurnLeft();
			break;

		case 'd':
		case 'D':
			snake.TurnRight();
			break;
		}
		snake.Move();
	} while (op != 'e');

	return 0;
}

