#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(void)
{
  int r = 0;
  char name[] = "/test";
  struct mq_attr attr = { .mq_maxmsg = 10, .mq_msgsize = 1};
  mqd_t q = mq_open(name,  O_WRONLY, NULL, &attr);
  if(q == (mqd_t) -1)
  {
    printf("err %m\n");
    return r;
  }
  
  for(int i = 0; i < 10; i++)
  {
    char msg = 'A';
    r = mq_send(q, &msg, 1, 1);

    if(r){printf("send err %m\n"); return 0;}
    
    sleep(1);
  }

  return 0;
}


