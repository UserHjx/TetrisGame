#include <stdio.h> //��׼��������������� 
#include <stdlib.h> //
#include <windows.h> //����DOS����(��ȡ����̨�ϵ�����λ�á�����������ɫ)
#include <conio.h> //���ռ��̵���������(Kbhit(),getch())
#include <time.h> //���ڻ������� 

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
  void welcom();//��ӭ����
  void Replay(struct Tetris * tetris);//���¿�ʼ��Ϸ
  void title();//��ӭ�����Ϸ��ı���
  void flower();//��ӭ�����ϵ��ַ�װ�λ�
  void close();//�ر���Ϸ 
   
int main() {
	printf("����˹����\n"); 
	return 0;
}

