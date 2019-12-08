#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char** argv) {
  if(argc < 2) {
    printf("Marco, you're fucking stupid\n");
    return -1;
  }

  int fd = open(argv[1], O_CREAT | O_RDWR | O_EXCL, 0644);

  if (fd < 0) {
    if (errno == EEXIST) {
      printf("dELETE THE FILE YOU FUCKING DONKEY\n");
      return -1;
    }
  }

  int num;
 //for(int i=0; i<1024*1024*1024; i++) {
 //  num = rand() % 1000;
 //  write(fd, &num, sizeof(int));
 //}
  for(int i=1024*1024*100; i>0; i--) {
    write(fd, &i, sizeof(int));
  }

  close(fd);
  return 0;
}
