#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

void printFile(char* filename) {
  int fd = open(filename, O_RDONLY),
      i,
      bytesRead = -1;
  while((bytesRead = read(fd, &i, sizeof(int))) == 4) {
    printf("%d ", i);
  }
  printf("End: %d\n", bytesRead);
}

//makes all of the temp files that are needed for the sort
void makeFiles(char* filename) {
  int rf = open(filename, O_RDONLY);
  int count = 0,
      bytesRead = -1;

  while(bytesRead != 0) {
    //TODO read in (up to) 250MB of ints from rf

    //TODO get filename (just the current count)

    //TODO open the file

    //TODO write all of those ints and close the file
  }

  close(rf);
}

int main(int argc, char** argv) {
  if(argc < 3) {
    printf("Need to include an input and output file");
    return -1;
  }

  //TODO open input file
  //TODO sort the sumbitch
  //TODO write to output file
  return 0;
}
