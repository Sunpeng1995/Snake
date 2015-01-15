#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<graphics.h>

char HelloPage(void);
int play(int size, int hard, int speed, int mode, int isload, int mapnum);
void drawHelloPage(int x, int y, TCHAR s[]);
void readRank(void);
void drawFood(int x, int y);
void drawBoom(int x, int y);
void drawPoison(int x, int y);
void drawWisdom(int x, int y);
void drawSnakeHead(int x, int y);
void drawSnakeBody(int x, int y);
void rule(void);