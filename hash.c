#include "hash.h"

extern int bucket_size ;
extern int hash_function(int x) ;

void status(dir* d)
{
	printf("---------------------------------------------------\n");
	printf("Global depth : %d\n" , d -> global_depth);
	int i = 0 , num_dir = pow_2(d -> global_depth) , j = 0 ;
	int check[num_dir] ;
	memset(check , 0 , num_dir*(sizeof (int))) ;
	for( ; i < num_dir ; i++)
	{
		bucket* cur = d -> buckets[i] ;
		int bid = extract_bits(i , cur -> local_depth) ;
		if(!check[bid])
		{
			printf("Bucket %d : Local depth : %d : ", bid , cur -> local_depth) ;
			for(j = 0 ; j < cur -> count ; j++)
				printf("%d ", cur -> list[j]) ;
			printf("\n") ;
			check[bid] = 1 ;
		}
	}
	printf("---------------------------------------------------\n");
}

void double_dir(dir* d , int overflow)
{
	int num_entries = pow_2(d -> global_depth) ;
	d -> buckets = (bucket**) realloc(d -> buckets , 
		2*num_entries*(sizeof (bucket*))) ;
	int i = num_entries ;
	bucket* of_bucket = d -> buckets[overflow] ;
	for( ; i < 2*num_entries ; i++)
	{
		if(i - num_entries == overflow)
			d -> buckets[i] = create_bucket(of_bucket -> local_depth + 1) ;
		else
			d -> buckets[i] = d -> buckets[i - num_entries] ;
	}
	of_bucket -> local_depth++ ;
	d -> global_depth++ ;
	int copy[bucket_size] ;
	memcpy(copy , of_bucket -> list , bucket_size*(sizeof (int))) ;
	of_bucket -> count = 0 ;
	for(i = 0 ; i < bucket_size ; i++)
		insert(d , copy[i]) ;
}

int insert(dir* d , int n)
{
	int hash = extract_bits(hash_function(n) , d -> global_depth) , i ;
	bucket* dst = d -> buckets[hash] ;
	if(dst -> count != bucket_size)		
	{
		dst -> list[dst -> count++] = n ;
		return hash ;
	}
	else
	{
		if(dst -> local_depth == d -> global_depth)
		{
			double_dir(d , hash) ;
			return insert(d , n) ;
		}
		else
		{			
			int new_id = extract_bits(hash , dst -> local_depth) + pow_2(dst -> local_depth) ;
			int i = new_id ;
			bucket* new = create_bucket(dst -> local_depth + 1) ;
			d -> buckets[new_id] = new ;//repeated code
			for( ; i < pow_2(d -> global_depth) ; i++)
				if(extract_bits(i , new -> local_depth) == new_id)
					d -> buckets[i] = new ;
			int t = extract_bits(hash , dst -> local_depth) + pow_2(dst -> local_depth) ;
			dst -> local_depth++ ;//repeated code
			int copy[bucket_size] ;//repeated code
			memcpy(copy , dst -> list , bucket_size*(sizeof (int))) ;//repeated code
			dst -> count = 0 ;//repeated code
			for(i = 0 ; i < bucket_size ; i++)//repeated code
				insert(d , copy[i]) ;			//repeated code
			return insert(d , n) ;
		}
	}
}

int search(dir* d , int val)
{
	int hash = extract_bits(hash_function(val) , d -> global_depth) , i = 0 ;
	bucket* b = d -> buckets[hash] ;
	for(i = 0 ; i < b -> count ; i++)
	{
		if(b -> list[i] == val)
			return hash ;
	}
	return -1 ;
}

int lazy_delete(dir* d , int val)
{
	int bid = search(d , val) ;
	if(bid == -1)
		return -1 ;
	bucket* cur = d -> buckets[bid] ;
	int i = 0 ; 
	for( ; i < cur -> count ; i++)
		if(cur -> list[i] == val)
			break ;
	if(cur -> count == 1)
		cur -> count-- ;
	else
	{
		cur -> list[i] = cur -> list[cur -> count - 1] ;
		cur -> count-- ;
	}
	return bid ;
}

int mirror(dir* d , int of)
{
	bucket* cur = d -> buckets[of] ;
	int offset = pow_2(cur -> local_depth - 1) ;
	if(of - offset >= 0)
		return of - offset ;
	return of + offset ;
}

int merge_buckets(dir* d , int val)
{
	int i = 0 , bid = lazy_delete(d , val) ;
	int num_dir = pow_2(d -> global_depth) ;
	bucket* cur = d -> buckets[bid] ;
	if(cur -> count == 0)
	{
		//Point all the buckets which point to bid to the bucket to which bid is being merged with.
		int num_dir = pow_2(d -> global_depth) ;
		int merge_to = mirror(d , bid) ;
		d -> buckets[bid] = d -> buckets[merge_to] ;
		int i = 0 ;
		for( ; i < num_dir ; i++)
		{
			if(extract_bits(i , cur -> local_depth) == bid)
				d -> buckets[i] = d -> buckets[merge_to] ;
		}
		d -> buckets[bid] -> local_depth-- ;
		free(cur) ;
	}
	return bid ;
}

int delete(dir* d , int val)
{
	switch(delete_type)
	{
		case LAZY :
			return lazy_delete(d , val) ;
			break ;
		case MERGE_BUCKETS :
			return merge_buckets(d , val) ;
	}
}