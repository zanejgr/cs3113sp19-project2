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
typedef struct Allocation{
	char[16] name;//empty means fragment of memory
	int pos;
	int size;
} Allocation;
typedef struct Request{
	char[16] name;//must not be empty
	int size;
}
//uses function pointers for polymorphism
typedef struct BuddySystem{
	Node top;//can be a buddy, or an allocation
	long available;
	extern int (*request)(char*, int);
	extern int (*release)(char*);
	extern Allocation*(*listAvailable)(); 
	extern Allocation*(*listAllocated)(); 
	extern char*(*find)(char*);
} BuddySystem;
typedef struct BestFit{
	int[] table;//holds positions
	long available;//holds current available memory, including segmented pieces

	extern int (*request)(char*, int);
	extern int (*release)(char*);
	extern Allocation*(*listAvailable)(); 
	extern Allocation*(*listAllocated)(); 
	extern char*(*find)(char*);
} BestFit;
typedef struct FirstFit{
	int[] table;//holds positions
	long available;//holds current available memory, including segmented pieces

	extern int (*request)(char*, int);
	extern int (*release)(char*);
	extern Allocation*(*listAvailable)(); 
	extern Allocation*(*listAllocated)(); 
	extern Allocation(*find)(char*);
} FirstFit;
typedef struct NextFit{
	int[] table;//holds positions
	long available;//holds current available memory, including segmented pieces

	int index;//for circle-queue structure

	extern int (*request)(char*, int);
	extern int (*release)(char*);
	extern Allocation*(*listAvailable)(); 
	extern Allocation*(*listAllocated)(); 
	extern Allocation(*find)(char*);
} NextFit;
