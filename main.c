#include <stdio.h> //标准的输入输出函数库 
#include <stdlib.h> //
#include <windows.h> //控制DOS界面(获取控制台上的坐标位置、设置字体颜色)
#include <conio.h> //接收键盘的输入和输出(Kbhit(),getch())
#include <time.h> //用于获得随机数
//#include "AllCode.c" 


/*******宏定义********/
#define FrameX 13 //游戏窗口左上角的X轴坐标为13
#define FrameY 3 // 游戏窗口左上角的Y轴坐标为3
#define Frame_height 20 //游戏窗口的高度为 20
#define Frame_width 18 //游戏窗口的宽度为 18

 /*******定义全局变量********/
 int i,j,Temp,Temp1,Temp2;//Temp,Temp1,Temp2用来记住和转换方块变量的值
 //标记游戏屏幕的图案：2,1,0分别表示该位置为游戏边框、方块、无图案
 int a[80][80]={0};
 int b[4];//标记4个“口 ”方块：1表示有方块，0表示无方块
  
 struct Tetris//声明俄罗斯方块的结构体 
 {
	int x;//中心方块的x轴坐标 
	int y;//中心方块的y轴坐标 
	int flag;//标记方块类型的序号 
	int next;//下一个俄罗斯方块类型的序号 
	int speed;//俄罗斯方块的移动速度 
	int number;//产生俄罗斯方块的个数 
	int score;//游戏的分数 
	int level; 	//游戏的等级 
 	
 };
 HANDLE hOut; //控制台句柄 

  int color(int c); 
  void gotoxy(int x,int y) ;//光标移到指定位置
  void DrwaGameframe(); //绘制游戏边框
  void Flag(struct Tetris*);//随机产生方块类型的序号
  void MakeTetris(struct Tetris*);//制作俄罗斯方块
  void PrintTetris(struct Tetris*);//打印俄罗斯方块
  void CleanTetris(struct Tetris*);//清楚俄罗斯方块的痕迹
  int ifMove(struct Tetris*);//判断是否能移动，返回值为1时能移动，否则不能移动
  void Del_Fullline(struct Tetris *);//判断是否满行，并删除满行的俄罗斯方块
  void Gameplay();//开始游戏
  void regulation(); //游戏规则
  void explation();//按键说明
  void welcome();//欢迎界面
  void Replay(struct Tetris * tetris);//重新开始游戏
  void title();//欢迎界面上方的标题
  void flower();//欢迎界面上的字符装饰花
  void close();//关闭游戏 
 
int main() 
{
	title(); 
	flower();
	welcome();
	return 0;
}
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);//更改文字颜色 
	return 0;
}
void gotoxy(int x,int y)
{
	COORD pos;//
	pos.X = x;//横坐标 
	pos.Y = y;//纵坐标
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos); 
}
void title()
{
	color(15);//亮白色
	gotoxy(24,3);//
	printf("趣  味  俄  罗  斯  方  块\n");
	color(11);//亮蓝色
	gotoxy(18,5);
	printf("■"); 
	gotoxy(18,6);
	printf("■■");
	gotoxy(18,7);	
	printf("■"); 
	
	color(14);//黄色 
	gotoxy(26,6);
	printf("■■");
	gotoxy(28,7);	
	printf("■■");
	
	color(10);//绿色
	gotoxy(36,6);	
	printf("■■");	
	gotoxy(36,7);	
	printf("■■");
	
	color(13);//粉色
	gotoxy(45,5);
	printf("■"); 	
	gotoxy(45,6);
	printf("■");		
	gotoxy(45,7);
	printf("■");	
	gotoxy(45,8);
	printf("■");	
	
	color(12);//亮红色
	gotoxy(56,6);			
	printf("■");
	gotoxy(52,7);			
	printf("■■■");			
}
void flower()
{
	gotoxy(66,11);//确定屏幕上要输出的位置
	color(12);//设置颜色
	printf("(_)");//红花上面的花瓣 

	gotoxy(64,12);
	printf("(_)");//红花左边花瓣
	
	gotoxy(68,12);
	printf("(_)");//红花右边花瓣
	
	gotoxy(66,13);
	printf("(_)");//红花下边花瓣
	
	gotoxy(67,12);//花蕊 
	color(6);//
	printf("@");//
	
	gotoxy(72,10);// 
	color(13);//
	printf("(_)");//粉花左边花瓣 
	
	gotoxy(76,10);// 
	printf("(_)");//粉花右边花瓣 

	gotoxy(74,9);// 
	printf("(_)");//粉花上边花瓣 
	
	gotoxy(74,11);// 
	printf("(_)");//粉花下边花瓣 
	
	gotoxy(75,10);//花蕊 
	color(6);//
	printf("@");//
	
	gotoxy(71,12);
	printf("|"); 
	
	gotoxy(72,11);
	printf("/"); 
	
	gotoxy(70,13);
	printf("\\|");//注意“\”为转义字符，所以打两遍
	 
	gotoxy(70,14);
	printf("`|/"); 	
	
	gotoxy(70,15);
	printf("\\|");
	
	gotoxy(71,16);
	printf("| /"); 	
	
	gotoxy(71,17);	
	printf("|"); 
	
	gotoxy(67,17);
	color(10);
	printf("\\\\\\\\");//草地	
	
	gotoxy(73,17);
	printf("//"); 
	
	gotoxy(67,18);
	color(2);
	printf("^^^^^^^");
	
	gotoxy(66,19);
	color(5);
	printf("何  锦  贤"); 		
}
void welcome()
{
	int n;
	int i,j=1;
	color(14);//黄色 
	for(i=9;i<=20;i++)//循环y轴坐标，打印输出上下边框=== 
	{
		for(j = 15;j<=60;j++)//循环x轴坐标，打印输出上下边框||
		{
			gotoxy(j,i);
			if(i==9||i==20)
			{
				printf("=");
			}
			else if(j == 15 || j==59)
			{
				printf("||");
			}
		}
	}
	/*
	*菜单里的文字 
	*/
	
	color(12);//红色
	gotoxy(25,12);
	printf("1.开始游戏");
	gotoxy(40,12);
	printf("2.按键说明");
	gotoxy(25,17);
	printf("3.游戏规则");
	gotoxy(40,17);
	printf("4.退出");
	gotoxy(21,22);
	color(3);
	printf("请选择[1 2 3 4]:[ ]\b\b");
	color(14);
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			system("cls");//清屏
			break;
		case 2:
			//
			break;
		case 3:
			//
			break;
		case 4:
			//
			break;
	}
}

  






