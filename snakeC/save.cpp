#include"save.h"
/*
�������ƣ��浵
�������ܣ����浱ǰһ����Ϸ����������
�����������Ϸģʽmode��������length���Ѷ�hard������score����ͼ��Сsize����Ϸ�ٶ�speed
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
	}                                            /*�����ڵ�ʳ����ݵ�ת�����ַ��������ڵ�ͼ�Ķ�ά������*/
	if (mode == 1)
		fp = fopen("save1", "wb");
	else if (mode == 2)
		fp = fopen("save2", "wb");
	else
		fp = fopen("save3", "wb");               /*�Բ�ͬ��Ϸģʽ������ͬ�Ĵ浵*/
	fwrite(&hard, sizeof(int), 1, fp);
	fwrite(&length, sizeof(int), 1, fp);
	fwrite(&score, sizeof(int), 1, fp);
	fwrite(&size, sizeof(int), 1, fp);
	fwrite(&speed, sizeof(int), 1, fp);
	for (int i = 0; i < LEN; i++){               /*�����ͼ�Ķ�ά����*/
		for (int j = 0; j < LEN; j++){
			fwrite(*(MAP + i) + j, sizeof(char), 1, fp);
		}
	}
	while (p != NULL){                           /*��������*/
		fwrite(p, sizeof(struct snake), 1, fp);
		p = p->next;
	}
	fclose(fp);
}

/*
�������ƣ�����
�������ܣ���ȡ�浵�е���Ϣ��ת������Ϸ�ڵĸ��ֲ���
�����������Ϸģʽmode��������ָ��*length���Ѷ�ָ��*hard������ָ��*score����ͼ��Сָ��*size���ٶ�ָ��*speed
����ֵ���Ƿ�ɹ���ȡ�浵
*/
int load(int mode, int *length, int *hard, int *score, int *size, int *speed){
	FILE* fp;
	struct snake *newnode, *p;
	int count = 0;
	char tmap[LEN][LEN] = { ' ' };
	if (mode == 1)                               /*��ȡ��ͬģʽ�浵*/
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
				if (tmap[i][j] == 'f'){          /*��ȡ��ͼ�е�ʳ��*/
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
				else if (tmap[i][j] == '#')      /*��ȡ�ϰ���*/
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
		while (!feof(fp)){                       /*��ȡ�ߵ�����*/
			newnode = (struct snake*)malloc(sizeof(struct snake));
			fread(newnode, sizeof(struct snake), 1, fp);
			p->next = newnode;
			p = p->next;
		}
		p->next = NULL;
		tail = p;
		p = head;
		while (p->next->next != NULL){           /*ɾ����feof��������Ķ���ڵ�*/
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
		drawWordWindow(_T("�޴˴浵"));
		system("pause");
		return 0;
	}
}