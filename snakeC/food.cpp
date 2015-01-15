#include"food.h"
/*
�������ƣ�����ʳ��
�������ܣ��������ʳ���ȷ�������ǵ�ͼ�����еĶ���
�����������ͼ��Сsize���Ѷ�hard
*/
int setFood(int size, int hard){
	int wisdom, poison;
	int tmap[LEN][LEN];
	srand((unsigned)time(NULL));               /*�������������*/
	wisdom = rand() % 5;
	poison = rand() % 3;                       /*������ʳ��������֣�������Ϊ1ʱ����*/
	reflect(tmap, size, hard);                 /*�ѵ�ǰ��ͼ���ѱ�ռ�õ�λ�ü�¼����*/
	tmap[head->y][head->x] = 1;
	if (eWisdom)
		tmap[wy][wx] = 1;                      /*reflect������ȱ�ǻ۲ݺ���ͷ�����꣬���ﲹ��*/
	if (!eFood){
		do{
			fx = rand() % (size - 2) + 1;
			fy = rand() % (size - 2) + 1;
		} while (tmap[fy][fx] != 0);           /*do whileѭ����ȷ�����������ڵ�ͼ�ѱ�ռ�õĵط�*/
		drawFood(fx, fy);                      /*��ӡʳ��*/
		eFood = 1;
	}
	if (!eBoom){
		do{
			bx = rand() % (size - 2) + 1;
			by = rand() % (size - 2) + 1;
		} while (tmap[by][bx] != 0);
		drawBoom(bx, by);                      /*����ͬ��*/
		eBoom = 1;
	}
	if ((!eWisdom) && wisdom == 1){
		do{
			wx = rand() % (size - 2) + 1;
			wy = rand() % (size - 2) + 1;
		} while (tmap[wy][wx] != 0);
		drawWisdom(wx, wy);                    /*�ǻ۲�ͬ��*/
		eWisdom = 1;
	}
	if ((!ePoison) && poison == 1){
		for (int i = 0; i < hard; i++){
			do{
				px[i] = rand() % (size - 2) + 1;
				py[i] = rand() % (size - 2) + 1;
			} while (tmap[py[i]][px[i]] != 0);
			drawFood(px[i], py[i]);            /*��������������3������hard����������*/
		}
		ePoison = 1;
	}
	return 0;
}

/*
�������ƣ��Ӳ�ʵ��
�������ܣ��ڵ�ͼ���������һ���Ӳ�
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
�������ƣ�����ʵ��
�������ܣ����ߵĳ��ȼ��룬��������벿����
����������߳�length
����ֵ���µ��߳�newlength
*/
int boom(int length){                          /*����length����������ը���Ľ���*/
	if (length == 1){
		eBoom = 0;
		return 0;
	}
	int newlength, temp;
	struct snake *p, *del;
	p = head;
	temp = length / 2;
	newlength = length - temp;
	for (int i = 0; i < newlength - 1; i++){   /*�������µĳ��ȴ����ض�����*/
		p = p->next;
	}
	del = p->next;
	p->next = NULL;
	tail = p;
	while (del != NULL){                       /*�����ضϵ�֮�����������Ļ�ϲ���*/
		p = del;
		del = del->next;
		drawLandBKG(p->x, p->y);
		free(p);
	}
	eBoom = 0;
	return newlength;
}

/*
�������ƣ�������˸
�������ܣ�ʹ��������Ļ����˸
��������������Ƿ����exist������Ŀǰ����˸״̬show�����ݸ���num
����ֵ������Ŀǰ����˸״̬show
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
�������ƣ��ǻ۲�ʵ��
�������ܣ�ʵ���ߵ��Զ�Ѱ·���ܿ��ϰ�����ݡ�ը�����Ե�ʳ��
�����������ͼ��Сsize�����ݸ���num����Ϸ�ٶ�speed
����ֵ������key
*/
int wisdom(int size, int num, int speed){
	int tmap[LEN][LEN], exist, key;
	struct node queue[512], path[64], food, end;
	struct snake *p;
	reflect(tmap, size, num);
	food = pack(fx, fy, -3);
	end = pack(head->x, head->y, -3);            /*�趨���Ϊʳ��յ�Ϊ�Ե��ǻ۲�ʱ����ͷ*/
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
		}                                        /*�����ҵ���·��������Ļ�ϴ�ӡ�ߵ��ƶ�*/
		if (head->x + 1 == fx)
			key = RIGHT;
		else if (head->x - 1 == fx)
			key = LEFT;
		else if (head->y + 1 == fy)
			key = DOWN;
		else
			key = UP;
	}                                            /*����ʳ���ڸ�ʱ���ж�ʳ�����ĸ����򣬲�����֮*/
	qhead = 0;
	qtail = 0;
	return key;
}

/*
�������ƣ��������
�������ܣ����ṹ��ѹ�����
�����������Ľṹ��n���ṹ������queue
*/
void enqueue(struct node n, struct node queue[512]){
	queue[qtail] = n;
	qtail++;
}

/*
�������ƣ��뿪����
�������ܣ������е�һ���ṹ�嵯�����У����в���
����������ṹ�����queue
����ֵ����Ľṹ��
*/
struct node dequeue(struct node queue[512]){
	qhead++;
	return queue[qhead - 1];
}

/*
�������ƣ���װ����
�������ܣ�����ͼ��һ��������һ����Ľṹ�壬���������ϼҵĶ����е�λ��
�����������ĺ�����x�����������y���ϼ��ڶ����е�λ��pre
����ֵ���õ�Ľṹ��t
*/
struct node pack(int x, int y, int pre){
	struct node t;
	t.x = x;
	t.y = y;
	t.preIndex = pre;
	return t;
}

/*
�������ƣ���Ѱ·��
�������ܣ�ͨ����������������ҳ�һ����̵�·��
���������������ϰ���ĵ�ͼ��ά����maze�����ṹ��start���յ�ṹ��end����������queue��·������path
����ֵ���Ƿ����·��
*/
int findPath(int maze[LEN][LEN], struct node start, struct node end, struct node queue[512], struct node path[64]){
	struct node qtemp;
	queue[0].x = start.x;
	queue[0].y = start.y;
	queue[0].preIndex = -1;
	maze[start.y][start.x] = 2;
	qtail = 1;
	while (qtail != qhead){                       /*���в�Ϊ��ʱ*/
		qtemp = dequeue(queue);
		if (qtemp.x == end.x && qtemp.y == end.y) /*����Ƿ񵽴��յ�*/
			break;
		if (maze[qtemp.y + 1][qtemp.x] == 0){     /*�����ýڵ���������ҽڵ��Ƿ�ɵ���*/
			maze[qtemp.y + 1][qtemp.x] = 2;       /*��̽�����Ľڵ���Ϊ2*/
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
	if (qtemp.x == end.x && qtemp.y == end.y){    /*��·����������path��*/
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
�������ƣ���ͼӳ��
�������ܣ�����Ϸ��ͼ�е��ϰ�����ݡ����ף���1��0����ʽӳ�䵽�µĶ�ά������
����������µĶ�ά����tmap����ͼ��Сsize�����ݸ���num
*/
void reflect(int tmap[LEN][LEN], int size, int num){
	struct snake *p;
	p = head->next;
	for (int i = 0; i < size; i++){               /*ͨ·��0���ϰ��︳1*/
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
	while (p != NULL){                            /*����ͷ���������Ϊ�ϰ���*/
		tmap[p->y][p->x] = 1;
		p = p->next;
	}
}

/*
�������ƣ����ݼ�ʱ
�������ܣ�ʹ���ݴ���10�룬ʱ�䵽ɾ������
����������Ƿ����ڼ�ʱtiming�����ݸ���hard
����ֵ���Ƿ����ڼ�ʱtiming
*/
int poisonclock(int timing, int num){
	time_t end;
	static time_t start;                          /*��̬��������ֹ�´ε���ʱ���*/
	if (timing == 0){
		start = time(NULL);
		timing = 1;
	}
	else{
		end = time(NULL);
		if (difftime(end, start) > 10.0){         /*����ʱ���*/
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

