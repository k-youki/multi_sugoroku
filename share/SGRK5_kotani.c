#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >の代わり */
#include <netdb.h>
#include <termio.h>
#include <ncurses.h>


#define GUARD  1
#define MAX_GUARD_COUNT 2
#define DOWN   3
#define MUTEKI 4
#define GOAL  50

int turn;           //誰のターンか
int field[100];     //マップ
int player_count;   //プレイヤー数

struct player{
  int dice;         //出した目
  int stop;         //休みターン
  int chara;        //使用キャラ
  int money;        //残金
  int status;       //防御か休みか
  int position;     //field上の位置
  int guard_count;  //残ガード回数
}player[3];

void title();
void setting();     //プレイヤー数
void init();        //各変数初期化・定義
void set();         //各変数初期値代入
void print();       //画面表示
void play_dice();   //サイコロを振る・ガード
void advance();     //行動の反映(マスの移動)
void stamp();       //踏む
void effect();      //マス目の効果発動
void next_turn();   //次のプレイヤーのターンへ
void goal_check();  //advance effect から

int main(void)
{
  initscr();	// 端末制御の開始

  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  
  start_color();	// カラーの設定
  init_pair(1, COLOR_RED, COLOR_BLUE);	// 色番号１を赤文字／青地とする
  bkgd(COLOR_PAIR(1));			// 色１をデフォルト色とする
  
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
  
  endwin();	// 端末制御の終了
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

void setting()      //プレイヤーの数
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

void init()         //各変数　定義
{
  srand((unsigned)time(NULL));
}

void set()          //各変数　初期値代入
{
  turn = 0;
}

void print()        //画面表示
{
  printf("PLAYER%dのターンです\n",turn);
  player[turn].position = 0;
  
  switch(player[turn].status){
  case DOWN:
    printf("あなたはダウン中です\n");
    break;
  default:
    break;
  }
}

void play_dice()    //サイコロを振る・ガード
{
  int number = 0;

  number = rand()%6+1;
  printf("dice : %d\n",number);
  player[turn].dice = number;
}

void advance()      //行動の反映(マスの移動)
{
}
