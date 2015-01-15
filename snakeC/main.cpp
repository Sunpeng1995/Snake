#include"main.h"

int main(void){
	initgraph(600, 400);                            //初始化600*400大小的画布
	char choice, isload;
	int mission;
	while (1){                                      //死循环，结束游戏后返回开始界面
		setbkcolor(RGB(166, 255, 168));
		cleardevice();
		drawHelloPage(0, 0, _T("***************贪吃蛇***************\n请选择模式：\n1)新手模式   2)闯关模式   3)无尽模式\n4)游戏排行   5)游戏规则   6)退出游戏\n"));
		choice = _getch();
		if (choice == '1'){
			drawHelloPage(0, 4, _T("请选择：\n1)新游戏   2)继续游戏\n"));
			while (1){                              //死循环，同上
				isload = _getch();
				if (isload == '1'){
					drawHelloPage(0, 6, _T("请选择地图：1)第一关   2)第二关   3)第三关"));
					while (1){
						mission = _getch();
						if (mission == '1'){
							mission = 1;
							break;
						}
						else if (mission == '2'){
							mission = 2;
							break;
						}
						else if (mission == '3'){
							mission = 3;
							break;
						}
						else
							continue;
					}
					drawHelloPage(0, 7, _T("请选择难度：1)简单   2)中等   3)困难"));
					while (1){
						int level;
						level = _getch();
						if (level == '1'){
							play(20, 1, 400, 1, 0, mission);
							break;
						}
						else if (level == '2'){
							play(20, 2, 300, 1, 0, mission);
							break;
						}
						else if (level == '3'){
							play(20, 3, 200, 1, 0, mission);
							break;
						}
						else
							continue;
					}
					break;
				}
				else if (isload == '2'){
					play(20, 1, 400, 1, 1, 1);
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
					play(20, 1, 400, 2, 0, 1);
					break;
				}
				else if (isload == '2'){
					play(20, 1, 400, 2, 1, 1);
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
					play(20, 3, 400, 3, 0, 1);
					break;
				}
				else if (isload == '2'){
					play(20, 3, 400, 3, 1, 1);
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
			rule();
		}
		else if (choice == '6')
			break;
		else {
			continue;
		}
	}
	return 0;
}

void rule(void){                   //游戏规则
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
	outtextxy(20, 180, _T("①练习模式仅供练习，可以自选地图，自选难度"));
	outtextxy(20, 200, _T("②闯关模式有三关，难度逐级递增"));
	outtextxy(20, 220, _T("③无尽模式无胜利条件，蛇移动速度随长度增加而增加"));
	outtextxy(20, 240, _T("④无尽模式中草地特别肥沃，杂草疯长，每次吃到食物，"));
	outtextxy(20, 260, _T("  都有几率出现杂草，蛇、食物等进入杂草即不可见"));
	outtextxy(20, 280, _T("  游戏结束凭分数高低进入英雄榜"));

	_getch();
}