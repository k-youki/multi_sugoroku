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
struct player PLAYER1;
struct player PLAYER2;
struct player PLAYER3;

struct player{
  int dice;         //出した目
  int stop;         //休みターン
  int chara;        //使用キャラ
  int money;        //残金
  int status;       //防御か休みか
  int position;     //field上の位置
  int guard_count;  //残ガード回数
} ;

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


main(void)
{
  setting();
  init();
  set();

  print();
  play_dice();

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
  turn = rand()%player_count+1;
  //field= ;
}

void print()        //画面表示
{
  printf("PLAYER%dのターンです\n",turn);
  PLAYER(turn).position = 0;
}

void play_dice()    //サイコロを振る・ガード
{
  int number=0;
  number = rand()%6+1;
  printf("dice : %d\n",number);
  //PLAYER? -> dice = number;
}

void advance()      //行動の反映(マスの移動)
{
}
