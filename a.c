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
	delete_type = atoi(argv[3]) ;
	dir* d = create_directory(initial_gd) ;
	int val ;
	char first = fgetc(stdin) ;
	while(1)
	{
		switch(first)
		{
			case 'i' :
				scanf("nsert %d\n" , &val) ;
				int add = insert(d , val) ;
				printf("Inserted %d into bucket %d\n", val , add);
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
						printf("%d found in bucket %d .\n", val , found);
				}
				else
				{
					scanf("atus\n") ;
					status(d) ;
				}
				break ;
			case 'd' :
				scanf("elete %d" , &val) ;
				int found = delete(d , val) ;
				if(found == -1)
					printf("%d not found .\n" , val) ;
				else
					printf("%d deleted from bucket %d .\n", val , found);
				break ;
			case 'm' :
				scanf("apping") ;
				wbptw(d) ;
				break ;
			case EOF :
				exit(0) ;
		}
		first = fgetc(stdin) ;
	}	return 0 ;
}
