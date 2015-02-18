#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >������ */
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
  
  printf("�����С���IP�����Ϥ��Ʋ�������");
  scanf("%s", ip);
  printf("�����С��Υݡ����ֹ�����Ϥ��Ʋ�����");
  scanf("%d", &port);
    
  /*
   *  �����åȤ��롣���Υ����åȤ�INET�ɥᥤ��ǡ����ȥ꡼�෿�����åȡ�
   */
  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    return 1;
  }
  
  /* 
   * addr����Ȥ�0�ˤ��Ƥ����ʤ��ȡ�bind()�ǥ��顼�������뤳�Ȥ�����
   */
  bzero((char *)&addr, sizeof(addr));
  
  /*
   * �����åȤ�̾��������Ƥ���
   */
  
  
  if ((hp = gethostbyname(ip)) == NULL) {
    perror("No such host");
    return 1;
  }
  bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  
  /*
   *  �����С��Ȥ���³���ߤ롣���줬�������뤿��ˤϡ������С������Ǥ�
   *  ���Υ��ɥ쥹��bind()���ơ�listen()��ȯ�Ԥ��Ƥ��ʤ���Фʤ�ʤ���
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


