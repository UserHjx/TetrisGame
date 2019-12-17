#include <stdio.h> //标准的输入输出函数库 
#include <stdlib.h> //
#include <windows.h> //控制DOS界面(获取控制台上的坐标位置、设置字体颜色)
#include <conio.h> //接收键盘的输入和输出(Kbhit(),getch())
#include <time.h> //用于获得随机数 

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
  void welcom();//欢迎界面
  void Replay(struct Tetris * tetris);//重新开始游戏
  void title();//欢迎界面上方的标题
  void flower();//欢迎界面上的字符装饰花
  void close();//关闭游戏 
   
int main() {
	printf("俄罗斯方块\n"); 
	return 0;
}

