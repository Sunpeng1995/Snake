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

int setFood(int);
void play(int, int, int, int, int);
int control(void);
void move(int key);
void deltail(void);
int boom(int);
int flashpoison(int, int);
int eatSelf(int length);
int wisdom(int size, int hard, int speed, int keylast);
void enqueue(struct node n, struct node queue[512]);
struct node dequeue(struct node queue[512]);
struct node pack(int x, int y, int pre);
int findPath(int maze[LEN][LEN], struct node start, struct node end, struct node queue[512], struct node path[64]);
void reflect(int map[LEN][LEN],int ,int);
void gotoxy(int, int);


void drawFood(int x, int y);
void drawBoom(int x, int y);
void drawPoison(int x, int y);
void drawWisdom(int x, int y);
void drawLandBKG(int x, int y);
void drawSnakeHead(int x, int y);
void drawSnakeBody(int x, int y);

int setFood(int size, int hard){
	int wisdom, poison;
	int tmap[LEN][LEN];
	srand((unsigned)time(NULL));
	wisdom = rand() % 5;
	poison = rand() % 3;
	reflect(tmap, size, hard);
	tmap[head->y][head->x] = 1;
	if (eWisdom)
		tmap[wy][wx] = 1;
	if (!eFood){
		do{
			fx = rand() % (size - 2) + 1;
			fy = rand() % (size - 2) + 1;
		} while (tmap[fy][fx] != 0);
		drawFood(fx, fy);
		eFood = 1;
	}
	if (!eBoom){
		do{
			bx = rand() % (size - 2) + 1;
			by = rand() % (size - 2) + 1;
		} while (tmap[by][bx] != 0);
		drawBoom(bx, by);
		eBoom = 1;
	}
	if ((!eWisdom) && wisdom == 1){
		do{
			wx = rand() % (size - 2) + 1;
			wy = rand() % (size - 2) + 1;
		} while (tmap[wy][wx] != 0);
		drawWisdom(wx, wy);
		eWisdom = 1;
	}
	if ((!ePoison) && poison == 1){
		for (int i = 0; i < hard; i++){
			do{
				px[i] = rand() % (size - 2) + 1;
				py[i] = rand() % (size - 2) + 1;
			} while (tmap[py[i]][px[i]] != 0);
			drawFood(px[i], py[i]);
		}
		ePoison = 1;
	}
	return 0;
}

int boom(int length){
	if (length == 1){
		eBoom = 0;
		return 0;
	}
	int newlength, temp;
	struct snake *p, *del;
	p = head;
	temp = length / 2;
	newlength = length - temp;
	for (int i = 0; i < newlength - 1; i++){
		p = p->next;
	}
	del = p->next;
	p->next = NULL;
	tail = p;
	while (del != NULL){
		p = del;
		del = del->next;
		drawLandBKG(p->x, p->y);
		free(p);
	}
	eBoom = 0;
	return newlength;
}

int flashpoison(int exist, int show, int hard){
	if (exist){
		if (show){
			for (int i = 0; i < hard; i++){
				drawPoison(px[i], py[i]);
			}
			return 0;
		}
		else{
			for (int i = 0; i < hard; i++){
				drawFood(px[i], py[i]);
			}
			return 1;
		}
	}
	else
		return 0;
}

int wisdom(int size, int hard, int speed, int keylast){
	int tmap[LEN][LEN], exist, key;
	struct node queue[512], path[64], food, end;
	struct snake *p;
	reflect(tmap, size, hard);
	food = pack(fx, fy, -3);
	end = pack(head->x, head->y, -3);
	exist = findPath(tmap, food, end, queue, path);
	if (exist){
		for (int i = 0; path[i].preIndex != -1; i++){
			Sleep(speed / 2);
			p = (struct snake*)malloc(sizeof(struct snake));
			p->x = path[i].x;
			p->y = path[i].y;
			p->next = head;
			drawSnakeBody(head->x, head->y);
			head = p;
			drawSnakeHead(head->x, head->y);
			deltail();
		}
		if (head->x + 1 == fx)
			key = RIGHT;
		else if (head->x - 1 == fx)
			key = LEFT;
		else if (head->y + 1 == fy)
			key = DOWN;
		else
			key = UP;
	}
	qhead = 0;
	qtail = 0;
	return key;
}

void enqueue(struct node n, struct node queue[512]){
	queue[qtail] = n;
	qtail++;
}

struct node dequeue(struct node queue[512]){
	qhead++;
	return queue[qhead - 1];
}

struct node pack(int x, int y, int pre){
	struct node t;
	t.x = x;
	t.y = y;
	t.preIndex = pre;
	return t;
}

int findPath(int maze[LEN][LEN], struct node start, struct node end, struct node queue[512], struct node path[64]){
	struct node qtemp;
	queue[0].x = start.x;
	queue[0].y = start.y;
	queue[0].preIndex = -1;
	maze[start.y][start.x] = 2;
	qtail = 1;
	while (qtail != qhead){
		qtemp = dequeue(queue);
		if (qtemp.x == end.x && qtemp.y == end.y)
			break;
		if (maze[qtemp.y + 1][qtemp.x] == 0){
			maze[qtemp.y + 1][qtemp.x] = 2;
			enqueue(pack(qtemp.x, qtemp.y + 1, qhead - 1), queue);
		}
		if (maze[qtemp.y][qtemp.x + 1] == 0){
			maze[qtemp.y][qtemp.x + 1] = 2;
			enqueue(pack(qtemp.x + 1, qtemp.y, qhead - 1), queue);
		}
		if (maze[qtemp.y - 1][qtemp.x] == 0){
			maze[qtemp.y - 1][qtemp.x] = 2;
			enqueue(pack(qtemp.x, qtemp.y - 1, qhead - 1), queue);
		}
		if (maze[qtemp.y][qtemp.x - 1] == 0){
			maze[qtemp.y][qtemp.x - 1] = 2;
			enqueue(pack(qtemp.x - 1, qtemp.y, qhead - 1), queue);
		}
	}
	if (qtemp.x == end.x && qtemp.y == end.y){
		int i = qtemp.preIndex;
		for (int j = 0; i != -1; j++){
			path[j] = queue[i];
			i = queue[i].preIndex;
		}
		return 1;
	}
	else
		return 0;
}

void reflect(int tmap[LEN][LEN], int size, int hard){
	struct snake *p;
	p = head->next;
	for (int i = 0; i < size; i++){            //Í¨Â·¸³0£¬ÕÏ°­Îï¸³1
		for (int j = 0; j < size; j++){
			if (MAP[i][j] == ' ')
				tmap[i][j] = 0;
			if (MAP[i][j] == '#')
				tmap[i][j] = 1;
		}
	}
	if (eBoom)
		tmap[by][bx] = 1;
	if (ePoison){
		for (int i = 0; i < hard; i++)
			tmap[py[i]][px[i]] = 1;
	}
	while (p != NULL){
		tmap[p->y][p->x] = 1;
		p = p->next;
	}
}

int poisonclock(int timing, int hard){
	time_t end;
	static time_t start;
	if (timing == 0){
		start = time(NULL);
		timing = 1;
	}
	else{
		end = time(NULL);
		if (difftime(end, start) > 10.0){
			for (int i = 0; i < hard; i++){
				drawLandBKG(px[i], py[i]);
				px[i] = 0;
				py[i] = 0;
			}
			timing = 0;
			ePoison = 0;
		}
	}
	return timing;
}