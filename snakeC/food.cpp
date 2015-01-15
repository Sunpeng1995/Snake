#include"food.h"
/*
函数名称：设置食物
函数功能：随机生成食物，并确保不覆盖地图上已有的东西
输入参数：地图大小size，难度hard
*/
int setFood(int size, int hard){
	int wisdom, poison;
	int tmap[LEN][LEN];
	srand((unsigned)time(NULL));               /*设置随机数种子*/
	wisdom = rand() % 5;
	poison = rand() % 3;                       /*这两种食物随机出现，当余数为1时出现*/
	reflect(tmap, size, hard);                 /*把当前地图上已被占用的位置记录下来*/
	tmap[head->y][head->x] = 1;
	if (eWisdom)
		tmap[wy][wx] = 1;                      /*reflect函数中缺智慧草和蛇头的坐标，这里补上*/
	if (!eFood){
		do{
			fx = rand() % (size - 2) + 1;
			fy = rand() % (size - 2) + 1;
		} while (tmap[fy][fx] != 0);           /*do while循环来确保不会生成在地图已被占用的地方*/
		drawFood(fx, fy);                      /*打印食物*/
		eFood = 1;
	}
	if (!eBoom){
		do{
			bx = rand() % (size - 2) + 1;
			by = rand() % (size - 2) + 1;
		} while (tmap[by][bx] != 0);
		drawBoom(bx, by);                      /*地雷同上*/
		eBoom = 1;
	}
	if ((!eWisdom) && wisdom == 1){
		do{
			wx = rand() % (size - 2) + 1;
			wy = rand() % (size - 2) + 1;
		} while (tmap[wy][wx] != 0);
		drawWisdom(wx, wy);                    /*智慧草同上*/
		eWisdom = 1;
	}
	if ((!ePoison) && poison == 1){
		for (int i = 0; i < hard; i++){
			do{
				px[i] = rand() % (size - 2) + 1;
				py[i] = rand() % (size - 2) + 1;
			} while (tmap[py[i]][px[i]] != 0);
			drawFood(px[i], py[i]);            /*毒草最多可以生成3个，用hard参数来控制*/
		}
		ePoison = 1;
	}
	return 0;
}

/*
函数名称：杂草实现
函数功能：在地图中随机生成一个杂草
*/
void setgrass(void){
	int grass, x, y;
	int tmap[LEN][LEN];
	reflect(tmap, LEN, 3);
	srand((unsigned)time(NULL));
	grass = rand() % 3;
	if (grass != 1){
		do{
			x = rand() % (LEN - 2) + 1;
			y = rand() % (LEN - 2) + 1;
		} while (tmap[y][x] != 0);
		MAP[y][x] = '@';
	}
}

/*
函数名称：地雷实现
函数功能：将蛇的长度减半，并擦除后半部蛇身
输入参数：蛇长length
返回值：新的蛇长newlength
*/
int boom(int length){                          /*传入length参数，计算炸掉的节数*/
	if (length == 1){
		eBoom = 0;
		return 0;
	}
	int newlength, temp;
	struct snake *p, *del;
	p = head;
	temp = length / 2;
	newlength = length - temp;
	for (int i = 0; i < newlength - 1; i++){   /*遍历到新的长度处，截断链表*/
		p = p->next;
	}
	del = p->next;
	p->next = NULL;
	tail = p;
	while (del != NULL){                       /*遍历截断点之后的链表，在屏幕上擦除*/
		p = del;
		del = del->next;
		drawLandBKG(p->x, p->y);
		free(p);
	}
	eBoom = 0;
	return newlength;
}

/*
函数名称：毒草闪烁
函数功能：使毒草在屏幕上闪烁
输入参数：毒草是否存在exist，毒草目前的闪烁状态show，毒草个数num
返回值：毒草目前的闪烁状态show
*/
int flashpoison(int exist, int show, int num){
	if (exist){
		if (show){
			for (int i = 0; i < num; i++){
				drawPoison(px[i], py[i]);
			}
			return 0;
		}
		else{
			for (int i = 0; i < num; i++){
				drawFood(px[i], py[i]);
			}
			return 1;
		}
	}
	else
		return 0;
}

/*
函数名称：智慧草实现
函数功能：实现蛇的自动寻路，避开障碍物、毒草、炸弹，吃到食物
输入参数：地图大小size，毒草个数num，游戏速度speed
返回值：方向key
*/
int wisdom(int size, int num, int speed){
	int tmap[LEN][LEN], exist, key;
	struct node queue[512], path[64], food, end;
	struct snake *p;
	reflect(tmap, size, num);
	food = pack(fx, fy, -3);
	end = pack(head->x, head->y, -3);            /*设定起点为食物，终点为吃到智慧草时的蛇头*/
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
		}                                        /*根据找到的路径，在屏幕上打印蛇的移动*/
		if (head->x + 1 == fx)
			key = RIGHT;
		else if (head->x - 1 == fx)
			key = LEFT;
		else if (head->y + 1 == fy)
			key = DOWN;
		else
			key = UP;
	}                                            /*到达食物邻格时，判断食物在哪个方向，并返回之*/
	qhead = 0;
	qtail = 0;
	return key;
}

/*
函数名称：进入队列
函数功能：将结构体压入队列
输入参数：点的结构体n，结构体数组queue
*/
void enqueue(struct node n, struct node queue[512]){
	queue[qtail] = n;
	qtail++;
}

/*
函数名称：离开队列
函数功能：将队列第一个结构体弹出队列，进行操作
输入参数：结构体队列queue
返回值：点的结构体
*/
struct node dequeue(struct node queue[512]){
	qhead++;
	return queue[qhead - 1];
}

/*
函数名称：包装坐标
函数功能：将地图上一个点打包成一个点的结构体，并标上其上家的队列中的位置
输入参数：点的横坐标x，点的纵坐标y，上家在队列中的位置pre
返回值：该点的结构体t
*/
struct node pack(int x, int y, int pre){
	struct node t;
	t.x = x;
	t.y = y;
	t.preIndex = pre;
	return t;
}

/*
函数名称：找寻路径
函数功能：通过宽度优先搜索，找出一条最短的路径
输入参数：标记完障碍物的地图二维数组maze，起点结构体start，终点结构体end，队列数组queue，路径数组path
返回值：是否存在路径
*/
int findPath(int maze[LEN][LEN], struct node start, struct node end, struct node queue[512], struct node path[64]){
	struct node qtemp;
	queue[0].x = start.x;
	queue[0].y = start.y;
	queue[0].preIndex = -1;
	maze[start.y][start.x] = 2;
	qtail = 1;
	while (qtail != qhead){                       /*队列不为空时*/
		qtemp = dequeue(queue);
		if (qtemp.x == end.x && qtemp.y == end.y) /*检测是否到达终点*/
			break;
		if (maze[qtemp.y + 1][qtemp.x] == 0){     /*检索该节点的上下左右节点是否可到达*/
			maze[qtemp.y + 1][qtemp.x] = 2;       /*已探索过的节点标记为2*/
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
	if (qtemp.x == end.x && qtemp.y == end.y){    /*将路径存入数组path中*/
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

/*
函数名称：地图映射
函数功能：将游戏地图中的障碍物、毒草、地雷，以1和0的形式映射到新的二维数组中
输入参数：新的二维数组tmap，地图大小size，毒草个数num
*/
void reflect(int tmap[LEN][LEN], int size, int num){
	struct snake *p;
	p = head->next;
	for (int i = 0; i < size; i++){               /*通路赋0，障碍物赋1*/
		for (int j = 0; j < size; j++){
			if (MAP[i][j] == ' ' || MAP[i][j] == '@')
				tmap[i][j] = 0;
			if (MAP[i][j] == '#')
				tmap[i][j] = 1;
		}
	}
	if (eBoom)
		tmap[by][bx] = 1;
	if (ePoison){
		for (int i = 0; i < num; i++)
			tmap[py[i]][px[i]] = 1;
	}
	while (p != NULL){                            /*除蛇头外的蛇身视为障碍物*/
		tmap[p->y][p->x] = 1;
		p = p->next;
	}
}

/*
函数名称：毒草计时
函数功能：使毒草存在10秒，时间到删除毒草
输入参数：是否正在计时timing，毒草个数hard
返回值：是否正在计时timing
*/
int poisonclock(int timing, int num){
	time_t end;
	static time_t start;                          /*静态变量，防止下次调用时清空*/
	if (timing == 0){
		start = time(NULL);
		timing = 1;
	}
	else{
		end = time(NULL);
		if (difftime(end, start) > 10.0){         /*计算时间差*/
			for (int i = 0; i < num; i++){
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

