//help from Weiss, chapter 4 section 2
//helper function prototypes
void printUsageString();
//data structures
//for buddy system
typedef struct Node{
	int size;
	void* left;//these can be allocations or another node
	void* right;
} Node;
