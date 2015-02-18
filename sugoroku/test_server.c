#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >の代わり */
#include <netdb.h>

#define PORT1 11111
#define PORT2 22222

int iserver(int pp, int port)
{
    int    i;
    int    fd1;
    struct sockaddr_in saddr;
    struct sockaddr_in caddr;
    int    len;
    int    ret;
    char   buf[1024];
    
    /*
     * ソケットを作る。このソケットはUNIXドメインで、ストリーム型ソケット。
     */
    if ((fd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      perror("socket");
      return(1);
    }
    
    /* 
     * saddrの中身を0にしておかないと、bind()でエラーが起こることがある
     */
    bzero((char *)&saddr, sizeof(saddr));
    
    /*
     * ソケットの名前を入れておく
     */
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(port);
    
    /*
     * ソケットにアドレスをバインドする。
     */
    if (bind(fd1, (struct sockaddr *)&saddr, sizeof(saddr)) < 0){
      perror("bind");
      return(1);
    }
    
    /*
     * listenをソケットに対して発行する
     */
    if (listen(fd1, 1) < 0) {
      perror("listen");
      return(1);
    }
    
    len = sizeof(caddr);
    /*
     * accept()により、クライアントからの接続要求を受け付ける。
     * 成功すると、クライアントと接続されたソケットのディスクリプタが
     * fd2に返される。このfd2を通して通信が可能となる。
     * fd1は必要なくなるので、close()で閉じる。
     */
    if ((pp = accept(fd1, (struct sockaddr *)&caddr, &len)) < 0) {
      perror("accept");
      return(1);
    }
    close(fd1);

    return 0;
}

int main(void)
{
  int i = 0;
  char buffer[256];
  char *dummy = 0;
  
  int pp1,pp2;
 

  printf("クライアント接続待ち\n");
  iserver(pp1,PORT1);
  printf("クライアント1人目接続\n");
  strcpy(buffer,"あなたは1人目のクライアントです\n");
  write(pp1, buffer, strlen(buffer)+1);
  iserver(pp2,PORT2);
  printf("クライアント2人目接続\n");
  strcpy(buffer,"あなたは2人目のクライアントです\n");
  write(pp2, buffer, strlen(buffer)+1);
  
  while(1){  
    //fgets(buffer,256,stdin);
    scanf("%s",buffer);
    write(pp1, buffer, strlen(buffer)+1);
    //write(pp2, buffer, strlen(buffer)+1);
    //read(fd2, dummy, 1024, 0);
  }
}
