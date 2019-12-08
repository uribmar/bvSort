#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char** argv) {
  if(argc < 2)
    return -1;
  else {
    int fd = open(argv[1], O_RDONLY);
    unsigned int last = 0;
    unsigned int curr;
    long count = 0;
    while(read(fd, &curr, sizeof(unsigned int)) != 0) {
      if(!(last <= curr)) {
        printf(" Number %ld: %u is not less than %u\n", count, last, curr);
      }
      last = curr;
      count++;
    }
  }
}
