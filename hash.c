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
			bucket* new = create_bucket(dst -> local_depth + 1) ;
			d -> buckets[new_id] = new ;//repeated code
			if(new_id + pow_2(new -> local_depth) < pow_2(d -> global_depth))
				d -> buckets[new_id + pow_2(new -> local_depth)] = new ;
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