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
    close(0);
    dup(p1[0]);
    close(p1[0]);
    close(p1[1]);
    char c;
    int n;
    n = read(0, &c, 1);
    if(n==0)
    {
      printf("%d ping failed!\n",getpid());
    }
    else
    {
      printf("%d: received ping\n",getpid());
    }
    close(1);
    dup(p2[1]);
    close(p2[0]);
    close(p2[1]);
    write(1, "c\n",2);
    close(1);
  }
  else
  {
    dup(1);
    close(1);
    dup(p1[1]);
    close(p1[0]);
    close(p1[1]);
    write(1, "p\n", 2);
    close(1);
    dup(2);
    close(2);
    close(0);
    dup(p2[0]);
    close(p2[0]);
    close(p2[1]);
    char c;
    int n;
    n = read(0, &c, 1);
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