#include "helpers.h"

//number of files that we have created
long inputFileSize;
int fileCount = 0;


//calculate number of temp files that need to be created based on input file size
void countFiles(char* filename) {
  int f = open(filename, O_RDONLY);
  inputFileSize = lseek(f, 0L, SEEK_END);

  printf("Size of input file: %ld bytes\n", inputFileSize);

  //int divide it into chunks of 250MB
  fileCount = inputFileSize / MAX_DATA_SIZE;
  if( (inputFileSize%MAX_DATA_SIZE) != 0) {
    fileCount++;
  }
}


//makes all of the temp files that are needed for the sort
void* makeFiles(void* arg) {
  threadInfo info = *(threadInfo*)arg;
  printf("I'm thread number %d and the file is named %s\n",
         info.tID, info.filename);
  /*
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
  */
}

int main(int argc, char** argv) {
  if(argc < 3) {
    printf("Need to include an input and output file\n");
    return -1;
  }

  countFiles(argv[1]);

  //initialize threads to make files
  pthread_t tID[NUM_CORES];
  threadInfo info[NUM_CORES];
  for(int i=0; i<NUM_CORES; i++) {
    info[i].filename = argv[1];
    info[i].tID = i;
    pthread_create(tID+i, 0, makeFiles, info+i);
  }

  //join threads
  for(int i=0; i<NUM_CORES; i++) {
    pthread_join(tID[i], NULL);
  }

  //TODO open input file
  //TODO sort the sumbitch
  //TODO write to output file
  return 0;
}
