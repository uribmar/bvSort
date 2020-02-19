# bvSort
A multithreaded program to sort files of unsigned, four byte integers when the file is too large to fit into RAM. The program breaks the file up into several 250MB-sized temporary files and then performs a merge on those temporary files to sort the data. Included in this repository are the following files:

## bvSort.c
The file to compile. When compiling, please make sure to include the -lpthread flag. When running this code, please make sure to specify an input file and an output file.

Running this code will create a temporary directory to store the temporary files that the program creates in. When the code is ran to completion, the temporary directory should be automatically removed.

## helpers.h
A file containing all of the odds and ends needed to run bvSort.c. Here is where global variables such as the maximum data size for a file to be live. The file also contains the struct used to create new threads and a comparator that is used to sort data subsets.

## dataGen.c
A program that is made to be compiled and executed to create a file of unsigned integers. Currently, the file is set to write a ~1GB file. Please make sure that a filename is specified in the command line argument and that the filename specified does not currently exist in the directory.

## dataChecker.c
A program that simply reads in data from a specified file and lists any errors in order in the file.
