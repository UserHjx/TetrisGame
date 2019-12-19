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
			DrwaGameframe(); 
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
void DrwaGameframe()
{
	gotoxy(FrameX+Frame_width-7,FrameY-2);//设置游戏名称的显示位置
	color(11);//亮蓝色
	printf("趣味俄罗斯方块");
	gotoxy(FrameX+2*Frame_width+3,FrameY+7);//上边框的显示位置
	color(2);
	printf("**********");// 
	gotoxy(FrameX+2*Frame_width+13,FrameY+7);
	color(3);
	printf("下一个出现的方块：");
	gotoxy(FrameX+2*Frame_width+3,FrameY+13);
	color(2);
	printf("**********");
	gotoxy(FrameX+2*Frame_width+3,FrameY+17);
	color(14);
	printf("↑键：旋转");
	gotoxy(FrameX+2*Frame_width+3,FrameY+19);
	printf("空格：暂停游戏");
	gotoxy(FrameX+2*Frame_width+3,FrameY+15);
	printf("Esc：退出游戏");
	gotoxy(FrameX,FrameY);
	color(12);
	printf("╔");
	gotoxy(FrameX+2*Frame_width-2,FrameY);
	printf("╗");
	gotoxy(FrameX,FrameY+Frame_height);
	printf("╚");
	gotoxy(FrameX+2*Frame_width-2,FrameY+Frame_height);
	printf("╝");	
	a[FrameX][FrameY+Frame_height]=2;
	a[FrameX+2*Frame_width-2][FrameY+Frame_height]=2;
	for(i=2;i<2*Frame_width-2;i+=2)
	{
		gotoxy(FrameX+i,FrameY);
		printf("═");
	}
	for(i=2;i<2*Frame_width-2;i+=2)
	{
		gotoxy(FrameX+i,FrameY+Frame_height);
		printf("═");
		a[FrameX+i][FrameY+Frame_height]=2;//标记下横框为游戏边框，防止方块越界 
	}
	for(i=1;i<Frame_height;i++)
	{
		gotoxy(FrameX,FrameY+i);
		printf("║");	
		a[FrameX][FrameY+i]=2;//标记左横框为游戏边框，防止方块越界 
	} 
	for(i=1;i<Frame_height;i++)
	{
		gotoxy(FrameX+2*Frame_width-2,FrameY+i);
		printf("║");	
		a[FrameX][FrameY+i]=2;//标记右横框为游戏边框，防止方块越界 
	} 
}
void MakeTetris(struct Tetris *tetris)
{
	a[tetris->x][tetris->y]=b[0];//中心方块位置的图形状态
	switch(tetris->flag)
	{
		case 1 :/*田字方块 
		1 ■■2
		0 ■■3
		 */              
		{
			color(10);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x+2][tetris->y-1]=b[2];
			a[tetris->x+2][tetris->y]=b[3];
			break;
		}
		case 2 :/*一字方块
		 ■■■■
		 1 0 2 3  */                            
		{
			color(13);
			a[tetris->x-2][tetris->y]=b[1];
			a[tetris->x+2][tetris->y]=b[2];
			a[tetris->x+4][tetris->y]=b[3];
			break;
		}
		case 3 :/*竖一字方块
		 ■1
		 ■0
		 ■2
		 ■3  */                            
		{
			color(13);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x][tetris->y-2]=b[2];
			a[tetris->x][tetris->y+1]=b[3];
			break;
		}
		case 4 :/*T字方块 
		1 0 2
		■■■
		  ■3   */                            
		{
			color(11);
			a[tetris->x-2][tetris->y]=b[1];
			a[tetris->x+2][tetris->y]=b[2];
			a[tetris->x][tetris->y+1]=b[3];
			break;
		}
		case 5 :/*顺时针90度T字方块 
		  ■1
	   3■■0
		  ■2*/                            
		{
			color(11);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x][tetris->y+1]=b[2];
			a[tetris->x-2][tetris->y]=b[3];
			break;
		}	
		case 6 :/*顺时针180度T字方块 
		   ■1
		 ■■■
		 2 0 3  */                         
		{
			color(11);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x-2][tetris->y]=b[2];
			a[tetris->x+2][tetris->y]=b[3];
			break;
		}
		case 7 :/*顺时针270度T字方块
			■1
		   0■■3
			■2	*/                            
		{
			color(11);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x][tetris->y+1]=b[2];
			a[tetris->x+2][tetris->y]=b[3];
			break;
		}	
		case 8 :/*正Z字方块 
		2 0
		■■
		  ■■
		  1 3    */                            
		{
			color(14);
			a[tetris->x][tetris->y+1]=b[1];
			a[tetris->x-2][tetris->y]=b[2];
			a[tetris->x+2][tetris->y+1]=b[3];
			break;
		}	
		case 9 :/*顺时针正Z字方块
		   ■1
		2■■0
		3■
		 */                            
		{
			color(14);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x-2][tetris->y]=b[2];
			a[tetris->x-2][tetris->y+1]=b[3];
			break;
		}	
		case 10 :/*反Z字方块 
		   1 3
		   ■■
		 ■■
		 2 0
		   */                            
		{
			color(14);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x-2][tetris->y]=b[2];/////****自修改*****///////
			a[tetris->x+2][tetris->y-1]=b[3];
			break;
			/*****原代码******
			color(14);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x-2][tetris->y-1]=b[2];
			a[tetris->x+2][tetris->y]=b[3];	 
			break; 
			*/
		}	
		case 11 :/*顺时针90度反Z字方块
		 2■
		 3■■0
		    ■1
		   */                            
		{
			color(14);
			a[tetris->x][tetris->y+1]=b[1];
			a[tetris->x-2][tetris->y-1]=b[2];
			a[tetris->x-2][tetris->y]=b[3];
			break;
		}	
		case 12 :/*7字方块 
		3■■1
		   ■0
		   ■2
		  */                            
		{
			color(12);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x][tetris->y+1]=b[2];
			a[tetris->x-2][tetris->y-1]=b[3];
			break;
		}	
		case 13 :/*顺时针90度7字方块
		 	 ■2
		 ■■■
		 1 0 3
		 */                            
		{
			color(12);
			a[tetris->x-2][tetris->y]=b[1];
			a[tetris->x+2][tetris->y-1]=b[2];
			a[tetris->x+2][tetris->y]=b[3];
			break;
		}
		case 14 :/*顺时针180度7字方块
		1■
		0■
		2■■3
		*/                            
		{
			color(12);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x][tetris->y+1]=b[2];
			a[tetris->x+2][tetris->y+1]=b[3];
			break;
		}			
		case 15 :/*顺时针270度7字方块
		 1 0 3
		 ■■■
		 ■
		 2
		 */                            
		{ 
			color(12);
			a[tetris->x-2][tetris->y]=b[1];
			a[tetris->x-2][tetris->y+1]=b[2];
			a[tetris->x+2][tetris->y]=b[3];
			break;
		}			
		case 16 :/*反7字方块
		  2■■3
		  0■
		  1■
		  */                            
		{
			color(12);
			a[tetris->x][tetris->y+1]=b[1];
			a[tetris->x][tetris->y-1]=b[2];
			a[tetris->x+2][tetris->y-1]=b[3];
			break;
		}			
		case 17 :/*顺时针90度反7字方块 
		1 0 3
		■■■
		    ■2
		*/                            
		{
			color(12);
			a[tetris->x-2][tetris->y]=b[1];
			a[tetris->x+2][tetris->y+1]=b[2];
			a[tetris->x+2][tetris->y]=b[3];
			break;
		}			
		case 18 :/*顺时针180度反7字方块
		   ■1
		   ■0
		 ■■2
		 3
		 */                            
		{
			color(12);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x][tetris->y+1]=b[2];
			a[tetris->x-2][tetris->y+1]=b[3];
			break;
		}			
		case 19 :/*顺时针270度反7字方块
		 2
		 ■
		 ■■■
		 1 0 3
		 */                            
		{
			color(12);
			a[tetris->x-2][tetris->y]=b[1];
			a[tetris->x-2][tetris->y-1]=b[2];
			a[tetris->x+2][tetris->y]=b[3];
			break;
		}									
	} 
}

void PrintfTetris(struct Tetris *tetris)
{
	for(i =0;i<4;i++)//把每个元素的值都为1 
	{
		b[i]=1;	
	}
		
	MakeTetris(tetris);//制作俄罗斯方块 
	for(i=tetris->x-2;i<=tetris->x+4;i+=2)
	{
		for(j=tetris->y-2;j<=tetris->y+1;j++)//循环方块所有可能出现的位置 
		{
			if(a[i][j]==1&&j>FrameY+1)//如果这个位置上有方块 
			{
				gotoxy(i,j);
				printf("■");
			} 
		} 
		
	}
	//*******打印菜单信息********
	
	gotoxy(FrameX+2*Frame_width+3,FrameY+1);//设置打印位置
	color(4);
	printf("level: ");
	color(12);
	printf(" %d",tetris->level);
	gotoxy(FrameX+2*Frame_width+3,FrameY+3);
	color(4);
	printf("score: ");
	color(12);
	printf(" %d",tetris->score);
	gotoxy(FrameX+2*Frame_width+3,FrameY+5);
	color(4);
	printf("speed :");
	color(12);
	printf(" %dms",tetris->speed);
}
int ifMove(struct Tetris *tetris) 
{
	if(a[tetris->x][tetris->y]!=0)//当中心位置上有图案时，返回值为0，即不可移动 
	{
		return 0; 
	}
	else
	{
		/*
			旋转全是顺时针 
			1.田字方块  
			2.一字方块（横）  3.一字方块（竖） 
			4.T字方块  5.T字方块90度  6.T字方块180度   7.T字方块270度
			8.Z字方块  9.Z字方块180度  
			10.反Z字方块  11.反Z字方块180度 
			12.7字方块  13.7字方块90度   14.7字方块180度  15.7字方块270度
			16.反7字方块  17.反7字方块90度  18.反7字方块180度  19.反7字方块270度
	    */
		if(
		/*当为方块的flag值为1（1为田字方块）且除中心方块位置外，其他“■”字方块位置上无图案时，说明这个位置能够放下田字方块，可以移动到这个位置 ，返回值为1，即可移动 */
		( tetris->flag==1 && ( a[tetris->x][tetris->y-1]==0 && a[tetris->x+2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) ) || 
		( tetris->flag==2 && ( a[tetris->x-2][tetris->y]==0 && a[tetris->x+2][tetris->y]==0 && a[tetris->x+4][tetris->y]==0 ) ) ||
		( tetris->flag==3 && ( a[tetris->x][tetris->y-1]==0 && a[tetris->x][tetris->y-2]==0 && a[tetris->x][tetris->y+1]==0  )) ||
		( tetris->flag==4 && ( a[tetris->x-2][tetris->y]==0 && a[tetris->x+2][tetris->y]==0 && a[tetris->x][tetris->y+1]==0  )) ||
		( tetris->flag==5 && ( a[tetris->x][tetris->y-1]==0 && a[tetris->x][tetris->y+1]==0 && a[tetris->x-2][tetris->y]==0  )) ||
		( tetris->flag==6 && ( a[tetris->x][tetris->y-1]==0 && a[tetris->x-2][tetris->y]==0 && a[tetris->x+2][tetris->y]==0  )) ||
		( tetris->flag==7 && ( a[tetris->x][tetris->y-1]==0 && a[tetris->x][tetris->y+1]==0 && a[tetris->x+2][tetris->y]==0  )) ||
		( tetris->flag==8 && ( a[tetris->x][tetris->y+1]==0 && a[tetris->x-2][tetris->y]==0 && a[tetris->x+2][tetris->y+1]==0  )) ||
		( tetris->flag==9 && ( a[tetris->x][tetris->y-1]==0 && a[tetris->x-2][tetris->y]==0 && a[tetris->x-2][tetris->y+1]==0  )) ||
		( tetris->flag==10 && ( a[tetris->x][tetris->y-1]==0 && a[tetris->x-2][tetris->y]==0 && a[tetris->x+2][tetris->y-1]==0  )) ||
		( tetris->flag==11 && ( a[tetris->x][tetris->y+1]==0 && a[tetris->x-2][tetris->y-1]==0 && a[tetris->x-2][tetris->y]==0  )) ||
		( tetris->flag==12 && ( a[tetris->x][tetris->y-1]==0 && a[tetris->x][tetris->y+1]==0 && a[tetris->x-2][tetris->y-1]==0  )) ||
		( tetris->flag==13 && ( a[tetris->x-2][tetris->y]==0 && a[tetris->x+2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0  )) ||
		( tetris->flag==14 && ( a[tetris->x][tetris->y-1]==0 && a[tetris->x][tetris->y+1]==0 && a[tetris->x+2][tetris->y+1]==0  )) ||
		( tetris->flag==15 && ( a[tetris->x-2][tetris->y]==0 && a[tetris->x-2][tetris->y+1]==0 && a[tetris->x+2][tetris->y]==0  )) ||
		( tetris->flag==16 && ( a[tetris->x][tetris->y+1]==0 && a[tetris->x][tetris->y-1]==0 && a[tetris->x+2][tetris->y-1]==0  )) ||
		( tetris->flag==17 && ( a[tetris->x-2][tetris->y]==0 && a[tetris->x+2][tetris->y+1]==0 && a[tetris->x+2][tetris->y]==0  )) ||
		( tetris->flag==18 && ( a[tetris->x][tetris->y-1]==0 && a[tetris->x][tetris->y+1]==0 && a[tetris->x-2][tetris->y+1]==0  )) ||
		( tetris->flag==19 && ( a[tetris->x-2][tetris->y]==0 && a[tetris->x-2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0  )) 
		)
		{
			return 1; 
		} 
	}
	return 0;
}
void CleanTetris(struct Tetris *tetris)
{
	for(i=0;i<4;i++)//全部归零 
	{
		b[i]=0; 
	}
	MakeTetris(tetris);
	for( i = tetris->x - 2 ;i <= tetris->x+4; i += 2)
	{
		for(j = tetris->y-2; j <= tetris->y+1;j++)
		{
			if(a[i][j] == 0 && j>FrameY)
			{
				gotoxy(i,j);
				printf(" ");
			}
		}	
		
	} 	
}
void Del_Fullline(struct Tetris *tetris)//当某行有Frame_width-2个方块时，则满行消除
{
	int k,del_rows=0;//分别用于记录某行方块的个数和删除方块的行数的变量 
	for(j=FrameY+Frame_height-1;j>=FrameY+1;j--)
	{//j=22,j>=4,j--
		k=0;
		for(i=FrameX+2;i<FrameX+2*Frame_width-2;i+=2)//纵坐标依次从下往上，横坐标依次由左至右判断是否满行 
		{//i=15;i<(13+34)
			if(a[i][j]==1)
			{
				k++;//记录此行方块的个数 
				if(k==Frame_width-2)//如果满行 
				{
					for(k=FrameX+2;k<Frame_width-2;k+=2)//删除满行的方块 
					{
						a[k][j]=0;
						gotoxy(k,j);
						printf(" "); 
					}
					
					for(k=j-1;k>FrameY;k--)//如果删除行以上的位置有方块，则先消除，再将方块下移一个位置 
					{//(第一次)k=21;k>3;k--
						for(i=FrameX+2;i<FrameX+2*Frame_width-2;i+=2)
						{//i=15;i<47;i+=2 
							if(a[i][k]==1)
							{
								a[i][k]=0;
								gotoxy(i,k);
								printf(" ");
								a[i][k+1]=1;
								gotoxy(i,k+1);
								printf("■");
							}	
						} 
					}
					j++;//方块下移后，重新判断删除行是否满行
					del_rows++;//记录删除方块的行数 		
				}	
			} 
		}	
	}
	tetris->score+=100*del_rows;//每删除一行，得100分
	if(del_rows>0 && ( tetris->score % 1000 == 0 || tetris->score/1000>tetris->level-1))
	{//如果的1000分 即累计删除了10行， 速度加快20ms并升一级 
		tetris->speed-=20;
		tetris->level++; 
	} 
} 
void Flag(struct Tetris *tetris)
{
	tetris->number++;//记住产生方块的个数
	/*srand函数是随机数发生器的初始化函数。原型：void srand(unsigned int seed);srand和rand()配合使用产生伪随机数序列。
	srand()函数位于time.h头文件当中 
	*/	
	srand(time(NULL));//初始化随机数

	if(tetris->number==1)
	{
		tetris->flag = (rand()%19)+1;//记住第一个方块的序号 
	} 
	 tetris->next=rand()%19+1;//记住下一个方块的序号 
		
} 

  

  






