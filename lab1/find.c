#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void
findallfile(char *filename, char *path)
{
  int fd;
  struct stat st;
  struct dirent de;
  char buf[512];
  char *p;
  if((fd = open(path, 0)) < 0)
  {
    printf("find: cannot open %s\n", path);
    return;
  }
  //printf("path:%s filename:%s\n", path, filename);
  strcpy(buf, path);
  p = buf + strlen(path);
  *p++ = '/';
  while(read(fd, &de, sizeof(de)) == sizeof(de))
  {
    if(de.inum == 0 || strcmp(".", de.name) == 0 || strcmp("..", de.name) == 0) continue;
    memmove(p, de.name, DIRSIZ);
    if((stat(buf, &st)) < 0)
    {
      printf("find: cannot stat %s\n", buf);
    }
    switch(st.type)
    {
    case T_FILE:
      if((strcmp(de.name, filename)) == 0)
      {
        printf("%s\n", buf);
      }
      break;
    case T_DIR:
      findallfile(filename, buf);
      break;
    }
  }
}

int
main(int argc, char* argv[])
{
  if(argc<2 || strcmp(".", argv[1])) exit(1);
  //printf("this is main,filename:%s\n", argv[2]);
  findallfile(argv[2], ".");
  exit(0);  
}