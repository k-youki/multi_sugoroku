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
  setting();
  init();
  set();

  while(1){
    print();
    if(player.status != DOWN){
      play_dice();
      if(++turn > player_count)
	turn = 0;
    }
  }
  
  return 0;
}


void setting()      //プレイヤーの数
{
  /*数字入力のみ*/
  while(player_count == 0){
    printf("プレイヤー数を入力 : ");
    scanf("%d",&player_count);
    if(player_count<1 | player_count>9){
      player_count = 0;
      printf("入力に間違いがあります\n\n");
    }
  }
}

void init()         //各変数　定義
{
  srand((unsigned)time(NULL));
}

void set()          //各変数　初期値代入
{
  turn = 0;
  //field= ;
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
