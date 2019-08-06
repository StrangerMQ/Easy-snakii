#include <iostream>
#include <conio.h>
#include <ctime>
#include <stdio.h>
#include <graphics.h>
using namespace std;

struct set
{
	int x;
	int y;
};
//蛇类
class snake1
{public:
	int length;
	set set[100];
	char dire;
}snake;
//食物类
class food1
{public:
	set set;
	int score=0;
}food;
enum{u,d,l,r};
//初始化蛇
void makesnake()
{
	snake.set[2].x = 10;
	snake.set[2].y = 10;
	snake.set[1].x = 20;
	snake.set[1].y = 10;
	snake.set[0].x = 30;
	snake.set[0].y = 10;
	snake.length = 3;
	snake.dire = r;
}
//画出蛇（坐标）
void drawsnake() 
{
	for (int i = 0; i < snake.length; i++)
	{
		setlinecolor(BLACK);
		setfillcolor(GREEN);
		fillrectangle(snake.set[i].x, snake.set[i].y, snake.set[i].x + 10, snake.set[i].y + 10);
	}
}
//移动蛇
void gosnake()
{
	for (int i = snake.length - 1; i > 0; i--)
	{
		snake.set[i].x = snake.set[i - 1].x;
		snake.set[i].y = snake.set[i - 1].y;
	}



	switch (snake.dire)
	{
	case u:
	{
		snake.set[0].y -=  10;
		break;
	}
	case d:
	{
		snake.set[0].y +=  10;
		break;
	}
	case r:
	{
		snake.set[0].x +=  10;
		break;
	}
	case l:
	{
		snake.set[0].x -= 10;
		break;
	}
	}
}
//控制蛇
void control()
{
	char m='\0';
	m = _getch();
	switch (m)
	{
	case 'W':
	case 'w':
	case 72:
		if (snake.dire != d)
			snake.dire = u;
		break;
	case 'S':
	case 's':
	case 80:
		if (snake.dire != u)
			snake.dire = d;
		break;
	case 'A':
	case 'a':
	case 75:
		if (snake.dire != r)
			snake.dire = l;
		break;
	case 'D':
	case 'd':
	case 77:
		if (snake.dire != l)
		snake.dire = r;
		break;
	}
}
//检查边界
int border()
{
	if (snake.set[0].x >= 640 || snake.set[0].x < 0)
		return 1;
	else if (snake.set[0].y >= 400 || snake.set[0].y < 0)
		return 1;
	else return 0;

}
//撞到自己
int hurt()
{
	int j = 0;
	for (int i = snake.length - 1; i > 0; i--)
	{
		if (snake.set[0].x == snake.set[i].x&&snake.set[0].y == snake.set[i].y)
		{
			return 1;
			break;
		}
		j++;
	}
	if (j == snake.length - 1)
		return 0;
}
//计分板
void score()
{
	char grade[200];
	sprintf_s(grade, "%d", food.score);
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	outtextxy(530, 20, "SCORE:");
	outtextxy(600, 20, grade);
}
//初始化食物
void makefood()
{
	food.set.x = rand() % 63 * 10;
	food.set.y = rand() % 39 * 10;
	for (int i = 0; i < snake.length; i++)
	{
		while (snake.set[i].x == food.set.x&&snake.set[i].y == food.set.y)
		{
			
			food.set.x = rand() % 63 * 10;
		    food.set.y = rand() % 39 * 10;
		}
	}
	
}
//画出食物
void drawfood()
{
	setlinecolor(RED);
	setfillcolor(RED);
	fillrectangle(food.set.x, food.set.y, food.set.x + 10, food.set.y + 10);
}
//判断吃食物
void checkfood()
{
	if (snake.set[0].x == food.set.x&&snake.set[0].y == food.set.y)
	{
		makefood();
		food.score++;
		snake.length++;
	}
}
//结算画面
void over()
{
	char grade[200];
	sprintf_s(grade, "%d", food.score);
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	outtextxy(280, 160, "WASTED");
	outtextxy(265, 180, "YOUR SCORE:");
	outtextxy(305, 200, grade);
}
//自动恰食
void automod()
{

}
//主函数
int main()
{
	srand((int)time(NULL));
	initgraph(640, 400);
	setbkcolor(WHITE);
	cleardevice();
	makesnake();
	makefood();
	while (1)
	{
		cleardevice();
		checkfood();
		drawfood();
		if (hurt())
		{
			over();
			break;
		}
		drawsnake();
		if (border())
		{
			over();
			break;
		}
		score();
		gosnake();
		Sleep(100);
		while (_kbhit())
		{
			control();
		}
	}
	drawsnake();
	
	while(_getch())
		continue;
	closegraph();
	return 0;
}
