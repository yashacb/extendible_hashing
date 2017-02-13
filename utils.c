extern int bucket_size ;

int pow_2(int n)
{
	if(n == 1)
		return 2 ;
	else 
	{
		int res = pow_2(n / 2) ;
		if(n % 2 == 0)
			return res * res ;
		return res * res * 2 ;
	}
}

int extract_bits(int x , int n) // extracts last n bits from x
{
	return x & ~((~0) << n) ;
}

bucket* create_bucket(int local_depth)
{
	bucket* n = (bucket*) malloc(sizeof (bucket)) ;
	n -> local_depth = local_depth ;
	n -> count = 0 ;
	n -> list = (int*) malloc(bucket_size * sizeof(int)) ;
	return n ;
}

dir* create_directory(int global_depth) 
{
	dir* d = (dir*) malloc(sizeof(dir)) ;
	d -> global_depth = global_depth ;
	int i = 0 , num_entries = pow_2(global_depth) ;
	d -> buckets = (bucket**) malloc(num_entries * sizeof(bucket*)) ;
	for( ; i < num_entries ; i++)
		d -> buckets[i] = create_bucket(global_depth) ;
	return d ;
}

int hash_function(int x)
{
	// implementation of hash function . Currently , it is identity .
	return x ;
}

void wbptw(dir* d)//which bucket points to what
{
	printf("---------------------------------------------------\n");
	int i = 0 , num_dir = pow_2(d -> global_depth) ;
	for( ; i < num_dir ; i++)
	{
		printf("Directory entry %3d maps to bucket %3d . Address : %x\n", i , extract_bits(i , d -> buckets[i] -> local_depth) , 
			(unsigned int)(d -> buckets[i]));
	}
	printf("---------------------------------------------------\n");
}