#include <iostream>
#include <conio.h>
#include <ctime>
#include <stdio.h>
#include <graphics.h>
using namespace std;
HWND hwnd = NULL;
struct set
{
	int x;
	int y;
};
//蛇类
class snake1
{public:
	int length;
	set set[200];
	char dire;
}snake;
//食物类
class food1
{public:
	set set;
	int score=0;
}food;
enum { u, d, l, r, n };
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
		setlinecolor(WHITE);
		setfillcolor(WHITE);
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
	setlinecolor(WHITE);
	setfillcolor(WHITE);
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
//反snake.dire
int antisnake()
{
	char a;
	if (snake.dire == u)
		a = d;
	else if (snake.dire == d)
		a = u;
	else if (snake.dire == r)
		a = l;
	else if (snake.dire == l)
		a = r;
	return a;
}
//自动恰食
int getauto()
{
	int x,y;
	char d1,d2;
	if (snake.set[0].x < food.set.x)
	{
		x = (food.set.x - snake.set[0].x) / 10;
		d1 = r;
	}
	else if (snake.set[0].x > food.set.x)
	{
		x = (snake.set[0].x - food.set.x) / 10;
		d1 = l;
	}
	else x = 0;
	if (snake.set[0].y < food.set.y)
	{
		y = (food.set.y - snake.set[0].y) / 10;
		d2 = d;
	}
	else if (snake.set[0].y > food.set.y)
	{
		y = (snake.set[0].y - food.set.y) / 10;
		d2 = u;
	}
	else y = 0;
	if (x != 0 && y != 0)
	{
		if (antisnake() == d1)
			return d2;
		else return d1;
	}
	if (x == 0 && y != 0)
	{
		if (antisnake() == d2)
			return r;
		else return d2;
	}
	if (y == 0 && x != 0)
	{
		if (antisnake() == d1)
			return u;
		else return d1;
	}
}
//避免撞到自己
int destory(int i)
{
	set a[200];
	char d1;
	for (int j = snake.length +3; j > 0; j--)
	{
		a[j].x = snake.set[j - 1].x;
	    a[j].y = snake.set[j - 1].y;
	}
	a[0].x = snake.set[0].x;
	a[0].y = snake.set[0].y;
	switch (i)
	{
	case u:
	{
		a[0].y -= 10;
		break;
	}
	case d:
	{
		a[0].y += 10;
		break;
	}
	case r:
	{
		a[0].x += 10;
		break;
	}
	case l:
	{
		a[0].x -= 10;
		break;
	}
	}
	for (int e = snake.length - 1; e > 3; e--)
	{
		if (a[0].x == a[e].x&&a[0].y == a[e].y)
		{
			//左下，向上
			if (a[e].y < a[e - 1].y&&a[e + 2].x < a[e + 1].x) i = l;
			//左下，向右
			else if (a[e].x > a[e - 1].x&&a[e + 2].y > a[e + 1].y) i = d;
			//左上，向右
			else if (a[e].x > a[e - 1].x&&a[e + 2].y < a[e + 1].y) i = u;
			//左上，向下
			else if (a[e].y > a[e - 1].y&&a[e + 2].x > a[e + 1].x) i = l;
			//右上，向左
			else if (a[e].x < a[e - 1].x&&a[e + 2].y < a[e + 1].y) i = u;
			//右下，向左
			else if (a[e].x < a[e - 1].x&&a[e + 2].y > a[e + 1].y) i = d;
			//右上，向下
			else if (a[e].y > a[e - 1].y&&a[e + 2].x < a[e + 1].x) i = r;
			//右下，向上
			else if (a[e].y < a[e - 1].y&&a[e + 2].x > a[e + 1].x) i = r;
			else if (a[e].x < a[e-1].x)
			{
				i = l; 
			}
			else if (a[e].x > a[e - 1].x)
			{
				i = r; 
			}
			else if (a[e].y < a[e - 1].y)
			{
				i = u; 
			}
			else if (a[e].y > a[e - 1].y)
			{
				i = d; 
			}
		}
	}
	return i;
}
//自动控制
void control1(int i)
{
	switch (i)
	{
	case u:
		if (snake.dire != d)
			snake.dire = u;
		break;
	case d:
		if (snake.dire != u)
			snake.dire = d;
		break;
	case l:
		if (snake.dire != r)
			snake.dire = l; 

		break;
	case r:
		if (snake.dire != l)
			snake.dire = r;
		break;
	}
}
//选择模式
int choose()
{
	return MessageBox(hwnd, "是否开启自动模式", "选择模式", MB_YESNO);
}
//主函数
int main()
{
	srand((int)time(NULL));
	hwnd=initgraph(640, 400);
	setbkcolor(BLACK);
	cleardevice();
	if (choose() == 6)
	{
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
			control1(destory(getauto()));
			gosnake();
			drawsnake();
			if (border())
			{
				over();
				break;
			}
			score(); 
			Sleep(1);
		}
		drawsnake();
	}
	else 
	{
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
	}
	
	while(_getch())
		continue;
	closegraph();
	return 0;
}
