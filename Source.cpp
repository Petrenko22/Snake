#include <iostream>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <time.h>

#define MAXSNAKESIZE 100
#define MAXFRAMEX 119
#define MAXFRAMEY 29

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) // установить bool visible = 0 - невидимый, bool visible = 1 - видимый
{
	if (size == 0)
	{
		size = 20;	// размер курсора по умолчанию Изменение на числа от 1 до 20 уменьшает ширину курсора
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}

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
		if (y < 0)
			y = MAXFRAMEY;
	}
	void MoveDown() {
		y++;
		if (y > MAXFRAMEY)
			y = 0;
	}
	void MoveLeft() {
		x--;
		if (x < 0)
			x = MAXFRAMEX;
	}
	void MoveRight() {
		x++;
		if (x > MAXFRAMEX)
			x = 0;
	}
	void Draw(char ch = '*') {
		gotoxy(x, y);
		cout << ch;
	}
	void Erase() {
		gotoxy(x, y);
		cout << " ";
	}
	void CopyPos(Point* p) {
		p->x = x;
		p->y = y;
	}
	int IsEqual(Point* p) {
		if (p->x == x && p->y == y)
			return 1;
		return 0;
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
	int state; // bool, представляющий состояние змеи, т.е. живой, мертвый
	int started;
	int blink; // фрукты мигают 
public:
	Snake() {
		size = 1; //размер по умолчанию
		cell[0] = new Point(20, 20); // 20,20 - позиция по умолчанию
		for (int i = 1; i < MAXSNAKESIZE; i++) {
			cell[i] = NULL;
		}
		fruit.SetPoint(rand() % MAXFRAMEX, rand() % MAXFRAMEY);
		state = 0;
		started = 0;
	}
	void AddCell(int x, int y) {
		cell[size++] = new Point(x, y);
	}
	void TurnUp() {
		if (dir != 's')
			dir = 'w'; // w - клавиша управления для поворота вверх
	}
	void TurnDown() {
		if (dir != 'w')
			dir = 's'; //s - клавиша управления для поворота вниз
	}
	void TurnLeft() {
		if (dir != 'd')
			dir = 'a'; //a - клавиша управления для поворота налево
	}
	void TurnRight() {
		if (dir != 'a')
			dir = 'd'; //d - клавиша управления для поворота направо
	}
	void WelcomeScreen() {
		SetConsoleTextAttribute(console, 15);
		cout << "\n  SNAKE "   ;

	}
	void Move() {
		// Очисти экран
		system("cls");

		if (state == 0) {
			if (!started) {
				WelcomeScreen();
				cout << "\nStart Game";
				_getch();
				started = 1;
				state = 1;
			}
			else {
				cout << "\nGame Over";
				cout << "\nClick to continue";
				_getch();
				state = 1;
				size = 1;
			}
		}

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

		if (SelfCollision())
			state = 0;




		// Столкновение с фруктами
		if (fruit.GetX() == cell[0]->GetX() && fruit.GetY() == cell[0]->GetY()) {
			AddCell(0, 0);
			fruit.SetPoint(rand() % MAXFRAMEX, rand() % MAXFRAMEY);
		}

		// рисунок змея
		for (int i = 0; i < size; i++)
			cell[i]->Draw();

		SetConsoleTextAttribute(console, 15);
		if (!blink)
			fruit.Draw('+');
		blink = !blink;
		SetConsoleTextAttribute(console, 14);

		//Debug();

		Sleep(100);
	}
	int SelfCollision() {
		for (int i = 1; i < size; i++)
			if (cell[0]->IsEqual(cell[i]))
				return 1;
		return 0;
	}
	void Debug() {
		for (int i = 0; i < size; i++) {
			cell[i]->Debug();
		}
	}
};
symbol = getch();
// считываем нажатую клавишу с помощью функции getch()
	 switch (symbol) {
	 case 72: if (change_x != 1 || change_y != 0) { change_x = -1; change_y = 0; } break;
	 case 75: if (change_x != 0 || change_y != 1) { change_x = 0; change_y = -1; } break;
	 case 80: if (change_x != -1 || change_y != 0) { change_x = 1; change_y = 0; } break;
	 case 77: if (change_x != 0 || change_y != -1) { change_x = 0; change_y = 1; } break;
		 // управление змейкой у нас через wasd
	 case 32: change_color(2); break;
		 // если нажат пробел, то меняем цвет консоли

int main() {
	// рандом без генерации
	setcursor(0, 0);
	srand((unsigned)time(NULL));

	// Тестовая змея
	Snake snake;
	char op = 'l';
	do {
		if (_kbhit()) {
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
