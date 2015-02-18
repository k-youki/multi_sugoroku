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
#include <ncurses.h>


#define GUARD  1
#define MAX_GUARD_COUNT 2
#define DOWN   3
#define MUTEKI 4
#define GOAL  50

int turn;           //ï�Υ�����
int field[100];     //�ޥå�
int player_count;   //�ץ쥤�䡼��

struct player{
  int dice;         //�Ф�����
  int stop;         //�٤ߥ�����
  int chara;        //���ѥ����
  int money;        //�Ķ�
  int status;       //�ɸ椫�٤ߤ�
  int position;     //field��ΰ���
  int guard_count;  //�ĥ����ɲ��
}player[3];

void title();
void setting();     //�ץ쥤�䡼��
void init();        //���ѿ�����������
void set();         //���ѿ����������
void print();       //����ɽ��
void play_dice();   //��������򿶤롦������
void advance();     //��ư��ȿ��(�ޥ��ΰ�ư)
void stamp();       //Ƨ��
void effect();      //�ޥ��ܤθ���ȯư
void next_turn();   //���Υץ쥤�䡼�Υ������
void goal_check();  //advance effect ����

int main(void)
{
  initscr();	// ü������γ���

  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  
  start_color();	// ���顼������
  init_pair(1, COLOR_RED, COLOR_BLUE);	// ���ֹ棱����ʸ�������ϤȤ���
  bkgd(COLOR_PAIR(1));			// ������ǥե���ȿ��Ȥ���
  
  title();
  setting();
  init();
  set();
  
  while(1){
    print();
    if(player[turn].status != DOWN){
      play_dice();
      if(++turn > player_count)
	turn = 0;
    }
    }*/
  
  endwin();	// ü������ν�λ
  return 0;
}

void title()
{
  erase();
  move(10, 20);
  addstr("Sugoroku Game!!");
  move(15, 15);
  addstr("Please enter any key");
  refresh();
  
  timeout(-1);
  getch();
}

void setting()      //�ץ쥤�䡼�ο�
{
  int num = 0;
  int key;
  
  while (1) {
    erase();
    move(12, 20);
    addstr("Num of player : ");
    mvprintw(12, 36, "%d", num+2);
    
    key = getch();
    if (key == 'q') 
      break;
    switch (key) {
    case KEY_UP:
      num = (num+1)%3; 
      break;
    case KEY_DOWN:
      num = num-1;
      if(num < 0)
	num = 2;
      break;
    }
    
    refresh();
  }
}

void init()         //���ѿ������
{
  srand((unsigned)time(NULL));
}

void set()          //���ѿ������������
{
  turn = 0;
}

void print()        //����ɽ��
{
  printf("PLAYER%d�Υ�����Ǥ�\n",turn);
  player[turn].position = 0;
  
  switch(player[turn].status){
  case DOWN:
    printf("���ʤ��ϥ�������Ǥ�\n");
    break;
  default:
    break;
  }
}

void play_dice()    //��������򿶤롦������
{
  int number = 0;

  number = rand()%6+1;
  printf("dice : %d\n",number);
  player[turn].dice = number;
}

void advance()      //��ư��ȿ��(�ޥ��ΰ�ư)
{
}
