/*
Alex Pan - HW 3
cache.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cache.h"

uint64_t defaulthash(key_type input){
	uint64_t out = 17*strlen((const char *)input);
	return out;
}

// Create a new cache object with a given maximum memory capacity
// and a hash function.
cache_t create_cache(uint64_t maxmem,hash_func hash){
	cache_t cache = malloc(sizeof(struct cache_obj));
	if (NULL == cache){
		printf("malloc failed for create_cache");
		return NULL;
	}
	
	cache->maxmemory = maxmem;
	cache->buckets = 10;
	cache->occupied = 0;


	if(hash == NULL){
		cache->hashf = defaulthash;
	}
	else cache->hashf = hash;

	cache->keyvals = calloc(maxmem,sizeof(struct cache_keyval));

	cache->eviction = create_queue();
	return cache; 
}

// Add a <key, value> pair to the cache.
// If key already exists, it will overwrite the old value.
// If maxmem capacity is exceeded, sufficient values will be removed
// from the cache to accomodate the new value.
void cache_set(cache_t cache, key_type key, val_type val, uint32_t val_size)
{
	if (val_size > cache->maxmemory){
		printf("Object is too large for cache\n");
		return;
	}
	int max = 0;
	int64_t index;
	double load = (double)(cache->occupied+1.0)/(double)cache->buckets;
	if(load>0.5){
		cache->buckets = cache->buckets*2;
		cache->keyvals = 
			realloc(cache->keyvals,sizeof(struct cache_keyval)*cache->buckets);
	}

	int lru;
	uint64_t usedmem = cache_space_used(cache)+val_size;
	while(usedmem>cache->maxmemory){
		if (cache->eviction->tail == NULL) lru = cache->eviction->head->index;
		else (lru = cache->eviction->tail->index);
		cache_delete(cache,cache->keyvals[lru].key);
		usedmem = cache_space_used(cache)+val_size;
	}
	// linear probing
	while (max < cache->buckets){
		index = (cache->hashf(key) + max) % cache->buckets;
		if (cache->keyvals[index].key == NULL){	
			cache->keyvals[index].key = malloc(sizeof(key_type));
			strcpy(cache->keyvals[index].key,key);
			cache->keyvals[index].val = malloc(val_size);
			memcpy(cache->keyvals[index].val,val,val_size);
			cache->occupied = cache->occupied + 1;
			cache->keyvals[index].size = val_size;
			queue_add(cache->eviction,index);
			cache->keyvals[index].node = cache->eviction->head;
			break;
		}
		else if (strcmp(cache->keyvals[index].key,key)==0){
			cache->keyvals[index].val = realloc(cache->keyvals[index].val,val_size);
			memcpy(cache->keyvals[index].val,val,val_size);
			queue_update(cache->eviction,cache->keyvals[index].node);
			break;
		}
		else max ++;
	}
}


// Retrieve the value associated with key in the cache, or NULL if not found.
// The size of the returned buffer will be assigned to *val_size.
val_type cache_get(cache_t cache, key_type key){
	int max = 0;
	int64_t index;
	if (cache==NULL){
		printf("Error: Cache is NULL");
		return NULL;
	} 
	if (cache->occupied==0) return NULL;
	// linear probing
	while (max < cache->buckets){
		index = (cache->hashf(key) + max) % cache->buckets;
		if (cache->keyvals[index].key!=NULL){
			if (strcmp(cache->keyvals[index].key,key)==0){
				return cache->keyvals[index].val;
			}
		}
		max++;
	}
	return NULL;
}


// Delete an object from the cache, if it's still there
void cache_delete(cache_t cache, key_type key){
	int max = 0;
	int64_t index;
	// linear probing
	while (max < cache->buckets){
		index = (cache->hashf(key) + max) % cache->buckets;
		if (cache->keyvals[index].key!=NULL){
			if (strcmp(cache->keyvals[index].key,key)==0){
				free(cache->keyvals[index].key);
				free(cache->keyvals[index].val);
				cache->keyvals[index].key = NULL;
				cache->keyvals[index].val = NULL;
				cache->keyvals[index].size = 0;
				queue_delete(cache->eviction,cache->keyvals[index].node);
				cache->keyvals[index].node = NULL;
				cache->occupied = cache->occupied -1;	
				return;
			}
		}
		++max;
	}
}


// Compute the total amount of memory used up by all cache values (not keys)
uint64_t cache_space_used(cache_t cache){
	uint64_t total = 0;
	int j = 0;
	for(;j<cache->buckets;++j){
		if (cache->keyvals[j].key!=NULL)
			total = total + cache->keyvals[j].size;
	}
	return total;
}


// Destroy all resource connected to a cache object
void destroy_cache(cache_t cache){
	for(int i = 0;i < cache->buckets;++i){
		free(cache->keyvals[i].key);
		free(cache->keyvals[i].val);
	}
	free(cache->keyvals);
	cache->keyvals = NULL;

	destroy_queue(cache->eviction);

	free(cache);
	cache=NULL;

}

int main(){
	//////////////////////////////// testing queue //////////////////////////////
	printf("Testing queue:\n");
	testing_create_queue();
	testing_queue_add();
	testing_queue_update();
	testing_queue_delete();
	printf("\n\n");

	//////////////////////////////// testing cache //////////////////////////////
	printf("Testing cache:\n");
	testing_create_cache();
	testing_cache_set();
	testing_cache_get();
	testing_cache_delete();
	testing_cache_space_used();
	printf("\n\n");

	return 0;
}