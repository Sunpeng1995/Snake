#include<graphics.h>
#include<stdio.h>


void drawWall(int x, int y){
	x *= 20;
	y *= 20;
	setfillcolor(RGB(255, 162, 0));
	solidrectangle(x, y, x + 20, y + 20);
}

void drawLandBKG(int x, int y){
	x *= 20;
	y *= 20;
	setfillcolor(RGB(132, 230, 116));
	solidrectangle(x, y, x + 20, y + 20);
}

void drawSnakeHead(int x, int y){
	x *= 20;
	y *= 20;
	setfillcolor(RGB(87, 255, 245));
	solidcircle(x + 10, y + 10, 9);
}

void drawSnakeBody(int x, int y){
	x *= 20;
	y *= 20;
	setfillcolor(RGB(245, 92, 186));
	solidcircle(x + 10, y + 10, 9);
}

void drawFood(int x, int y){
	IMAGE img;
	x *= 20;
	y *= 20;
	loadimage(&img, _T("food.bmp"));
	putimage(x, y, &img);
}

void drawPoison(int x, int y){
	IMAGE img;
	x *= 20;
	y *= 20;
	loadimage(&img, _T("poison.bmp"));
	putimage(x, y, &img); 
}

void drawBoom(int x, int y){
	IMAGE img;
	x *= 20;
	y *= 20;
	loadimage(&img, _T("boom.bmp"));
	putimage(x, y, &img);
}

void drawWisdom(int x, int y){
	IMAGE img;
	x *= 20;
	y *= 20;
	loadimage(&img, _T("wisdom.bmp"));
	putimage(x, y, &img);
}

void drawGrass(int x, int y){
	IMAGE img;
	x *= 20;
	y *= 20;
	loadimage(&img, _T("grass.bmp"));
	putimage(x, y, &img);
}

void drawWordText(int x, int y, TCHAR s[]){
	LOGFONT f;
	settextcolor(WHITE);
	settextstyle(20, 0, _T("黑体"));
	gettextstyle(&f);
	f.lfQuality = PROOF_QUALITY;
	settextstyle(&f);
	outtextxy(x * 20, y * 20, s);
}

void drawNumber(int x, int y, int num){
	x *= 20;
	y *= 20;
	LOGFONT f;
	TCHAR s[5];
	RECT r = { x, y, x + 200, y + 20 };
	settextcolor(RGB(255, 0, 150));
	settextstyle(20, 0, _T("黑体"));
	_stprintf(s, _T("%d"), num);
	gettextstyle(&f);
	f.lfQuality = PROOF_QUALITY;
	settextstyle(&f);
	drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void drawWordWindow(TCHAR s[]){
	LOGFONT f;
	RECT r = { 0, 0, 400, 400 };
	setfillcolor(RED);
	solidrectangle(95, 145, 305, 255);
	setfillcolor(RGB(95, 200, 244));
	solidrectangle(100, 150, 300, 250);
	settextcolor(RGB(255, 0, 150));
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, _T("黑体"));
	gettextstyle(&f);
	f.lfQuality = PROOF_QUALITY;
	settextstyle(&f);
	drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void drawWordBKG(int x, int y){
	x *= 20;
	y *= 20;
	setfillcolor(BLACK);
	solidrectangle(x, y, x + 200, y + 20);
}

void drawHelloPage(int x, int y, TCHAR s[]){
	LOGFONT f;
	RECT r = { x*20, y*20, 600, 400 };
	settextcolor(BLACK);
	settextstyle(20, 0, _T("黑体"));
	gettextstyle(&f);
	f.lfQuality = PROOF_QUALITY;
	settextstyle(&f);
	drawtext(s, &r, DT_CENTER);
}