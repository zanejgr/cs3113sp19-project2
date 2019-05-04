#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define _POSIX_C_SOURCE 200809L
//user interaction functions
void requestFirstFit(char* name,long size);
void releaseFirstFit(char* name);
void availableFirstFit();
void assignedFirstFit();
void findFirstFit(char* name);
//utility and debugging
void usage();
void printTable();
//global for helper functions
long len;
char**allocations;
int firstFit(int argc, char**argv);
