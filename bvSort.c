#include "helpers.h"

//number of files that we have created
int fileCount = 0;

//makes all of the temp files that are needed for the sort
void makeFiles(char* filename) {
  //file decriptor for the file we will read in the data to be sorted from
  int rf = open(filename, O_RDONLY);

  int* data = (int*)malloc(MAX_DATA_SIZE);
  int dataCounter;

  while(1) {
    //read in (up to) 250MB of ints from rf
    dataCounter = read(rf, data, sizeof(int)*MAX_DATA_SIZE);
    if(dataCounter == 0) {
      break;
    }
    else {
      fileCount++;
    }

    //FIXME should probably put these in their own directory at some point in time
    char outputFilename[8];
    sprintf(outputFilename, "%d", fileCount);

    //open the file
    int wf = open(outputFilename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    //write all of those ints and close the file
    for(int i=0; i<dataCounter/4; i++) {
      write(wf, data+i, sizeof(int));
    }

    close(wf);
  }

  free(data);
  close(rf);
}

int main(int argc, char** argv) {
  if(argc < 3) {
    printf("Need to include an input and output file\n");
    return -1;
  }

  makeFiles(argv[1]);

  //TODO open input file
  //TODO sort the sumbitch
  //TODO write to output file
  return 0;
}
