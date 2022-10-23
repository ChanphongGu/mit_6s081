#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p1[2], p2[2];
  pipe(p1);
  pipe(p2);
  if(fork()==0)
  {
    char c;
    int n;
    n = read(p1[0], &c, 1);
    if(n==0)
    {
      printf("%d ping failed!\n",getpid());
    }
    else
    {
      printf("%d: received ping\n",getpid());
    }
    write(p2[1], "c\n",2);
    close(p2[1]);
  }
  else
  {
    write(p1[1], "p\n", 2);
    close(p1[1]);
    char c;
    int n;
    n = read(p2[0], &c, 1);
    if(n==0)
    {
      printf("%d pong failed!\n",getpid());
    }
    else
    {
      printf("%d: received pong\n",getpid());
    }
    
  }
  exit(0);
}