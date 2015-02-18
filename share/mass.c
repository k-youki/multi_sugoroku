/*
 1.1進む
 2.2進む
 3.3進む
 4.4進む
 5.5進む
 6.6進む
 7.1戻る
 8.2戻る
 9.3戻る
10.4戻る
11.5戻る
12.6戻る
13.スタートに戻る
14.1回休み
15.2回休み
16.次のターンの人と場所交換
17.前のターンの人と場所交換
18.次のターンの人1回休み
19.前のターンの人1回休み
20.N分進む
21.N分戻る
22.収入（多い）
23.収入（普通）
24.収入（少ない）
25.出費（多い）
26.出費（普通）
27.出費（少ない）
*/
//alt w ctrl　y コピペ


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >の代わり */
#include <netdb.h>

#define GUARD 0
#define DOWN  1
#define MAX_GUARD_COUNT 2
#define MUTEKI 3
#define GOAL  50
//お金　
#define MANY  10000
#define NORMAL 5000
#define FEW    3000
#define LITTLE 1000
#define FIELD 100

int turn;           //誰のターンか
int field[100];     //マップ
int player_count;   //プレイヤー数

typedef struct {
  int dice;         //出した目
  int stop;         //休みターン
  int chara;        //使用キャラ
  int money;        //kane!
  int status;       //防御か休みか
  int position;     //field上の位置
  int guard_count;  //残ガード回数

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
void advance_one(PLAYER player[])   //1進む
{
  player[turn].position=player[turn].position+1;
}
void advance_two(PLAYER player[])   //2進む
{
    player[turn].position=player[turn].position+2;
}
void advance_three(PLAYER player[])   //3進む
{
  player[turn].position=player[turn].position+3;
}
void advance_four(PLAYER player[])   //4進む
{
  player[turn].position=player[turn].position+4;
}
void advance_five(PLAYER player[])   //5進む
{
  player[turn].position=player[turn].position+5;
}
void advance_six(PLAYER player[])   //6進む
{
  player[turn].position=player[turn].position+6;
}
void return_one(PLAYER player[])    //1戻る
{
  player[turn].position=player[turn].position-1;
}
void return_two(PLAYER player[])    //2戻る
{
  player[turn].position=player[turn].position-2;  
}
void return_three(PLAYER player[])   //3戻る
{
  player[turn].position=player[turn].position-3;
}
void return_four(PLAYER player[])   //4戻る
{
  player[turn].position=player[turn].position-4;
}
void return_five(PLAYER player[])   //5戻る
{   
    player[turn].position=player[turn].position-5;
}
void return_six(PLAYER player[])   //6戻る
{
  player[turn].position=player[turn].position-6;
}
void return_start(PLAYER player[])   //スタートに戻る
{
  player[turn].position=field[0];
}
void rest_one(PLAYER player[])   //1回休む
{
  player[turn].stop=1;
}
void rest_two(PLAYER player[])   //2回休む
{
  player[turn].stop=2;
}
void change_next(PLAYER player[])   //次のターンの人と場所交換
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
void change_front(PLAYER player[])   //前のターンの人と場所交換
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
void rest_next(PLAYER player[])   //次のターンの人1回休み
{
  int i=0;
  
  if(turn==player_count){
    i=1;
  }else{
    i=turn+1;
  }
  player[i].stop=1;
}
void rest_front(PLAYER player[])   //前のターンの人1回休み
{
  int i=0;
  
  if(turn==1){
    i=player_count;
  }else{
    i=turn-1;
  }
  player[i].stop=1;
}
void advance_N(PLAYER player[])   //N分進む
{
  int n=0;

  srand((unsigned)time(NULL));
  n=rand()%10+1;
  player[turn].position=player[turn].position+n;
}
void return_N(PLAYER player[])   //N分戻る 
{
  int n=0;

  srand((unsigned)time(NULL));
  n=rand()%10+1;
  player[turn].position=player[turn].position-n;
 
}
void revenue_many(PLAYER player[])   //収入（多い）
{
  int c=0;
  srand((unsigned)time(NULL));

  c=rand()%(MANY-NORMAL+1)+NORMAL;
  player[turn].money=player[turn].money+c;
}
void revenue_normal(PLAYER player[])   //収入（普通）
{
  int c=0;
  srand((unsigned)time(NULL));
  
  c=rand()%(NORMAL-LITTLE+1)+LITTLE;
  player[turn].money=player[turn].money+c;
}
void revenue_little(PLAYER player[])   //収入（少ない　）
{
  int c=0;
  srand((unsigned)time(NULL));

  c=rand()%LITTLE+1;
  player[turn].money=player[turn].money+c;
}
void cost_many(PLAYER player[])   //出費（多い）
{
  int c=0;
  srand((unsigned)time(NULL));

    c=rand()%(NORMAL-FEW+1)+FEW;
    player[turn].money=player[turn].money-c;
}
void cost_normal(PLAYER player[])   //出費（普通）
{
  int c=0;
  srand((unsigned)time(NULL));

  c=rand()%(FEW-LITTLE+1)+LITTLE;
  player[turn].money=player[turn].money-c;
}
void cost_little(PLAYER player[])   //出費（少ない）
{
  int c=0;
  srand((unsigned)time(NULL));

  c=rand()%LITTLE+1;
  player[turn].money=player[turn].money-c;
}
