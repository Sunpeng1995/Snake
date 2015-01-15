#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<graphics.h>


#define LEFT  75
#define RIGHT 77
#define UP    72
#define DOWN  80
#define LEN 20


struct snake{
	int x;
	int y;
	struct snake *next;
};
struct node{
	int x;
	int y;
	int preIndex;
};
int qhead = 0, qtail = 0;
struct snake *head, *direct, *tail, *temp;
int fx, fy, px[3], py[3], bx, by, wx, wy;
int eFood, ePoison, eBoom, eWisdom;
extern char MAP[LEN][LEN];

void normalMap(int n, int mapnum);
int setFood(int, int);
int play(int size, int hard, int speed, int mode, int isload, int mapnum);
int control(int, int, int);
void move(int key);
void deltail(void);
int boom(int);
int flashpoison(int, int, int);
int eatSelf(int length, int*);
int wisdom(int size, int hard, int);
void dealRank(int score);
int poisonclock(int timing, int hard);
int load(int mode, int *length, int *hard, int *score, int *size, int *speed);
void save(int mode, int length, int hard, int score, int size, int speed);
void setgrass(void);

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
void drawPoison(int x, int y);
void drawWisdom(int x, int y);
void drawGrass(int x, int y);