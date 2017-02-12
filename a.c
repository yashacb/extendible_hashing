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
				scanf("nsert %d\n" , &val) ;
				insert(d , val) ;
				break ;
			case 's' :
				first = getchar() ;
				if(first == 'e')
				{
					scanf("arch %d\n" , &val) ;
					int found = search(d , val) ;
					if(found == -1)
						printf("%d not found .\n" , val) ;
					else
						printf("%d found in bucket %d\n", val , found);
				}
				else
				{
					scanf("atus\n") ;
					status(d) ;
				}
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
