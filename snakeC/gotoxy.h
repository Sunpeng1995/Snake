#include<Windows.h>
void gotoxy(int x, int y)//λ�ú������ٶ�����
{
	COORD pos;

	pos.X = x;

	pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}