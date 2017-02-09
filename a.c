#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "utils.c"
#include "hash.c"

int main(int argc , char* argv[])
{	
	initial_gd = atoi(argv[1]) ;
	bucket_size = atoi(argv[2]) ;
	dir* d = create_directory(initial_gd) ;
	int t = insert(d , 8) ;
	printf("Inserted %d in %d\n", 8 , t);
	status(d) ;
	t = insert(d , 16) ;
	printf("Inserted %d in %d\n", 16 , t);
	status(d) ;
	t = insert(d , 4) ;
	printf("Inserted %d in %d\n", 4 , t);
	status(d) ;
	t = insert(d , 9) ;
	printf("Inserted %d in %d\n", 9 , t);
	status(d) ;
	t = insert(d , 17) ;
	printf("Inserted %d in %d\n", 17 , t);
	status(d) ;
	t = insert(d , 5) ;
	printf("Inserted %d in %d\n", 5 , t);
	status(d) ;
	return 0 ;
}
