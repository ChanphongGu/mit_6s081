#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char *argv[])
{
  if(argc < 2)
  {
    printf("xargs: failed command\n");
  }
  char *command[MAXARG];
  int len = 0;
  for(int i = 1; i<argc; i++)
  {
    command[i-1] = argv[i];
  }
  len = argc - 1;
  while(1)
  {
    char buf[100];
    memset(buf, 0, sizeof(buf));
    gets(buf, sizeof(buf));
    if(buf[0] == 0) break;
    buf[strlen(buf) - 1] = 0;  //将换行去掉
    if(fork() == 0)
    {
      command[len++] = buf;
      exec(argv[1], command);
      exit(1);
    }
    else
    {
      wait(0);
    }

  }
  exit(0);
}