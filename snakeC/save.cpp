#include"save.h"
/*
函数名称：存档
函数功能：保存当前一切游戏场景、分数
输入参数：游戏模式mode，蛇身长度length，难度hard，分数score，地图大小size，游戏速度speed
*/
void save(int mode, int length, int hard, int score, int size, int speed){
	FILE* fp;
	struct snake *p;
	p = head;
	MAP[fy][fx] = 'f';
	if (eBoom)
		MAP[by][bx] = 'b';
	if (eWisdom)
		MAP[wy][wx] = 'w';
	if (ePoison){
		for (int i = 0; i < hard; i++)
			MAP[py[i]][px[i]] = 'p';
	}                                            /*将存在的食物、毒草等转换成字符，保存在地图的二维数组中*/
	if (mode == 1)
		fp = fopen("save1", "wb");
	else if (mode == 2)
		fp = fopen("save2", "wb");
	else
		fp = fopen("save3", "wb");               /*对不同游戏模式创建不同的存档*/
	fwrite(&hard, sizeof(int), 1, fp);
	fwrite(&length, sizeof(int), 1, fp);
	fwrite(&score, sizeof(int), 1, fp);
	fwrite(&size, sizeof(int), 1, fp);
	fwrite(&speed, sizeof(int), 1, fp);
	for (int i = 0; i < LEN; i++){               /*保存地图的二维数组*/
		for (int j = 0; j < LEN; j++){
			fwrite(*(MAP + i) + j, sizeof(char), 1, fp);
		}
	}
	while (p != NULL){                           /*保存链表*/
		fwrite(p, sizeof(struct snake), 1, fp);
		p = p->next;
	}
	fclose(fp);
}

/*
函数名称：读档
函数功能：读取存档中的信息，转换成游戏内的各种参数
输入参数：游戏模式mode，蛇身长度指针*length，难度指针*hard，分数指针*score，地图大小指针*size，速度指针*speed
返回值：是否成功读取存档
*/
int load(int mode, int *length, int *hard, int *score, int *size, int *speed){
	FILE* fp;
	struct snake *newnode, *p;
	int count = 0;
	char tmap[LEN][LEN] = { ' ' };
	if (mode == 1)                               /*读取不同模式存档*/
		fp = fopen("save1", "rb");
	else if (mode == 2)
		fp = fopen("save2", "rb");
	else
		fp = fopen("save3", "rb");
	if (fp != NULL){
		fread(hard, sizeof(int), 1, fp);
		fread(length, sizeof(int), 1, fp);
		fread(score, sizeof(int), 1, fp);
		fread(size, sizeof(int), 1, fp);
		fread(speed, sizeof(int), 1, fp);
		for (int i = 0; i < LEN; i++){
			for (int j = 0; j < LEN; j++){
				fread(*(tmap + i) + j, sizeof(char), 1, fp);
				if (tmap[i][j] == 'f'){          /*读取地图中的食物*/
					eFood = 1;
					fy = i;
					fx = j;
					tmap[i][j] = ' ';
					drawLandBKG(fx, fy);
					drawFood(fx, fy);
				}
				else if (tmap[i][j] == 'b'){
					eBoom = 1;
					by = i;
					bx = j;
					tmap[i][j] = ' ';
					drawLandBKG(bx, by);
					drawBoom(bx, by);
				}
				else if (tmap[i][j] == 'w'){
					eWisdom = 1;
					wy = i;
					wx = j;
					tmap[i][j] = ' ';
					drawLandBKG(wx, wy);
					drawWisdom(wx, wy);
				}
				else if (tmap[i][j] == 'p'){
					ePoison = 1;
					py[count] = i;
					px[count] = j;
					count++;
					tmap[i][j] = ' ';
					drawLandBKG(px[count], py[count]);
					drawFood(px[count], py[count]);
				}
				else if (tmap[i][j] == '@')
					drawGrass(j, i);
				else if (tmap[i][j] == '#')      /*读取障碍物*/
					drawWall(j, i);
				else
					drawLandBKG(j, i);
			}
		}
		for (int i = 0; i < LEN; i++){
			for (int j = 0; j < LEN; j++){
				MAP[i][j] = tmap[i][j];
			}
		}
		head = (struct snake*)malloc(sizeof(struct snake));
		fread(head, sizeof(struct snake), 1, fp);
		drawSnakeHead(head->x, head->y);
		p = head;
		while (!feof(fp)){                       /*读取蛇的链表*/
			newnode = (struct snake*)malloc(sizeof(struct snake));
			fread(newnode, sizeof(struct snake), 1, fp);
			p->next = newnode;
			p = p->next;
		}
		p->next = NULL;
		tail = p;
		p = head;
		while (p->next->next != NULL){           /*删除因feof函数引起的多余节点*/
			p = p->next;
		}
		p->next = NULL;
		free(tail);
		tail = p;
		p = head->next;

		while (p != NULL){
			drawSnakeBody(p->x, p->y);
			p = p->next;
		}

		fclose(fp);
		return 1;
	}
	else{
		drawWordWindow(_T("无此存档"));
		system("pause");
		return 0;
	}
}