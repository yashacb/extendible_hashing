#define LAZY 0
#define MERGE_BUCKETS 1
#define COMPRESS_DIRECTORY 2

int initial_gd ;
int bucket_size ;
int delete_type ;

typedef struct bucket
{
	int local_depth ;
	int count ; // number of elements currently in the bucket .
	int *list ;
}bucket ;

typedef struct dir
{
	int global_depth ;
	bucket** buckets ;

}dir ;