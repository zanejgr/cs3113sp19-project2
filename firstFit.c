#include"firstFit.h"
//global for helper functions
extern long len;
extern char**allocations;
int firstFit(int argc, char*argv[]){
	len = strtol(argv[1],NULL,0);

	//allow array of allocation labels to be used by helpr functions
	allocations = calloc(len,sizeof(char*));
	for(int i = 0; i < len; i++)
		allocations[i]=calloc(17,sizeof(char));

	char command[64];
	strncpy(command,"",64);//well above the length of any valid command
	char* buf=NULL;
	size_t bufsize = 64;
	ssize_t numRead =getline(&buf,&bufsize,stdin);
	while(numRead>0){
		if(buf){
			strncpy(command,buf,numRead);
			//strip relic of getline, if present
			for(int i = 0; i < bufsize; i++)
				if(command[i]=='\n') command[i]='\0';
			char* nextToken = strtok(command," ");
			//execute the relevant function
			if(nextToken){
				if(command[0]=='#'){
				}
				else if(!strcmp(nextToken,"REQUEST")){
					nextToken= strtok(NULL," ");
					if(!nextToken||strlen(nextToken)<=0||strlen(nextToken)>16) {
						usage();
					}else{
						char* nextNext = strtok(NULL," ");
						if(nextToken&&nextNext){
							long l = strtol(nextNext,NULL,0);
							if(l>0)	requestFirstFit(nextToken,l);
						}
						else{
							puts("something's really wrong here");
							return(1);
						}
					}
				}
				else if(!strcmp(nextToken,"RELEASE")){
					nextToken= strtok(NULL," ");
					if(!nextToken||strlen(nextToken)<=0||strlen(nextToken)>16) {
						usage();
					}else
						releaseFirstFit(nextToken);
				}
				else if(!strcmp(nextToken,"LIST")){
					nextToken = strtok(NULL," ");
					if(nextToken&&strlen(nextToken)>=0&&strlen(nextToken)<16) {
						if(!strcmp(nextToken,"AVAILABLE")){
							availableFirstFit();
						}
						else if(!strcmp(nextToken,"ASSIGNED")){
							assignedFirstFit();
						}
					}
					else{
						usage();
					}
				}
				else if(!strcmp(nextToken,"FIND")){
					nextToken = strtok(NULL," ");
					if(!nextToken||strlen(nextToken)<=0||strlen(nextToken)>16) {
						usage();
					}else
						findFirstFit(nextToken);
				}
				else{ 
					usage();
				}
			}
		}
		strncpy(command,"",64);
		if(buf) free(buf);
		buf=NULL;
		numRead = getline(&buf,&bufsize,stdin);
	}
	return(0);
}

void requestFirstFit(char* name,long size){
	if(name==NULL || sizeof name == 0 || name[0]=='\0' || strlen(name)>16){
		printf("FAIL REQUEST %.16s %ld",name,size);
		return;
	}
	long unallocated = 0;
	size_t blockStartIndex=0;	
	for(long i = 0; i < len;i++){
		if(!strcmp("",allocations[i]))
			unallocated++;
		else{
			blockStartIndex = i+1;
			unallocated = 0;
		}
		if(unallocated>=size){
			while(unallocated-->0){
				strncpy(allocations[blockStartIndex++],name,16);	
			}
			printf("ALLOCATED %.16s %ld",name,size);
			return;
		}
	}
	printf("FAIL REQUEST %.16s %ld",name,size);
}
void releaseFirstFit(char* name){
	if(name==NULL || name[0]=='\0' || strlen(name)>16){
		printf("FAIL RELEASE %.16s",name);
		return;
	}
	long deallocated = 0;
	for(long i = 0; i < len;i++){
		if(!strcmp(allocations[i],name)){
			strncpy(allocations[i],"",16);
			deallocated++;
		}
	}

	if(deallocated>0) printf("FREE %.16s %ld",name,deallocated);
	else printf("FAIL RELEASE %.16s",name);
}

void availableFirstFit(){
	long index = 0;
	long size = 0;
	int full = 1;//becomes 0 if any empty block is found
	for(long i = 0; i < len;i++){
		if(!strcmp(allocations[i],"")) {
			full = 0;
			size++;
		}
		else if(size>0){
			printf("(%ld, %ld)",index,size);
			size = 0;
			index = i+ 1;
		}else{
			size = 0;
			index = i+1;
		}
	}
	if(full){//if the allocation table has no free memory
		puts("FULL");
	}
	else if(size>=0){//if the allocations end in a process
		printf("(%ld, %ld)",index,size);
	}//otherwise, nothing left to print
	return;
}
void assignedFirstFit(){
	long index = 0;
	long size = 1;
	int empty = 1;//becomes 0 if any allocated block is found
	for(long i = 0; i <len-1;i++){
		int iUnallocated = 0;//flag for unallocated block index
		if(!strcmp(allocations[i],"")){
			size = 1;
			iUnallocated = 1;	
		}
		else empty = 0;
		//if the block after this has the same process(or lack thereof)
		if(!strcmp(allocations[i],allocations[i+1])){
			if(iUnallocated) index = i+1;
			else size++;
		}else if(!iUnallocated){
			printf("(%ld, %ld) ",index,size);
			size = 1;
			index = i+1;
		}
	}
	//if an allocation reaches the end
	if(0!=strcmp(allocations[len-1],"")){
		printf("(%ld, %ld)",index,size);
		empty=0;
	}
	else if(empty) puts("NONE");
}
//findFirstFits a process and measures its allocation
void findFirstFit(char* name){
	int found =0;
	long i=-1;
	//exits when is found
	while(!found&&++i<len)	if(!strcmp(allocations[i],name)) found = 1;
	size_t pos = i;
	long blockLen= 0;
	//counts how long it is
	while(i<len){	
		if(!strcmp(allocations[i++],name)) blockLen++;
		else break;
	}
	if(!found) puts("FAULT");
	else printf("(%.16s, %ld, %ld)",name,blockLen,pos);
}
/******************
 * debug functions*
 *****************/
void  printTable(){
	for(long i = 0; i < len; i++){
		puts(allocations[i]);
	}
}

void usage(){
	puts("Valid options are REQUEST A n, RELEASE A, LIST AVAILABLE, LIST ASSIGNED AND FIND");
}
