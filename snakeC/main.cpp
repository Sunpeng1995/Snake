#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<graphics.h>

char HelloPage(void);
int play(int, int, int, int, int);
void drawHelloPage(int x, int y, TCHAR s[]);
void readRank(void);
void drawFood(int x, int y);
void drawBoom(int x, int y);
void drawPoison(int x, int y);
void drawWisdom(int x, int y);
void drawSnakeHead(int x, int y);
void drawSnakeBody(int x, int y);

int main(void){
	initgraph(600, 400);
	char choice, isload;
	while (1){
		setbkcolor(RGB(166, 255, 168));
		cleardevice();
		drawHelloPage(0, 0, _T("***************̰����***************\n��ѡ��ģʽ��\n1)����ģʽ   2)����ģʽ   3)�޾�ģʽ\n4)��Ϸ����   5)��Ϸ����   6)�˳���Ϸ\n"));
		choice = _getch();
		if (choice == '1'){
			drawHelloPage(0, 4, _T("��ѡ��\n1)����Ϸ   2)������Ϸ\n"));
			while (1){
				isload = _getch();
				if (isload == '1'){
					play(20, 1, 400, 1, 0);
					break;
				}
				else if (isload == '2'){
					play(20, 1, 400, 1, 1);
					break;
				}
				else
					continue;
			}
		}
		else if (choice == '2'){
			drawHelloPage(0, 4, _T("��ѡ��\n1)����Ϸ   2)������Ϸ\n"));
			while (1){
				isload = _getch();
				if (isload == '1'){
					play(20, 1, 400, 2, 0);
					break;
				}
				else if (isload == '2'){
					play(20, 1, 400, 2, 1);
					break;
				}
				else
					continue;
			}
		}
		else if (choice == '3'){
			drawHelloPage(0, 4, _T("��ѡ��\n1)����Ϸ   2)������Ϸ\n"));
			while (1){
				isload = _getch();
				if (isload == '1'){
					play(20, 3, 400, 3, 0);
					break;
				}
				else if (isload == '2'){
					play(20, 3, 400, 3, 1);
					break;
				}
				else
					continue;
			}
		}
		else if (choice == '4'){
			readRank();
		}
		else if (choice == '5'){
			LOGFONT f;
			cleardevice();
			settextcolor(BLACK);
			settextstyle(20, 0, _T("����"));
			gettextstyle(&f);
			f.lfQuality = PROOF_QUALITY;
			settextstyle(&f);
			outtextxy(260, 0, _T("��Ϸ����"));
			drawSnakeHead(1, 2);
			outtextxy(40, 40, _T("��ʾ��ͷ"));
			drawSnakeBody(7, 2);
			outtextxy(160, 40, _T("��ʾ����"));
			drawFood(1, 3);
			outtextxy(40, 60, _T("��ʾʳ��Ե���������һ��"));
			drawPoison(1, 4);
			outtextxy(40, 80, _T("��ʾ���ݣ��Ե���������һ�ڣ���Ϊ0ʱ��Ϸ������"));
			drawBoom(1, 5);
			outtextxy(40, 100, _T("��ʾ���ף��Ե�����ը��һ�볤�ȣ�����Ϊ1ʱ�Ե�������"));
			drawWisdom(1, 6);
			outtextxy(40, 120, _T("��ʾ�ǻ۲ݣ��Ե��߿��Զ����߳Ե���һ��ʳ��"));
			outtextxy(20, 140, _T("�÷���������ߵ��ƶ�����ǽ����"));
			outtextxy(20, 160, _T("�߿���ҧ���Լ���β�ͣ�������β�ͻ��Ϊ�ϰ����������"));
			outtextxy(20, 180, _T("������ģʽ������ϰ��ʮ�ּ�"));
			outtextxy(20, 200, _T("�ڴ���ģʽ�����أ��Ѷ��𼶵���"));
			outtextxy(20, 220, _T("���޾�ģʽ��ʤ�����������ƶ��ٶ��泤�����Ӷ�����"));
			outtextxy(20, 240, _T("  ƾ�����ߵͽ���Ӣ�۰�"));
			
			_getch();
		}
		else if (choice == '6')
			break;
		else {
			continue;
		}
	}
	return 0;
}