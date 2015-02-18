#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >������ */
#include <netdb.h>
#include <termio.h>


#define GUARD  1
#define MAX_GUARD_COUNT 2
#define DOWN   3
#define MUTEKI 4
#define GOAL  50

int turn;           //ï�Υ�����
int field[100];     //�ޥå�
int player_count;   //�ץ쥤�䡼��
struct player PLAYER1;
struct player PLAYER2;
struct player PLAYER3;

struct player{
  int dice;         //�Ф�����
  int stop;         //�٤ߥ�����
  int chara;        //���ѥ����
  int money;        //�Ķ�
  int status;       //�ɸ椫�٤ߤ�
  int position;     //field��ΰ���
  int guard_count;  //�ĥ����ɲ��
} ;

void setting();     //�ץ쥤�䡼��
void init();        //���ѿ�����������
void set();         //���ѿ����������
void print();       //����ɽ��
void play_dice();   //���������򿶤롦������
void advance();     //��ư��ȿ��(�ޥ��ΰ�ư)
void stamp();       //Ƨ��
void effect();      //�ޥ��ܤθ���ȯư
void next_turn();   //���Υץ쥤�䡼�Υ������
void goal_check();  //advance effect ����


main(void)
{
  setting();
  init();
  set();

  print();
  play_dice();

  return 0;
}


void setting()      //�ץ쥤�䡼�ο�
{
  /*�������ϤΤ�*/
  while(player_count == 0){
    printf("�ץ쥤�䡼�������� : ");
    scanf("%d",&player_count);
    if(player_count<1 | player_count>9){
      player_count = 0;
      printf("���Ϥ˴ְ㤤������ޤ�\n\n");
    }
  }
}

void init()         //���ѿ������
{
  srand((unsigned)time(NULL));
}

void set()          //���ѿ������������
{
  turn = rand()%player_count+1;
  //field= ;
}

void print()        //����ɽ��
{
  printf("PLAYER%d�Υ�����Ǥ�\n",turn);
  PLAYER(turn).position = 0;
}

void play_dice()    //���������򿶤롦������
{
  int number=0;
  number = rand()%6+1;
  printf("dice : %d\n",number);
  //PLAYER? -> dice = number;
}

void advance()      //��ư��ȿ��(�ޥ��ΰ�ư)
{
}