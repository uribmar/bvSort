#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>

//256MB file
int MAX_DATA_SIZE = 268435456;
int MAX_ARR_SIZE = 268435456/(sizeof(unsigned int));
int NUM_CORES = 2;
char* TEMP_FILE_PATH = "temp/";


struct thready {
  char* filename;
  int tID;
} typedef threadInfo;


void printFile(char* filename) {
  int fd = open(filename, O_RDONLY),
      i,
      bytesRead = -1;
  while((bytesRead = read(fd, &i, sizeof(int))) == 4) {
    printf("%d ", i);
  }
  printf("End: %d\n", bytesRead);
}
