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
		drawHelloPage(0, 0, _T("***************贪吃蛇***************\n请选择模式：\n1)新手模式   2)闯关模式   3)无尽模式\n4)游戏排行   5)游戏规则   6)退出游戏\n"));
		choice = _getch();
		if (choice == '1'){
			drawHelloPage(0, 4, _T("请选择：\n1)新游戏   2)继续游戏\n"));
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
			drawHelloPage(0, 4, _T("请选择：\n1)新游戏   2)继续游戏\n"));
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
			drawHelloPage(0, 4, _T("请选择：\n1)新游戏   2)继续游戏\n"));
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
			settextstyle(20, 0, _T("宋体"));
			gettextstyle(&f);
			f.lfQuality = PROOF_QUALITY;
			settextstyle(&f);
			outtextxy(260, 0, _T("游戏规则"));
			drawSnakeHead(1, 2);
			outtextxy(40, 40, _T("表示蛇头"));
			drawSnakeBody(7, 2);
			outtextxy(160, 40, _T("表示蛇身"));
			drawFood(1, 3);
			outtextxy(40, 60, _T("表示食物，吃到蛇身增长一节"));
			drawPoison(1, 4);
			outtextxy(40, 80, _T("表示毒草，吃到蛇身缩短一节（减为0时游戏结束）"));
			drawBoom(1, 5);
			outtextxy(40, 100, _T("表示地雷，吃到蛇身炸掉一半长度（蛇身为1时吃到即死）"));
			drawWisdom(1, 6);
			outtextxy(40, 120, _T("表示智慧草，吃到蛇可自动行走吃到下一个食物"));
			outtextxy(20, 140, _T("用方向键控制蛇的移动，碰墙即死"));
			outtextxy(20, 160, _T("蛇可以咬断自己的尾巴，残留的尾巴会成为障碍物，碰到即死"));
			outtextxy(20, 180, _T("①新手模式仅供练习，十分简单"));
			outtextxy(20, 200, _T("②闯关模式有三关，难度逐级递增"));
			outtextxy(20, 220, _T("③无尽模式无胜利条件，蛇移动速度随长度增加而增加"));
			outtextxy(20, 240, _T("  凭分数高低进入英雄榜"));
			
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