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
	int val ;
	char first = fgetc(stdin) ;
	while(1)
	{
		switch(first)
		{
			case 'i' :
				scanf("nsert %d" , &val) ;
				insert(d , val) ;
				break ;
			case 's' :
				first = getchar() ;
				if(first == 'e')
					/*do search */ ;
				else
					status(d) ;
				break ;
			case 'd' :
				/*do delete*/ ;
				break ;
			case EOF :
				exit(0) ;
		}
		first = fgetc(stdin) ;
	}
	return 0 ;
}
