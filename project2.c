#include <stdio.h> 
#include <stdlib.h>
#include "Util.h"
#include "project2.h"
#include "firstFit.h"

FILE* script;
void printargs(int argc, char**argv);
long len;

int main(int argc, char**argv){
	//check argument validity
	//try opening file
	if(argc!=4){puts("invalid argument count");
		printUsageString();
		printargs(argc,argv);
		return 1;
	}
	else if (strcmp(argv[1],"BESTFIT")!=0&&
			strcmp(argv[1],"FIRSTFIT")!=0&&
			strcmp(argv[1],"NEXTFIT")!=0&&
			strcmp(argv[1],"BUDDY")!=0){
		puts("invalid argument");
		printUsageString();
		printargs(argc,argv);
		return 1;
	}
	script = freopen(argv[3],"r",stdin);
	if (!script){
		puts("file not found");
		printUsageString();
		printargs(argc,argv);
		return 1;
	}
	else if (!(len = strtol(argv[2],NULL,10))){
		puts("invalid size");
		puts(argv[2]);
		printUsageString();
		printargs(argc,argv);
		return 1;
	}

	char*outArgs[2]={argv[0],argv[3]};
	//open the relevant source file based on the users choice
	if(!strcmp(argv[1],"FIRSTFIT")) return(firstFit(2,outArgs));
	//error, execution should never reach here
	puts("not implemented");
	return(1);

}
void printUsageString(){
	puts("usage: \"./project2 [BESTFIT|FIRSTFIT|NEXTFIT|BUDDY|");
	puts(" N ${file}.txt");
}
void printargs(int argc, char**argv){
	for(int i = 0; i < argc; i++){
		puts(argv[i]);
	}
}
