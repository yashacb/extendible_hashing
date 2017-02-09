int initial_gd ;
int bucket_size ;

typedef struct bucket
{
	int printed ;
	int local_depth ;
	int count ; // number of elements currently in the bucket .
	int *list ;
}bucket ;

typedef struct dir
{
	int global_depth ;
	bucket** buckets ;

}dir ;