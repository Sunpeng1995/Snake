#include<stdio.h>
#include<string.h>
#include<graphics.h>

void drawHelloPage(int x, int y, TCHAR s[]);

struct rankinf{
	TCHAR name[20];
	int sumscore;
};

void dealRank(int score){
	struct rankinf temp, *p, sort[11] = { 0 };
	int clash = 0;
	temp.sumscore = score;
	InputBox(temp.name, 20, _T("�������������"));
	FILE* fp;
	fp = fopen("rank", "rb");
	if (fp != NULL){
		for (int i = 1; !feof(fp); i++){
			fread(sort + i, sizeof(struct rankinf), 1, fp);
		}
		fclose(fp);
	}
	for (int i = 1; i < 12; i++){
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
	for (int i = 0; i < 11; i++){//ѡ������
		p = sort + i;
		for (int j = i + 1; j < 11; j++){
			if (p->sumscore < sort[j].sumscore)
				p = sort + j;
		}
		temp = sort[i];
		sort[i] = *p;
		*p = temp;
	}
	setbkcolor(WHITE);
	cleardevice();
	outtextxy(0, 0, _T("--------------Ӣ�۰�--------------\n"));
	outtextxy(0, 20, _T("����   ����        �÷�\n"));
	for (int i = 0; i < 10; i++){
		TCHAR s[30];
		_stprintf(s, _T("%2d.    %-8s    %-4d"), i + 1, sort[i].name, sort[i].sumscore);
		outtextxy(0, (i + 2) * 20, s);
	}
	fp = fopen("rank", "wb");
	for (int i = 0; i < 10; i++){
		fwrite(sort + i, sizeof(struct rankinf), 1, fp);
	}
	fclose(fp);
}

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
	outtextxy(0, 0, _T("--------------Ӣ�۰�--------------\n"));
	outtextxy(0, 20, _T("����   ����        �÷�\n"));
	for (int i = 0; i < 10; i++){
		TCHAR s[30];
		_stprintf(s, _T("%2d.    %-8s%-4d"), i + 1, sort[i].name, sort[i].sumscore);
		outtextxy(0, (i + 2) * 20, s);
	}
	system("pause");
}