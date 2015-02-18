#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >������ */
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
     * �����åȤ��롣���Υ����åȤ�UNIX�ɥᥤ��ǡ����ȥ꡼�෿�����åȡ�
     */
    if ((fd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      perror("socket");
      return(1);
    }
    
    /* 
     * saddr����Ȥ�0�ˤ��Ƥ����ʤ��ȡ�bind()�ǥ��顼�������뤳�Ȥ�����
     */
    bzero((char *)&saddr, sizeof(saddr));
    
    /*
     * �����åȤ�̾��������Ƥ���
     */
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(port);
    
    /*
     * �����åȤ˥��ɥ쥹��Х���ɤ��롣
     */
    if (bind(fd1, (struct sockaddr *)&saddr, sizeof(saddr)) < 0){
      perror("bind");
      return(1);
    }
    
    /*
     * listen�򥽥��åȤ��Ф���ȯ�Ԥ���
     */
    if (listen(fd1, 1) < 0) {
      perror("listen");
      return(1);
    }
    
    len = sizeof(caddr);
    /*
     * accept()�ˤ�ꡢ���饤����Ȥ������³�׵������դ��롣
     * ��������ȡ����饤����Ȥ���³���줿�����åȤΥǥ�������ץ���
     * fd2���֤���롣����fd2���̤����̿�����ǽ�Ȥʤ롣
     * fd1��ɬ�פʤ��ʤ�Τǡ�close()���Ĥ��롣
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
 

  printf("���饤�������³�Ԥ�\n");
  iserver(pp1,PORT1);
  printf("���饤�����1������³\n");
  strcpy(buffer,"���ʤ���1���ܤΥ��饤����ȤǤ�\n");
  write(pp1, buffer, strlen(buffer)+1);
  iserver(pp2,PORT2);
  printf("���饤�����2������³\n");
  strcpy(buffer,"���ʤ���2���ܤΥ��饤����ȤǤ�\n");
  write(pp2, buffer, strlen(buffer)+1);
  
  while(1){  
    //fgets(buffer,256,stdin);
    scanf("%s",buffer);
    write(pp1, buffer, strlen(buffer)+1);
    //write(pp2, buffer, strlen(buffer)+1);
    //read(fd2, dummy, 1024, 0);
  }
}
