#include<stdio.h>
#include<time.h>
#include<Windows.h>
#define LEN 20
#define LEFT  75
#define RIGHT 77
#define UP    72
#define DOWN  80

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


void deltail(void);
void enqueue(struct node n, struct node queue[512]);
struct node dequeue(struct node queue[512]);
struct node pack(int x, int y, int pre);
int findPath(int maze[LEN][LEN], struct node start, struct node end, struct node queue[512], struct node path[64]);
void reflect(int map[LEN][LEN], int, int);

void drawFood(int x, int y);
void drawBoom(int x, int y);
void drawPoison(int x, int y);
void drawWisdom(int x, int y);
void drawLandBKG(int x, int y);
void drawSnakeHead(int x, int y);
void drawSnakeBody(int x, int y);