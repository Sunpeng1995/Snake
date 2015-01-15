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

void normalMap(int n);
int setFood(int,int);
int play(int,int,int, int,int);
int control(int,int,int);
void move(int key);
void deltail(void);
int boom(int);
int flashpoison(int, int, int);
int eatSelf(int length, int*);
int wisdom(int size, int hard, int, int);
void dealRank(int score);
int poisonclock(int timing, int hard);
int load(int mode, int *length, int *hard, int *score, int *size, int *speed);
void save(int mode, int length, int hard, int score, int size, int speed);


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


int play(int size, int hard, int speed, int mode, int isload){
	eFood = 0, ePoison = 0, eBoom = 0, eWisdom = 0;
	bx = 0, by = 0, wx = 0, wy = 0;
	for (int i = 0; i < hard; i++){
		px[i] = 0;
		py[i] = 0;
	}//初始化各个食物的值
	int timing = 0;
	int score = 0, ranksave, loadcorrect;
	int keylast = 0;
	int length = 1, life = 1;
	int showPoison = 0;
	setbkcolor(BLACK);
	cleardevice();
	srand((unsigned)time(NULL));
	if (isload == 0){
		normalMap(size);
		head = (struct snake*)malloc(sizeof(struct snake));
		head->x = rand() % (size - 2) + 1;
		head->y = rand() % (size - 2) + 1;
		head->next = NULL;
		tail = head;
		drawSnakeHead(head->x, head->y);
		setFood(size, hard);
	}
	else{
		loadcorrect = load(mode, &length, &hard, &score, &size, &speed);
		if (loadcorrect == 0){
			return 0;
		}
	}
	//TODO 2015-1-6 01:09:42

	keylast = _getch();
	while (1){
		Sleep(speed);
		drawWordText(size + 1, 1, _T("当前分数（分）："));
		drawWordBKG(size + 1, 3);
		drawNumber(size + 1, 3, score + length * 10);
		drawWordText(size + 1, 5, _T("当前身长（节）："));
		drawWordBKG(size + 1, 7);
		drawNumber(size + 1, 7, length);
		drawWordText(size + 1, 9, _T("当前速度（ms/步）："));
		drawWordBKG(size + 1, 11);
		drawNumber(size + 1, 11, speed);
		drawWordText(size + 1, 13, _T("按空格暂停游戏"));
		drawWordBKG(size + 1, 15);
		drawFood(size + 1, 15);
		drawWordText(size + 2, 15, _T("-食物"));
		drawWordBKG(size + 1, 16);
		drawPoison(size + 1, 16);
		drawWordText(size + 2, 16, _T("-毒草"));
		drawWordBKG(size + 1, 17);
		drawBoom(size + 1, 17);
		drawWordText(size + 2, 17, _T("-地雷"));
		drawWordBKG(size + 1, 18);
		drawWisdom(size + 1, 18);
		drawWordText(size + 2, 18, _T("-智慧草"));

		keylast = control(keylast, length, size);
		if (keylast == -1){
			save(mode, length, hard, score, size, speed);
			return 0;
		}
		move(keylast);
		head = direct;
		if (MAP[head->y][head->x] == '#')//撞墙
			life = 0;
		if (length > 4){
			length = eatSelf(length, &score);//吃自己
		}
		drawSnakeHead(head->x, head->y);
		showPoison = flashpoison(ePoison, showPoison, hard);
		if (direct->x != fx || direct->y != fy)//吃食物
			deltail();
		else{
			eFood = 0;
			length++;
			setFood(size, hard);
			score += 10;
		}
		if (head->next != NULL)
			drawSnakeBody(head->next->x, head->next->y);
		if (direct->x == bx && direct->y == by && eBoom == 1){//吃炸弹
			length = boom(length);
			score /= 2; 
		}
		for (int i = 0; i < hard; i++){//吃毒草
			if (direct->x == px[i] && direct->y == py[i] && ePoison == 1){
				if (length == 1)
					life = 0;
				else{
					deltail();
					length--;
					for (int j = 0; j < hard; j++){
						if (j != i)
							drawLandBKG(px[j], py[j]);
						px[j] = 0;
						py[j] = 0;
					}
					ePoison = 0;
					showPoison = 1;
					score -= 10;
					timing = 0;
				}
				
			}
		}
		if (direct->x == wx && direct->y == wy && eWisdom==1){//吃智慧草
			keylast = wisdom(size, hard, speed, keylast);
			eWisdom = 0;
			score += 50;
		}

		if (ePoison)
			timing = poisonclock(timing, hard);
		if (eFood)
			drawFood(fx, fy);
		if (eBoom)
			drawBoom(bx, by);
		if (eWisdom)
			drawWisdom(wx, wy);

		
		if (mode == 2 && length == 3){
			if (hard == 3){
				drawWordWindow(_T("恭喜你，通关了！"));
				_getch();
				break;
			}
			else{
				drawWordWindow(_T("进入下一关！"));
				_getch();
				play(size, hard + 1, speed - 100, 2, 0);
				break;
			}
		}
		if (mode == 3)
			speed = 400 - (length - 1) * 5;
		if (length == 0)
			life = 0;

		if (life == 0)
			break;
	}

	if (life == 0){
		drawWordWindow(_T("游戏失败"));
		if (mode == 3){
			dealRank(score + length * 10);
		}
		system("pause");
	}
	return 0;
}


int control(int keylast, int length, int size){
	int key, keytemp, save;
	key = keylast;
	if (_kbhit()){
		keytemp = _getch();
		if (keytemp == 0xE0 || keytemp == 0)  //读取功能键
			keytemp = _getch();
		else if (keytemp == 32){
			drawWordBKG(size + 1, 15);
			drawWordText(size + 1, 15, _T("游戏已暂停..."));
			drawWordBKG(size + 1, 16);
			drawWordText(size + 1, 16, _T("空格键-继续游戏"));
			drawWordBKG(size + 1, 17);
			drawWordText(size + 1, 17, _T("ESC键-保存并退出"));
			drawWordBKG(size + 1, 18);
			while (1){
				save = _getch();
				if (save == 32){
					drawWordBKG(size + 1, 15);
					drawFood(size + 1, 15);
					drawWordText(size + 2, 15, _T("-食物"));
					drawWordBKG(size + 1, 16);
					drawPoison(size + 1, 16);
					drawWordText(size + 2, 16, _T("-毒草"));
					drawWordBKG(size + 1, 17);
					drawBoom(size + 1, 17);
					drawWordText(size + 2, 17, _T("-地雷"));
					drawWordBKG(size + 1, 18);
					drawWisdom(size + 1, 18);
					drawWordText(size + 2, 18, _T("-智慧草"));
					drawWordText(size + 1, 13, _T("按空格暂停游戏"));
					keytemp = keylast;
					break;
				}
				else if (save == 27){
					system("cls");
					return -1;
				}
				else
					continue;
			}
		}
		if (length > 1){//只有一节时，转向不受限
			if (keytemp == LEFT && keylast != RIGHT)
				key = keytemp;
			if (keytemp == RIGHT && keylast != LEFT)
				key = keytemp;
			if (keytemp == UP && keylast != DOWN)
				key = keytemp;
			if (keytemp == DOWN && keylast != UP)
				key = keytemp;
		}
		else {
			if (keytemp == LEFT || keytemp == RIGHT || keytemp == UP || keytemp == DOWN)
				key = keytemp;
		}
	}
	return key;
}


void move(int key){
	direct = (struct snake*)malloc(sizeof(struct snake));
	direct->x = head->x;
	direct->y = head->y;
	switch (key){
	case UP:
		direct->y--;
		break;
	case DOWN:
		direct->y++;
		break;
	case LEFT:
		direct->x--;
		break;
	case RIGHT:
		direct->x++;
		break;
	default:
		break;
	}
	direct->next = head;
}


void deltail(void){
	temp = head;
	while (temp->next->next != NULL){
		temp = temp->next;
	}
	temp->next = NULL;
	drawLandBKG(tail->x, tail->y);
	free(tail);
	tail = temp;
}


int eatSelf(int length, int *score){
	struct snake *p, *temp;
	int count;
	p = head->next;
	temp = head->next;
	while (p->next != NULL){
		p = p->next;
		if (p->x == direct->x&&p->y == direct->y){
			while (temp->next != p)
				temp = temp->next;
			tail = temp;
			tail->next = NULL;
			break;
		}
	}
	if (p->next == NULL)
		return length;
	else{
		count = 1;
		temp = p;
		p = p->next;
		free(temp);
		while (p != NULL){
			count++;
			MAP[p->y][p->x] = '#';
			drawWall(p->x, p->y);
			temp = p;
			p = p->next;
			free(temp);
		}
		*score /= 2;
		return length - count;
	}
}

