#include"game.h"

/*
�������ƣ���Ϸ������
�������ܣ�������Ϸ�����庯��������Ϸ�е��¼����д���
�����������ͼ��Сsize����Ϸ�Ѷ�hard����Ϸ�ٶ�speed����Ϸģʽmode���Ƿ�����浵isload����ͼ���mapnum
*/
int play(int size, int hard, int speed, int mode, int isload, int mapnum){
	eFood = 0, ePoison = 0, eBoom = 0, eWisdom = 0;
	bx = 0, by = 0, wx = 0, wy = 0;
	for (int i = 0; i < hard; i++){
		px[i] = 0;
		py[i] = 0;
	}                                            /*��ʼ������ʳ������Ϊ0*/
	int timing = 0;
	int score = 0, ranksave, loadcorrect;
	int keylast = 0;
	int length = 1, life = 1;
	int showPoison = 0;
	setbkcolor(BLACK);
	cleardevice();
	srand((unsigned)time(NULL));
	if (isload == 0){                            /*����Ƿ�Ҫ��ȡ�浵*/
		normalMap(size, mapnum);                 /*��ʼ����ͼ*/
		head = (struct snake*)malloc(sizeof(struct snake));
		head->x = rand() % (size - 2) + 1;
		head->y = rand() % (size - 2) + 1;
		head->next = NULL;
		tail = head;
		drawSnakeHead(head->x, head->y);
		setFood(size, hard);
	}
	else{                                        /*����浵*/
		loadcorrect = load(mode, &length, &hard, &score, &size, &speed);
		if (loadcorrect == 0){
			return 0;
		}
	}

	keylast = _getch();
	while (1){
		Sleep(speed);                            /*��Ϸ�ٶ�*/
		drawWordText(size + 1, 1, _T("��ǰ�������֣���"));
		drawWordBKG(size + 1, 3);
		drawNumber(size + 1, 3, score + length * 10);
		drawWordText(size + 1, 5, _T("��ǰ�����ڣ���"));
		drawWordBKG(size + 1, 7);
		drawNumber(size + 1, 7, length);
		drawWordText(size + 1, 9, _T("��ǰ�ٶȣ�ms/������"));
		drawWordBKG(size + 1, 11);
		drawNumber(size + 1, 11, speed);
		drawWordText(size + 1, 13, _T("���ո���ͣ��Ϸ"));
		drawWordBKG(size + 1, 14);
		drawGrass(size + 1, 14);
		drawWordText(size + 2, 14, _T("-�Ӳ�"));
		drawWordBKG(size + 1, 15);
		drawFood(size + 1, 15);
		drawWordText(size + 2, 15, _T("-ʳ��"));
		drawWordBKG(size + 1, 16);
		drawPoison(size + 1, 16);
		drawWordText(size + 2, 16, _T("-����"));
		drawWordBKG(size + 1, 17);
		drawBoom(size + 1, 17);
		drawWordText(size + 2, 17, _T("-����"));
		drawWordBKG(size + 1, 18);
		drawWisdom(size + 1, 18);
		drawWordText(size + 2, 18, _T("-�ǻ۲�"));
		/*��Ϸ�������ͼ��*/

		keylast = control(keylast, length, size);
		if (keylast == -1){
			save(mode, length, hard, score, size, speed);
			return 0;
		}
		move(keylast);
		head = direct;
		if (MAP[head->y][head->x] == '#')        /*ײǽ*/
			life = 0;
		if (length > 4){
			length = eatSelf(length, &score);    /*ҧ���Լ�*/
		}
		drawSnakeHead(head->x, head->y);
		showPoison = flashpoison(ePoison, showPoison, hard);
		if (direct->x != fx || direct->y != fy)  /*��ʳ��*/
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
		if (direct->x == bx && direct->y == by && eBoom == 1){/*�Ե���*/
			length = boom(length);
			score /= 2; 
		}
		for (int i = 0; i < hard; i++){          /*�Զ���*/
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
		if (direct->x == wx && direct->y == wy && eWisdom == 1){/*���ǻ۲�*/
			keylast = wisdom(size, hard, speed);
			eWisdom = 0;
			score += 50;
		}

		if (ePoison)                             /*�ش�ӡһ��ʳ��*/
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
		
		if (mode == 2 && length == 5){           /*����ģʽ��֧*/
			if (hard == 3){
				drawWordWindow(_T("��ϲ�㣬ͨ���ˣ�"));
				_getch();
				break;
			}
			else{
				drawWordWindow(_T("������һ�أ�"));
				_getch();
				play(size, hard + 1, speed - 100, 2, 0, mapnum + 1);
				break;
			}
		}
		if (mode == 3)                           /*�޾�ģʽ��֧*/
			speed = 400 - (length - 1) * 5;

		if (length == 0)                         /*�����ж�*/
			life = 0;
		if (life == 0)
			break;
	}

	if (life == 0){
		drawWordWindow(_T("��Ϸʧ��"));
		if (mode == 3){
			dealRank(score + length * 10);
		}
		system("pause");
	}
	return 0;
}

/*
�������ƣ����̿���
�������ܣ���ȡ������Ӧ����Ӧ��ͬ���¼�
����������ϴεķ���keylast���߳���length����ͼ��Сsize
����ֵ������ֵ��-1ʱ���д浵
*/
int control(int keylast, int length, int size){
	int key, keytemp, save;
	key = keylast;
	if (_kbhit()){
		keytemp = _getch();
		if (keytemp == 0xE0 || keytemp == 0)     /*��ȡ���ܼ�*/
			keytemp = _getch();
		else if (keytemp == 32){                 /*��ͣʱ*/
			drawWordBKG(size + 1, 14);
			drawWordBKG(size + 1, 15);
			drawWordText(size + 1, 15, _T("��Ϸ����ͣ..."));
			drawWordBKG(size + 1, 16);
			drawWordText(size + 1, 16, _T("�ո��-������Ϸ"));
			drawWordBKG(size + 1, 17);
			drawWordText(size + 1, 17, _T("ESC��-���沢�˳�"));
			drawWordBKG(size + 1, 18);
			while (1){
				save = _getch();
				if (save == 32){                 /*��ԭʱ*/
					drawWordBKG(size + 1, 14);
					drawGrass(size + 1, 14);
					drawWordText(size + 2, 14, _T("-�Ӳ�"));
					drawWordBKG(size + 1, 15);
					drawFood(size + 1, 15);
					drawWordText(size + 2, 15, _T("-ʳ��"));
					drawWordBKG(size + 1, 16);
					drawPoison(size + 1, 16);
					drawWordText(size + 2, 16, _T("-����"));
					drawWordBKG(size + 1, 17);
					drawBoom(size + 1, 17);
					drawWordText(size + 2, 17, _T("-����"));
					drawWordBKG(size + 1, 18);
					drawWisdom(size + 1, 18);
					drawWordText(size + 2, 18, _T("-�ǻ۲�"));
					drawWordText(size + 1, 13, _T("���ո���ͣ��Ϸ"));
					keytemp = keylast;
					break;
				}
				else if (save == 27){
					system("cls");
					return -1;                   /*�浵*/
				}
				else
					continue;
			}
		}
		if (length > 1){                         /*ֻ��һ��ʱ��ת������*/
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
�������ƣ��ƶ�
�������ܣ���һ���µ�ͷ����deltail��������ʵ���ƶ�
�������������key
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
�������ƣ�ɾ��β��
�������ܣ�ɾ���������β�ڵ㣬������Ļ�ϲ���
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
�������ƣ�ҧ���Լ�
�������ܣ����������Լ�������ʱ����֮�������ڵ�ضϣ�����ϰ�����۷�
���������������length����ǰ����ָ�����*score
����ֵ���µ�������
*/
int eatSelf(int length, int *score){
	struct snake *p, *temp;
	int count;
	p = head->next;
	temp = head->next;
	while (p->next != NULL){
		p = p->next;
		if (p->x == direct->x&&p->y == direct->y){/*����Ƿ�ͷ�ڵ��Ƿ������Լ�����*/
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
		while (p != NULL){                       /*����Ļ�ϲ�����������ϰ���*/
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

