#include <iostream>
#include <math.h>
#include <stdio.h>
#include <time.h>
//#include <graphics.h>
#include <regraph.h>

using namespace std;

main() {
	initwindow(170, 470);
	setbkcolor(WHITE);
	cleardevice();
	
	int colors[] = { BLUE, LIGHTGREEN, RED, YELLOW };
    int c = sizeof(colors)/4;
    for(int i = 0; i <= 10; i++) {
    	setcolor(colors[i%c]);
    	settextstyle(i, 0, 5);
    	outtextxy(10, i * 40, "TEXT");
    }
	
	
	getch();
	closegraph();
}
