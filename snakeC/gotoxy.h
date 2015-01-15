#include<Windows.h>
void gotoxy(int x, int y)//位置函数，百度来的
{
	COORD pos;

	pos.X = x;

	pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}