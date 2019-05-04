# cs3113sp19-project2
=================================================================
|Manual								|
=================================================================
=================================================================
|USAGE: project2 [BESTFIT|FIRSTFIT|NEXTFIT|BUDDY] $n example.txt|
=================================================================
Where n is some power of two between 16 and 1073741824. 
The contents of example.txt should be line-separated.
Each line should be one of the following:
=================================================================
REQUEST A n
RELEASE A 
LIST AVAILABLE
LIST ASSIGNED
FIND A
=================================================================
Where A is an ascii string of length at most 16 characters
indicating the name of the process needing allocation and N is
the number of bytes in need of allocating. 
=================================================================
|BEHAVIOR: 							|
=================================================================
Request will allocate n bytes for a process named A. On success, 
output to stdout "ALLOCATED A x". On failure, output FAIL REQUEST A n.

Release will free memory held by process A. On success, print to stdout
"FREE A, n, x" where n is the amount of memory reclaimed, and x is the 
start address of the memory. On failure, output FAIL REQUEST A n.

List available prints location information for all available memory to stdout.
The information will be space separated tuples of the form (n\_1, x\_1)...
where x\_i is the starting location, and n\_i is the size of the memory.
If none, print "FULL"

List assigned prints location information for all allocated memory to stdout.
The information will be space separated triples of the form (A\_1,n\_1, x\_1)...
where x\_i is the starting location, A is the process label, and n\_i is the size of the memory.

Find locates the starting address and size of the process. On success, a triple of the form (A\_1,n\_1, x\_1)
will be printed to stdout where x\_i is the starting location, A is the process label, and n\_i is the size of the memory.
On failure, print "FAULT"

=================================================================
|Process							|
=================================================================
I started by generating a makefile and building a backbone for the project.

To make the header files, I found a few resources on implementing interfaces in polymorphism-like 
structuring of C code, so that I could use the same switch statement for the 4 structures.
The books I read (in addition to the class texts) were Data Structures and Algorithm Analysis in C
by Mark Allen Weiss, and Object-oriented Programming with ANSI-C. 

Eventually though, due to time-constraints, I just used Sed and vim-substitutions rather than learning the preprocessor enough to implement these.
Because of this, there are a lot of superfluous functions in the header-files. I finally gave up on
trying to learn the function-pointer union pattern recommended by these. 

=================================================================
|implementation							|
=================================================================
I started with the first-fit system, because it seemed the simplest.
All of its functions are reused for the best- and next-fit systems.
The structs for the tree are found in project2.h.
