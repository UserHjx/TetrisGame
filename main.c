#include <stdio.h> //��׼��������������� 
#include <stdlib.h> //
#include <windows.h> //����DOS����(��ȡ����̨�ϵ�����λ�á�����������ɫ)
#include <conio.h> //���ռ��̵���������(Kbhit(),getch())
#include <time.h> //���ڻ�������
//#include "AllCode.c" 


/*******�궨��********/
#define FrameX 13 //��Ϸ�������Ͻǵ�X������Ϊ13
#define FrameY 3 // ��Ϸ�������Ͻǵ�Y������Ϊ3
#define Frame_height 20 //��Ϸ���ڵĸ߶�Ϊ 20
#define Frame_width 18 //��Ϸ���ڵĿ��Ϊ 18

 /*******����ȫ�ֱ���********/
 int i,j,Temp,Temp1,Temp2;//Temp,Temp1,Temp2������ס��ת�����������ֵ
 //�����Ϸ��Ļ��ͼ����2,1,0�ֱ��ʾ��λ��Ϊ��Ϸ�߿򡢷��顢��ͼ��
 int a[80][80]={0};
 int b[4];//���4������ �����飺1��ʾ�з��飬0��ʾ�޷���
  
 struct Tetris//��������˹����Ľṹ�� 
 {
	int x;//���ķ����x������ 
	int y;//���ķ����y������ 
	int flag;//��Ƿ������͵���� 
	int next;//��һ������˹�������͵���� 
	int speed;//����˹������ƶ��ٶ� 
	int number;//��������˹����ĸ��� 
	int score;//��Ϸ�ķ��� 
	int level; 	//��Ϸ�ĵȼ� 
 	
 };
 HANDLE hOut; //����̨��� 

  int color(int c); 
  void gotoxy(int x,int y) ;//����Ƶ�ָ��λ��
  void DrwaGameframe(); //������Ϸ�߿�
  void Flag(struct Tetris*);//��������������͵����
  void MakeTetris(struct Tetris*);//��������˹����
  void PrintTetris(struct Tetris*);//��ӡ����˹����
  void CleanTetris(struct Tetris*);//�������˹����ĺۼ�
  int ifMove(struct Tetris*);//�ж��Ƿ����ƶ�������ֵΪ1ʱ���ƶ����������ƶ�
  void Del_Fullline(struct Tetris *);//�ж��Ƿ����У���ɾ�����еĶ���˹����
  void Gameplay();//��ʼ��Ϸ
  void regulation(); //��Ϸ����
  void explation();//����˵��
  void welcome();//��ӭ����
  void Replay(struct Tetris * tetris);//���¿�ʼ��Ϸ
  void title();//��ӭ�����Ϸ��ı���
  void flower();//��ӭ�����ϵ��ַ�װ�λ�
  void close();//�ر���Ϸ 
 
int main() 
{
	title(); 
	flower();
	welcome();
	return 0;
}
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);//����������ɫ 
	return 0;
}
void gotoxy(int x,int y)
{
	COORD pos;//
	pos.X = x;//������ 
	pos.Y = y;//������
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos); 
}
void title()
{
	color(15);//����ɫ
	gotoxy(24,3);//
	printf("Ȥ  ζ  ��  ��  ˹  ��  ��\n");
	color(11);//����ɫ
	gotoxy(18,5);
	printf("��"); 
	gotoxy(18,6);
	printf("����");
	gotoxy(18,7);	
	printf("��"); 
	
	color(14);//��ɫ 
	gotoxy(26,6);
	printf("����");
	gotoxy(28,7);	
	printf("����");
	
	color(10);//��ɫ
	gotoxy(36,6);	
	printf("����");	
	gotoxy(36,7);	
	printf("����");
	
	color(13);//��ɫ
	gotoxy(45,5);
	printf("��"); 	
	gotoxy(45,6);
	printf("��");		
	gotoxy(45,7);
	printf("��");	
	gotoxy(45,8);
	printf("��");	
	
	color(12);//����ɫ
	gotoxy(56,6);			
	printf("��");
	gotoxy(52,7);			
	printf("������");			
}
void flower()
{
	gotoxy(66,11);//ȷ����Ļ��Ҫ�����λ��
	color(12);//������ɫ
	printf("(_)");//�컨����Ļ��� 

	gotoxy(64,12);
	printf("(_)");//�컨��߻���
	
	gotoxy(68,12);
	printf("(_)");//�컨�ұ߻���
	
	gotoxy(66,13);
	printf("(_)");//�컨�±߻���
	
	gotoxy(67,12);//���� 
	color(6);//
	printf("@");//
	
	gotoxy(72,10);// 
	color(13);//
	printf("(_)");//�ۻ���߻��� 
	
	gotoxy(76,10);// 
	printf("(_)");//�ۻ��ұ߻��� 

	gotoxy(74,9);// 
	printf("(_)");//�ۻ��ϱ߻��� 
	
	gotoxy(74,11);// 
	printf("(_)");//�ۻ��±߻��� 
	
	gotoxy(75,10);//���� 
	color(6);//
	printf("@");//
	
	gotoxy(71,12);
	printf("|"); 
	
	gotoxy(72,11);
	printf("/"); 
	
	gotoxy(70,13);
	printf("\\|");//ע�⡰\��Ϊת���ַ������Դ�����
	 
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
	printf("\\\\\\\\");//�ݵ�	
	
	gotoxy(73,17);
	printf("//"); 
	
	gotoxy(67,18);
	color(2);
	printf("^^^^^^^");
	
	gotoxy(66,19);
	color(5);
	printf("��  ��  ��"); 		
}
void welcome()
{
	int n;
	int i,j=1;
	color(14);//��ɫ 
	for(i=9;i<=20;i++)//ѭ��y�����꣬��ӡ������±߿�=== 
	{
		for(j = 15;j<=60;j++)//ѭ��x�����꣬��ӡ������±߿�||
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
	*�˵�������� 
	*/
	
	color(12);//��ɫ
	gotoxy(25,12);
	printf("1.��ʼ��Ϸ");
	gotoxy(40,12);
	printf("2.����˵��");
	gotoxy(25,17);
	printf("3.��Ϸ����");
	gotoxy(40,17);
	printf("4.�˳�");
	gotoxy(21,22);
	color(3);
	printf("��ѡ��[1 2 3 4]:[ ]\b\b");
	color(14);
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			system("cls");//����
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
	gotoxy(FrameX+Frame_width-7,FrameY-2);//������Ϸ���Ƶ���ʾλ��
	color(11);//����ɫ
	printf("Ȥζ����˹����");
	gotoxy(FrameX+2*Frame_width+3,FrameY+7);//�ϱ߿����ʾλ��
	color(2);
	printf("**********");// 
	gotoxy(FrameX+2*Frame_width+13,FrameY+7);
	color(3);
	printf("��һ�����ֵķ��飺");
	gotoxy(FrameX+2*Frame_width+3,FrameY+13);
	color(2);
	printf("**********");
	gotoxy(FrameX+2*Frame_width+3,FrameY+17);
	color(14);
	printf("��������ת");
	gotoxy(FrameX+2*Frame_width+3,FrameY+19);
	printf("�ո���ͣ��Ϸ");
	gotoxy(FrameX+2*Frame_width+3,FrameY+15);
	printf("Esc���˳���Ϸ");
	gotoxy(FrameX,FrameY);
	color(12);
	printf("�X");
	gotoxy(FrameX+2*Frame_width-2,FrameY);
	printf("�[");
	gotoxy(FrameX,FrameY+Frame_height);
	printf("�^");
	gotoxy(FrameX+2*Frame_width-2,FrameY+Frame_height);
	printf("�a");	
	a[FrameX][FrameY+Frame_height]=2;
	a[FrameX+2*Frame_width-2][FrameY+Frame_height]=2;
	for(i=2;i<2*Frame_width-2;i+=2)
	{
		gotoxy(FrameX+i,FrameY);
		printf("�T");
	}
	for(i=2;i<2*Frame_width-2;i+=2)
	{
		gotoxy(FrameX+i,FrameY+Frame_height);
		printf("�T");
		a[FrameX+i][FrameY+Frame_height]=2;//����º��Ϊ��Ϸ�߿򣬷�ֹ����Խ�� 
	}
	for(i=1;i<Frame_height;i++)
	{
		gotoxy(FrameX,FrameY+i);
		printf("�U");	
		a[FrameX][FrameY+i]=2;//�������Ϊ��Ϸ�߿򣬷�ֹ����Խ�� 
	} 
	for(i=1;i<Frame_height;i++)
	{
		gotoxy(FrameX+2*Frame_width-2,FrameY+i);
		printf("�U");	
		a[FrameX][FrameY+i]=2;//����Һ��Ϊ��Ϸ�߿򣬷�ֹ����Խ�� 
	} 
}
void MakeTetris(struct Tetris *tetris)
{
	a[tetris->x][tetris->y]=b[0];//���ķ���λ�õ�ͼ��״̬
	switch(tetris->flag)
	{
		case 1 :/*���ַ��� 
		1 ����2
		0 ����3
		 */              
		{
			color(10);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x+2][tetris->y-1]=b[2];
			a[tetris->x+2][tetris->y]=b[3];
			break;
		}
		case 2 :/*һ�ַ���
		 ��������
		 1 0 2 3  */                            
		{
			color(13);
			a[tetris->x-2][tetris->y]=b[1];
			a[tetris->x+2][tetris->y]=b[2];
			a[tetris->x+4][tetris->y]=b[3];
			break;
		}
		case 3 :/*��һ�ַ���
		 ��1
		 ��0
		 ��2
		 ��3  */                            
		{
			color(13);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x][tetris->y-2]=b[2];
			a[tetris->x][tetris->y+1]=b[3];
			break;
		}
		case 4 :/*T�ַ��� 
		1 0 2
		������
		  ��3   */                            
		{
			color(11);
			a[tetris->x-2][tetris->y]=b[1];
			a[tetris->x+2][tetris->y]=b[2];
			a[tetris->x][tetris->y+1]=b[3];
			break;
		}
		case 5 :/*˳ʱ��90��T�ַ��� 
		  ��1
	   3����0
		  ��2*/                            
		{
			color(11);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x][tetris->y+1]=b[2];
			a[tetris->x-2][tetris->y]=b[3];
			break;
		}	
		case 6 :/*˳ʱ��180��T�ַ��� 
		   ��1
		 ������
		 2 0 3  */                         
		{
			color(11);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x-2][tetris->y]=b[2];
			a[tetris->x+2][tetris->y]=b[3];
			break;
		}
		case 7 :/*˳ʱ��270��T�ַ���
			��1
		   0����3
			��2	*/                            
		{
			color(11);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x][tetris->y+1]=b[2];
			a[tetris->x+2][tetris->y]=b[3];
			break;
		}	
		case 8 :/*��Z�ַ��� 
		2 0
		����
		  ����
		  1 3    */                            
		{
			color(14);
			a[tetris->x][tetris->y+1]=b[1];
			a[tetris->x-2][tetris->y]=b[2];
			a[tetris->x+2][tetris->y+1]=b[3];
			break;
		}	
		case 9 :/*˳ʱ����Z�ַ���
		   ��1
		2����0
		3��
		 */                            
		{
			color(14);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x-2][tetris->y]=b[2];
			a[tetris->x-2][tetris->y+1]=b[3];
			break;
		}	
		case 10 :/*��Z�ַ��� 
		   1 3
		   ����
		 ����
		 2 0
		   */                            
		{
			color(14);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x-2][tetris->y]=b[2];/////****���޸�*****///////
			a[tetris->x+2][tetris->y-1]=b[3];
			break;
			/*****ԭ����******
			color(14);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x-2][tetris->y-1]=b[2];
			a[tetris->x+2][tetris->y]=b[3];	 
			break; 
			*/
		}	
		case 11 :/*˳ʱ��90�ȷ�Z�ַ���
		 2��
		 3����0
		    ��1
		   */                            
		{
			color(14);
			a[tetris->x][tetris->y+1]=b[1];
			a[tetris->x-2][tetris->y-1]=b[2];
			a[tetris->x-2][tetris->y]=b[3];
			break;
		}	
		case 12 :/*7�ַ��� 
		3����1
		   ��0
		   ��2
		  */                            
		{
			color(12);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x][tetris->y+1]=b[2];
			a[tetris->x-2][tetris->y-1]=b[3];
			break;
		}	
		case 13 :/*˳ʱ��90��7�ַ���
		 	 ��2
		 ������
		 1 0 3
		 */                            
		{
			color(12);
			a[tetris->x-2][tetris->y]=b[1];
			a[tetris->x+2][tetris->y-1]=b[2];
			a[tetris->x+2][tetris->y]=b[3];
			break;
		}
		case 14 :/*˳ʱ��180��7�ַ���
		1��
		0��
		2����3
		*/                            
		{
			color(12);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x][tetris->y+1]=b[2];
			a[tetris->x+2][tetris->y+1]=b[3];
			break;
		}			
		case 15 :/*˳ʱ��270��7�ַ���
		 1 0 3
		 ������
		 ��
		 2
		 */                            
		{ 
			color(12);
			a[tetris->x-2][tetris->y]=b[1];
			a[tetris->x-2][tetris->y+1]=b[2];
			a[tetris->x+2][tetris->y]=b[3];
			break;
		}			
		case 16 :/*��7�ַ���
		  2����3
		  0��
		  1��
		  */                            
		{
			color(12);
			a[tetris->x][tetris->y+1]=b[1];
			a[tetris->x][tetris->y-1]=b[2];
			a[tetris->x+2][tetris->y-1]=b[3];
			break;
		}			
		case 17 :/*˳ʱ��90�ȷ�7�ַ��� 
		1 0 3
		������
		    ��2
		*/                            
		{
			color(12);
			a[tetris->x-2][tetris->y]=b[1];
			a[tetris->x+2][tetris->y+1]=b[2];
			a[tetris->x+2][tetris->y]=b[3];
			break;
		}			
		case 18 :/*˳ʱ��180�ȷ�7�ַ���
		   ��1
		   ��0
		 ����2
		 3
		 */                            
		{
			color(12);
			a[tetris->x][tetris->y-1]=b[1];
			a[tetris->x][tetris->y+1]=b[2];
			a[tetris->x-2][tetris->y+1]=b[3];
			break;
		}			
		case 19 :/*˳ʱ��270�ȷ�7�ַ���
		 2
		 ��
		 ������
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
	for(i =0;i<4;i++)//��ÿ��Ԫ�ص�ֵ��Ϊ1 
	{
		b[i]=1;	
	}
		
	MakeTetris(tetris);//��������˹���� 
	for(i=tetris->x-2;i<=tetris->x+4;i+=2)
	{
		for(j=tetris->y-2;j<=tetris->y+1;j++)//ѭ���������п��ܳ��ֵ�λ�� 
		{
			if(a[i][j]==1&&j>FrameY+1)//������λ�����з��� 
			{
				gotoxy(i,j);
				printf("��");
			} 
		} 
		
	}
	//*******��ӡ�˵���Ϣ********
	
	gotoxy(FrameX+2*Frame_width+3,FrameY+1);//���ô�ӡλ��
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
	if(a[tetris->x][tetris->y]!=0)//������λ������ͼ��ʱ������ֵΪ0���������ƶ� 
	{
		return 0; 
	}
	else
	{
		/*
			��תȫ��˳ʱ�� 
			1.���ַ���  
			2.һ�ַ��飨�ᣩ  3.һ�ַ��飨���� 
			4.T�ַ���  5.T�ַ���90��  6.T�ַ���180��   7.T�ַ���270��
			8.Z�ַ���  9.Z�ַ���180��  
			10.��Z�ַ���  11.��Z�ַ���180�� 
			12.7�ַ���  13.7�ַ���90��   14.7�ַ���180��  15.7�ַ���270��
			16.��7�ַ���  17.��7�ַ���90��  18.��7�ַ���180��  19.��7�ַ���270��
	    */
		if(
		/*��Ϊ�����flagֵΪ1��1Ϊ���ַ��飩�ҳ����ķ���λ���⣬�����������ַ���λ������ͼ��ʱ��˵�����λ���ܹ��������ַ��飬�����ƶ������λ�� ������ֵΪ1�������ƶ� */
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
	for(i=0;i<4;i++)//ȫ������ 
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
void Del_Fullline(struct Tetris *tetris)//��ĳ����Frame_width-2������ʱ������������
{
	int k,del_rows=0;//�ֱ����ڼ�¼ĳ�з���ĸ�����ɾ������������ı��� 
	for(j=FrameY+Frame_height-1;j>=FrameY+1;j--)
	{//j=22,j>=4,j--
		k=0;
		for(i=FrameX+2;i<FrameX+2*Frame_width-2;i+=2)//���������δ������ϣ��������������������ж��Ƿ����� 
		{//i=15;i<(13+34)
			if(a[i][j]==1)
			{
				k++;//��¼���з���ĸ��� 
				if(k==Frame_width-2)//������� 
				{
					for(k=FrameX+2;k<Frame_width-2;k+=2)//ɾ�����еķ��� 
					{
						a[k][j]=0;
						gotoxy(k,j);
						printf(" "); 
					}
					
					for(k=j-1;k>FrameY;k--)//���ɾ�������ϵ�λ���з��飬�����������ٽ���������һ��λ�� 
					{//(��һ��)k=21;k>3;k--
						for(i=FrameX+2;i<FrameX+2*Frame_width-2;i+=2)
						{//i=15;i<47;i+=2 
							if(a[i][k]==1)
							{
								a[i][k]=0;
								gotoxy(i,k);
								printf(" ");
								a[i][k+1]=1;
								gotoxy(i,k+1);
								printf("��");
							}	
						} 
					}
					j++;//�������ƺ������ж�ɾ�����Ƿ�����
					del_rows++;//��¼ɾ����������� 		
				}	
			} 
		}	
	}
	tetris->score+=100*del_rows;//ÿɾ��һ�У���100��
	if(del_rows>0 && ( tetris->score % 1000 == 0 || tetris->score/1000>tetris->level-1))
	{//�����1000�� ���ۼ�ɾ����10�У� �ٶȼӿ�20ms����һ�� 
		tetris->speed-=20;
		tetris->level++; 
	} 
} 
void Flag(struct Tetris *tetris)
{
	tetris->number++;//��ס��������ĸ���
	/*srand������������������ĳ�ʼ��������ԭ�ͣ�void srand(unsigned int seed);srand��rand()���ʹ�ò���α��������С�
	srand()����λ��time.hͷ�ļ����� 
	*/	
	srand(time(NULL));//��ʼ�������

	if(tetris->number==1)
	{
		tetris->flag = (rand()%19)+1;//��ס��һ���������� 
	} 
	 tetris->next=rand()%19+1;//��ס��һ���������� 
		
} 

  

  






