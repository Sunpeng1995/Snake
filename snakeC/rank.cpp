#include<stdio.h>
#include<string.h>
#include<graphics.h>

struct rankinf{
	TCHAR name[20];
	int sumscore;
};

/*
函数名称：排行榜存储
函数功能：将新的分数存入排行榜，并进行排序，在屏幕上显示排行榜
输入参数：分数score
*/
void dealRank(int score){
	struct rankinf temp, *p, sort[11] = { 0 };
	int clash = 0;
	temp.sumscore = score;
	InputBox(temp.name, 20, _T("请输入你的名字"));
	FILE* fp;
	fp = fopen("rank", "rb");                    /*先读取文件中的排行榜*/
	if (fp != NULL){
		for (int i = 1; !feof(fp); i++){
			fread(sort + i, sizeof(struct rankinf), 1, fp);
		}
		fclose(fp);
	}
	for (int i = 1; i < 12; i++){                /*检测是否与原有名字重合*/
		if (_tcscmp(temp.name, sort[i].name) == 0){
			if (temp.sumscore>sort[i].sumscore){
				sort[i] = temp;
				clash = 1;
			}
			else
				clash = 2;
			break;
		}
	}
	if (clash == 0){
		sort[0] = temp;
	}
	for (int i = 0; i < 11; i++){                /*进行选择排序*/
		p = sort + i;
		for (int j = i + 1; j < 11; j++){
			if (p->sumscore < sort[j].sumscore)
				p = sort + j;
		}
		temp = sort[i];
		sort[i] = *p;
		*p = temp;
	}
	setbkcolor(WHITE);                           /*在屏幕上显示排行榜*/
	cleardevice();
	outtextxy(0, 0, _T("--------------英雄榜--------------\n"));
	outtextxy(0, 20, _T("排名   姓名        得分\n"));
	for (int i = 0; i < 10; i++){
		TCHAR s[30];
		_stprintf(s, _T("%2d.    %-8s    %-4d"), i + 1, sort[i].name, sort[i].sumscore);
		outtextxy(0, (i + 2) * 20, s);
	}
	fp = fopen("rank", "wb");                    /*将新的排行榜存入文件*/
	for (int i = 0; i < 10; i++){
		fwrite(sort + i, sizeof(struct rankinf), 1, fp);
	}
	fclose(fp);
}

/*
函数名称：排行榜读取
函数功能：只对文件中的排行榜进行读取
*/
void readRank(void){
	struct rankinf temp, *p, sort[11] = { 0 };
	FILE* fp;
	fp = fopen("rank", "rb");
	if (fp != NULL){
		for (int i = 0; !feof(fp); i++){
			fread(sort + i, sizeof(struct rankinf), 1, fp);
		}
		fclose(fp);
	}
	cleardevice();
	outtextxy(0, 0, _T("--------------英雄榜--------------\n"));
	outtextxy(0, 20, _T("排名   姓名        得分\n"));
	for (int i = 0; i < 10; i++){
		TCHAR s[30];
		_stprintf(s, _T("%2d.    %-8s%-4d"), i + 1, sort[i].name, sort[i].sumscore);
		outtextxy(0, (i + 2) * 20, s);
	}
	system("pause");
}