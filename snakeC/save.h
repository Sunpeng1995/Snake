#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#define LEN 20

extern struct snake{
	int x;
	int y;
	struct snake *next;
};
extern struct node{
	int x;
	int y;
	int preIndex;
};
extern int qhead, qtail;
extern struct snake *head, *direct, *tail, *temp;
extern int fx, fy, px[3], py[3], bx, by, wx, wy;
extern int eFood, ePoison, eBoom, eWisdom;
extern char MAP[LEN][LEN];

void drawSnakeHead(int x, int y);
void drawSnakeBody(int x, int y);
void drawWordText(int x, int y, TCHAR s[]);
void drawNumber(int x, int y, int num);
void drawLandBKG(int x, int y);
void drawWordWindow(TCHAR s[]);
void drawWall(int x, int y);
void drawWordBKG(int x, int y);
void drawFood(int x, int y);
void drawBoom(int x, int y);
void drawWisdom(int x, int y);
void drawGrass(int x, int y);