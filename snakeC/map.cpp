#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define LEN 20

char MAP[LEN][LEN];


//n为地图大小
void normalMap(int n){
	void drawWall(int x, int y);
	void drawLandBKG(int x, int y);
	int i, j;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			if (i == 0 || i == n - 1 || j == 0 || j == n - 1)
				MAP[i][j] = '#';
			else
				MAP[i][j] = ' ';
			if (MAP[i][j] == '#')
				drawWall(j, i);
			else
				drawLandBKG(j, i);
		}
	}
}

