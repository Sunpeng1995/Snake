#include"game.h"

/*
函数名称：游戏主函数
函数功能：进行游戏的主体函数，对游戏中的事件进行处理
输入参数：地图大小size，游戏难度hard，游戏速度speed，游戏模式mode，是否载入存档isload，地图编号mapnum
*/
int play(int size, int hard, int speed, int mode, int isload, int mapnum){
	eFood = 0, ePoison = 0, eBoom = 0, eWisdom = 0;
	bx = 0, by = 0, wx = 0, wy = 0;
	for (int i = 0; i < hard; i++){
		px[i] = 0;
		py[i] = 0;
	}                                            /*初始化所有食物坐标为0*/
	int timing = 0;
	int score = 0, ranksave, loadcorrect;
	int keylast = 0;
	int length = 1, life = 1;
	int showPoison = 0;
	setbkcolor(BLACK);
	cleardevice();
	srand((unsigned)time(NULL));
	if (isload == 0){                            /*检测是否要读取存档*/
		normalMap(size, mapnum);                 /*初始化地图*/
		head = (struct snake*)malloc(sizeof(struct snake));
		head->x = rand() % (size - 2) + 1;
		head->y = rand() % (size - 2) + 1;
		head->next = NULL;
		tail = head;
		drawSnakeHead(head->x, head->y);
		setFood(size, hard);
	}
	else{                                        /*载入存档*/
		loadcorrect = load(mode, &length, &hard, &score, &size, &speed);
		if (loadcorrect == 0){
			return 0;
		}
	}

	keylast = _getch();
	while (1){
		Sleep(speed);                            /*游戏速度*/
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
		drawWordBKG(size + 1, 14);
		drawGrass(size + 1, 14);
		drawWordText(size + 2, 14, _T("-杂草"));
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
		/*游戏侧边栏，图例*/

		keylast = control(keylast, length, size);
		if (keylast == -1){
			save(mode, length, hard, score, size, speed);
			return 0;
		}
		move(keylast);
		head = direct;
		if (MAP[head->y][head->x] == '#')        /*撞墙*/
			life = 0;
		if (length > 4){
			length = eatSelf(length, &score);    /*咬断自己*/
		}
		drawSnakeHead(head->x, head->y);
		showPoison = flashpoison(ePoison, showPoison, hard);
		if (direct->x != fx || direct->y != fy)  /*吃食物*/
			deltail();
		else{
			eFood = 0;
			eBoom = 0;
			drawLandBKG(bx, by);
			length++;
			setFood(size, hard);
			score += 10;
			if (mode == 3)
				setgrass();
		}
		if (head->next != NULL)
			drawSnakeBody(head->next->x, head->next->y);
		if (direct->x == bx && direct->y == by && eBoom == 1){/*吃地雷*/
			length = boom(length);
			score /= 2; 
		}
		for (int i = 0; i < hard; i++){          /*吃毒草*/
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
		if (direct->x == wx && direct->y == wy && eWisdom == 1){/*吃智慧草*/
			keylast = wisdom(size, hard, speed);
			eWisdom = 0;
			score += 50;
		}

		if (ePoison)                             /*重打印一遍食物*/
			timing = poisonclock(timing, hard);
		if (eFood)
			drawFood(fx, fy);
		if (eBoom)
			drawBoom(bx, by);
		if (eWisdom)
			drawWisdom(wx, wy);
		if (mode == 3){
			for (int i = 0; i < size; i++){
				for (int j = 0; j < size; j++){
					if (MAP[i][j] == '@')
						drawGrass(j, i);
				}
			}
		}
		
		if (mode == 2 && length == 5){           /*闯关模式分支*/
			if (hard == 3){
				drawWordWindow(_T("恭喜你，通关了！"));
				_getch();
				break;
			}
			else{
				drawWordWindow(_T("进入下一关！"));
				_getch();
				play(size, hard + 1, speed - 100, 2, 0, mapnum + 1);
				break;
			}
		}
		if (mode == 3)                           /*无尽模式分支*/
			speed = 400 - (length - 1) * 5;

		if (length == 0)                         /*死亡判定*/
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

/*
函数名称：键盘控制
函数功能：获取键盘响应，对应不同的事件
输入参数：上次的方向keylast，蛇长度length，地图大小size
返回值：方向值，-1时进行存档
*/
int control(int keylast, int length, int size){
	int key, keytemp, save;
	key = keylast;
	if (_kbhit()){
		keytemp = _getch();
		if (keytemp == 0xE0 || keytemp == 0)     /*读取功能键*/
			keytemp = _getch();
		else if (keytemp == 32){                 /*暂停时*/
			drawWordBKG(size + 1, 14);
			drawWordBKG(size + 1, 15);
			drawWordText(size + 1, 15, _T("游戏已暂停..."));
			drawWordBKG(size + 1, 16);
			drawWordText(size + 1, 16, _T("空格键-继续游戏"));
			drawWordBKG(size + 1, 17);
			drawWordText(size + 1, 17, _T("ESC键-保存并退出"));
			drawWordBKG(size + 1, 18);
			while (1){
				save = _getch();
				if (save == 32){                 /*复原时*/
					drawWordBKG(size + 1, 14);
					drawGrass(size + 1, 14);
					drawWordText(size + 2, 14, _T("-杂草"));
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
					return -1;                   /*存档*/
				}
				else
					continue;
			}
		}
		if (length > 1){                         /*只有一节时，转向不受限*/
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

/*
函数名称：移动
函数功能：添一个新的头，与deltail函数共用实现移动
输入参数：方向key
*/
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

/*
函数名称：删除尾巴
函数功能：删除蛇链表的尾节点，并在屏幕上擦除
*/
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

/*
函数名称：咬断自己
函数功能：当蛇碰到自己的身体时，其之后的身体节点截断，变成障碍物，并扣分
输入参数：蛇身长度length，当前分数指针变量*score
返回值：新的蛇身长度
*/
int eatSelf(int length, int *score){
	struct snake *p, *temp;
	int count;
	p = head->next;
	temp = head->next;
	while (p->next != NULL){
		p = p->next;
		if (p->x == direct->x&&p->y == direct->y){/*检测是否头节点是否碰到自己身体*/
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
		while (p != NULL){                       /*在屏幕上擦除，并变成障碍物*/
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

