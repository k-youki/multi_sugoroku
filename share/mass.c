/*
 1.1�ʤ�
 2.2�ʤ�
 3.3�ʤ�
 4.4�ʤ�
 5.5�ʤ�
 6.6�ʤ�
 7.1���
 8.2���
 9.3���
10.4���
11.5���
12.6���
13.�������Ȥ����
14.1��٤�
15.2��٤�
16.���Υ�����οͤȾ���
17.���Υ�����οͤȾ���
18.���Υ�����ο�1��٤�
19.���Υ�����ο�1��٤�
20.Nʬ�ʤ�
21.Nʬ���
22.������¿����
23.���������̡�
24.�����ʾ��ʤ���
25.�����¿����
26.��������̡�
27.����ʾ��ʤ���
*/
//alt w ctrl��y ���ԥ�


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >������ */
#include <netdb.h>

#define GUARD 0
#define DOWN  1
#define MAX_GUARD_COUNT 2
#define MUTEKI 3
#define GOAL  50
//���⡡
#define MANY  10000
#define NORMAL 5000
#define FEW    3000
#define LITTLE 1000
#define FIELD 100

int turn;           //ï�Υ�����
int field[100];     //�ޥå�
int player_count;   //�ץ쥤�䡼��

typedef struct {
  int dice;         //�Ф�����
  int stop;         //�٤ߥ�����
  int chara;        //���ѥ����
  int money;        //kane!
  int status;       //�ɸ椫�٤ߤ�
  int position;     //field��ΰ���
  int guard_count;  //�ĥ����ɲ��

} PLAYER;

void advance_one();
void advance_two();
void advance_three();
void advance_four();
void advance_five();
void advance_six();
void return_one();
void return_two();
void return_three();
void return_four();
void return_five();
void return_six();
void return_start();
void rest_one();
void rest_two();
void change_next();
void change_front();
void rest_next();
void rest_front();
void advance_N();
void return_N();
void revenue_many();
void revenue_normal();
void revenue_little();
void cost_many();
void cost_normal();
void cost_little();

int main(void){

  PLAYER player[player_count];

  return 0;
}
void advance_one(PLAYER player[])   //1�ʤ�
{
  player[turn].position=player[turn].position+1;
}
void advance_two(PLAYER player[])   //2�ʤ�
{
    player[turn].position=player[turn].position+2;
}
void advance_three(PLAYER player[])   //3�ʤ�
{
  player[turn].position=player[turn].position+3;
}
void advance_four(PLAYER player[])   //4�ʤ�
{
  player[turn].position=player[turn].position+4;
}
void advance_five(PLAYER player[])   //5�ʤ�
{
  player[turn].position=player[turn].position+5;
}
void advance_six(PLAYER player[])   //6�ʤ�
{
  player[turn].position=player[turn].position+6;
}
void return_one(PLAYER player[])    //1���
{
  player[turn].position=player[turn].position-1;
}
void return_two(PLAYER player[])    //2���
{
  player[turn].position=player[turn].position-2;  
}
void return_three(PLAYER player[])   //3���
{
  player[turn].position=player[turn].position-3;
}
void return_four(PLAYER player[])   //4���
{
  player[turn].position=player[turn].position-4;
}
void return_five(PLAYER player[])   //5���
{   
    player[turn].position=player[turn].position-5;
}
void return_six(PLAYER player[])   //6���
{
  player[turn].position=player[turn].position-6;
}
void return_start(PLAYER player[])   //�������Ȥ����
{
  player[turn].position=field[0];
}
void rest_one(PLAYER player[])   //1��٤�
{
  player[turn].stop=1;
}
void rest_two(PLAYER player[])   //2��٤�
{
  player[turn].stop=2;
}
void change_next(PLAYER player[])   //���Υ�����οͤȾ���
{
  int p,i;
  
  if(turn==player_count){
    i=1;
  }else{
    i=turn+1;
  }

  p=player[turn].position;
  player[turn].position=player[i].position;
  player[i].position=p;
}
void change_front(PLAYER player[])   //���Υ�����οͤȾ���
{
  int p;
  int i=0;
 
  if(turn==1){
    i=player_count;
  }else{
    i=turn-1;
  }
  
  p=player[turn].position;
  player[turn].position=player[i].position;
  player[i].position=p;
}
void rest_next(PLAYER player[])   //���Υ�����ο�1��٤�
{
  int i=0;
  
  if(turn==player_count){
    i=1;
  }else{
    i=turn+1;
  }
  player[i].stop=1;
}
void rest_front(PLAYER player[])   //���Υ�����ο�1��٤�
{
  int i=0;
  
  if(turn==1){
    i=player_count;
  }else{
    i=turn-1;
  }
  player[i].stop=1;
}
void advance_N(PLAYER player[])   //Nʬ�ʤ�
{
  int n=0;

  srand((unsigned)time(NULL));
  n=rand()%10+1;
  player[turn].position=player[turn].position+n;
}
void return_N(PLAYER player[])   //Nʬ��� 
{
  int n=0;

  srand((unsigned)time(NULL));
  n=rand()%10+1;
  player[turn].position=player[turn].position-n;
 
}
void revenue_many(PLAYER player[])   //������¿����
{
  int c=0;
  srand((unsigned)time(NULL));

  c=rand()%(MANY-NORMAL+1)+NORMAL;
  player[turn].money=player[turn].money+c;
}
void revenue_normal(PLAYER player[])   //���������̡�
{
  int c=0;
  srand((unsigned)time(NULL));
  
  c=rand()%(NORMAL-LITTLE+1)+LITTLE;
  player[turn].money=player[turn].money+c;
}
void revenue_little(PLAYER player[])   //�����ʾ��ʤ�����
{
  int c=0;
  srand((unsigned)time(NULL));

  c=rand()%LITTLE+1;
  player[turn].money=player[turn].money+c;
}
void cost_many(PLAYER player[])   //�����¿����
{
  int c=0;
  srand((unsigned)time(NULL));

    c=rand()%(NORMAL-FEW+1)+FEW;
    player[turn].money=player[turn].money-c;
}
void cost_normal(PLAYER player[])   //��������̡�
{
  int c=0;
  srand((unsigned)time(NULL));

  c=rand()%(FEW-LITTLE+1)+LITTLE;
  player[turn].money=player[turn].money-c;
}
void cost_little(PLAYER player[])   //����ʾ��ʤ���
{
  int c=0;
  srand((unsigned)time(NULL));

  c=rand()%LITTLE+1;
  player[turn].money=player[turn].money-c;
}
