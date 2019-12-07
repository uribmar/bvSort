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
  int rf = open(info.filename, O_RDONLY);
  unsigned int* readData = (unsigned int*)malloc(MAX_DATA_SIZE);
  int dataToRead = MAX_DATA_SIZE;
  for(int i = info.tID; i < fileCount; i += 2) {
    //get the file name
    char outputFile[8];
    char fID[3];
    sprintf(fID, "%d", i);
    strcpy(outputFile, TEMP_FILE_PATH);
    strcat(outputFile, fID);
    printf("Thread %d is writing file %s\n", info.tID, outputFile);

    //seek to the proper location
    lseek(rf, MAX_DATA_SIZE*i, SEEK_SET);

    //read in the proper amount of data
    if(i == fileCount-1 && inputFileSize % MAX_DATA_SIZE != 0) {
      dataToRead = inputFileSize % MAX_DATA_SIZE;
    }
    read(rf, readData, dataToRead);

    //open and write to the temp file
    int wf = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    write(wf, readData, dataToRead);
    close(wf);
  }

  free(readData);
  close(rf);
}

int main(int argc, char** argv) {
  if(argc < 3) {
    printf("Need to include an input and output file\n");
    return -1;
  }

  //get the number of temp files and make the directory for it
  countFiles(argv[1]);
  mkdir(TEMP_FILE_PATH, 0777);

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

  //delete the files then delete the directory
  for(int i=0; i<fileCount; i++) {
    char outputFile[8];
    char fID[3];
    sprintf(fID, "%d", i);
    strcpy(outputFile, TEMP_FILE_PATH);
    strcat(outputFile, fID);
    unlink(outputFile);
  }
  rmdir(TEMP_FILE_PATH);

  //TODO open input file
  //TODO sort the sumbitch
  //TODO write to output file
  return 0;
}
