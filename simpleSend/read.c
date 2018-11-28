#include <mqueue.h>
#include <stdio.h>
#include <string.h>

int main(){
  int i;
  char buff[10];
  struct mq_attr attr= { .mq_maxmsg = 10, .mq_msgsize = 1};
  mqd_t recvq;

  recvq = mq_open("/test", O_RDONLY|O_CREAT, 0644, &attr);
  mq_getattr(recvq, &attr);

  if(-1 == recvq) { puts("open err"); return 0;}

  int c = 0;

  while(1)
  {
    puts("in");
    int prio = 1;
    int r = mq_receive(recvq, buff, attr.mq_msgsize, &prio);
    if(r == -1) {printf("rec err %m\n"); break;}
    printf("%c\n", buff[0]);
    c++;
    if(c > 5) break;
  }

  puts("cloes");
  mq_close(recvq);
  mq_unlink("/test");
  return 0;
}
