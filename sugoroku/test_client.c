#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >の代わり */
#include <netdb.h>

#define PORT1 11111
#define PORT2 22222

int fd;

int iclient(void)
{
  struct sockaddr_in addr;
  struct hostent *hp;
  int    len;
  char   buf[1024];
  int    ret;
  unsigned char ip[50];
  int port;
  
  printf("サーバーのIPを入力して下さい．");
  scanf("%s", ip);
  printf("サーバーのポート番号を入力して下さい");
  scanf("%d", &port);
    
  /*
   *  ソケットを作る。このソケットはINETドメインで、ストリーム型ソケット。
   */
  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    return 1;
  }
  
  /* 
   * addrの中身を0にしておかないと、bind()でエラーが起こることがある
   */
  bzero((char *)&addr, sizeof(addr));
  
  /*
   * ソケットの名前を入れておく
   */
  
  
  if ((hp = gethostbyname(ip)) == NULL) {
    perror("No such host");
    return 1;
  }
  bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  
  /*
   *  サーバーとの接続を試みる。これが成功するためには、サーバーがすでに
   *  このアドレスをbind()して、listen()を発行していなければならない。
   */
  if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
    perror("connect");
    return 1;
  }
  
  return 0;
}

int main(void)
{
  char buffer[256];
  char *dummy = 0;

  iclient();

  while(1){
    //fgets(buffer,256,stdin);
    read(fd, buffer, 256, 0);
    printf("%s\n", buffer);
    //sleep(1000);
    //send(fd, dummy, 1024, 0);
    //write(fd, dummy, 1024);
  }
}


