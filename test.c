#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cache.h"

// TESTING FUNCTIONS //

void testing_create_queue(){
	int failed = 0;
	queue_t q = create_queue();
	int size = q->queue_size;
	if(size!=0){
		printf("Initializing queue size failed\n");
		++failed;
	}
	if (q->head!=NULL){
		printf("NULL on head failed\n");
		++failed;
	} 
	if (q->tail!=NULL){
		printf("NULL on tail failed\n");
		++failed;
	}
	if (failed==0) printf("Testing create_queue() successful\n");
	else printf("Testing create_queue() failed\n");
	destroy_queue(q);
	q = NULL;
}

void testing_queue_add(){
	int failed = 0;
	queue_t q = create_queue();
	queue_add(q,0);
	if(q->head->index != 0 ||
		q->tail != NULL ||
		q->head->prev != NULL ||
		q->head->next != NULL ||
		q->queue_size != 1){
			printf("Test failed on initalizing first element");
			++failed;
	}

	for(int i = 1;i<10;++i){
		queue_add(q,i);
		if(q->head->index != i ||
			q->tail->index != 0 ||
			q->head->prev != NULL ||
			q->tail->next != NULL ||
			q->queue_size != i+1){
				printf("Test failed on initalizing element %d\n",i);
				++failed;
		}
	}
	if (failed==0) printf("Testing add_queue() successful\n");
	else printf("Testing add_queue() failed\n");
	destroy_queue(q);
	q = NULL;
}

void testing_queue_update(){
	int failed = 0;
	queue_t q = create_queue();
	for(int i = 0;i<10;++i){
		queue_add(q,i);
	}
	queue_update(q,q->head);
	if(q->head->index != 9 ||
		q->head->next->index!=8||
		q->tail->index != 0 ||
		q->head->prev != NULL ||
		q->tail->next != NULL ||
		q->queue_size != 10){
		printf("Test failed on updating first element\n");
	}

	for(int i = 8;i>0;--i){
		node_t n = q->head->next;
		for(int j = 8-i;j>0;--j){
			n = n->next;
		}
		queue_update(q,n);
		if(q->head->index != i ||
			q->head->next->index != i+1||
			q->tail->index != 0 ||
			q->head->prev != NULL ||
			q->tail->next != NULL ||
			q->queue_size != 10){
				printf("head %d",q->head->index);
				printf("tail %d",q->tail->index);
				printf("size %d",q->queue_size);
				printf("Test failed on updating element %d\n",i);
				++failed;
		}
	}

	queue_update(q,q->tail);
	if(q->head->index != 0 ||
		q->head->next->index != 1 ||
		q->tail->index != 9 ||
		q->head->prev != NULL ||
		q->tail->next != NULL ||
		q->queue_size != 10){
			printf("head %d",q->head->index);
		printf("tail %d",q->tail->prev->index);
			printf("tailprev %d",q->tail->index);
			printf("size %d\n",q->queue_size);
			printf("Test failed on updating last element\n");
			++failed;
	}
	if (failed==0) printf("Testing queue_update() successful\n");
	else printf("Testing queue_update() failed\n");
	destroy_queue(q);
	q = NULL;
}

void testing_queue_delete(){
	int failed = 0;
	queue_t q = create_queue();
	for(int i = 0;i<10;++i){
		queue_add(q,i);
	}
	//[9,8,7,6,5,4,3,2,1,0]
	for(int i = 0;i<=5;++i){
		node_t n = q->head;
		for(int j=0;j<i;++j){
			n = n->next;
		}
		queue_update(q,n);
	}
	//[3,4,5,6,7,8,9,2,1,0]
	for(int i = 0;i<=3;++i){
		node_t n = q->tail->prev->prev->prev;
		queue_update(q,n);
	}
	//[7,8,9,3,4,5,6,2,1,0]
	for(int i = 0;i<2;++i){
		queue_delete(q,q->tail);
		if (q->head->index!= 7 ||
			q->tail->index!= i+1 ||
			q->queue_size != 9-i){
				printf("%d\n",i);
				printf("head %d",q->head->index);
				printf("tail %d",q->tail->index);
				printf("size %d",q->queue_size);
				printf("Test failed on deleting element from end\n");
				++failed;
		}
	}
	queue_delete(q,q->tail);
	for(int i = 3;i<6;++i){
		queue_delete(q,q->head->next->next->next);
		if (q->head->index!= 7 ||
			q->tail->index!= 6 ||
			q->queue_size != 9-i){
				printf("head %d",q->head->index);
				printf("tail %d",q->tail->index);
				printf("size %d\n",q->queue_size);
				printf("Test failed on deleting element from middle\n");
				++failed;
		}
	}
	for(int i = 7;i<9;++i){
		queue_delete(q,q->head);
		if (q->head->index!= i+1 ||
			q->tail->index!= 6 ||
			q->queue_size != 10-i){
				printf("head %d",q->head->index);
				printf("tail %d",q->tail->index);
				printf("size %d\n",q->queue_size);
				printf("Test failed on deleting element from head\n");
				++failed;
		}
	}
	queue_delete(q,q->head);
	queue_delete(q,q->tail);
	queue_t a = q;
	for(int i = 0;i<10;++i){
		queue_add(q,i);
	}
	for(int i = 0;i<10;++i){
		queue_delete(q,q->head);
	}
	if (q!=a){
		printf("Test failed on clearing a queue\n");
		++failed;
	}

	if (failed==0) printf("Testing queue_delete() successful\n");
	else printf("Testing update_delete() failed\n");

	destroy_queue(q);
	q=NULL;
}

// void testing_hashfunc(hash_func func,key_type key,uint64_t expected){
// 	printf("Testing (*hash_func):\n");
// 	uint64_t testout = (func)(key);
// 	if (testout == expected) printf("Test succesful\n");
// 	else printf("Test failed on input %s",key);
// }

void testing_create_cache(){
	int failed = 0;
	cache_t c = create_cache(100,NULL);

	char * current = "checking maxmemory";
	if(c->maxmemory!=100){
		printf("Test failed on: %s\n",current);
		++failed;
	}
	current = "checking number of buckets";
	if(c->buckets!=10){
		printf("Test failed on: %s\n",current);
		++failed;
	}
	current = "checking number of occupied buckets";
	if (c->occupied!=0){
		printf("Test failed on: %s\n",current);
		++failed;
	} 
	if (failed==0) printf("Testing create_cache() successful\n");
	else printf("Testing create_cache() failed\n");

	destroy_cache(c);

	c = NULL;
}

void testing_cache_set(){
	int failed = 0;
	cache_t c = create_cache(100,NULL);
	char * current = "setting first element (str)";
	cache_set(c,(key_type)"1",(val_type)"val1",5);
	if(strcmp(c->keyvals[(c->hashf)((key_type)"1")%(c->buckets)].val,"val1")!=0 ||
		c->eviction->head->index != 7 ||
		c->eviction->tail != NULL ||
		c->eviction->head != c->keyvals[7].node ||
		c->occupied != 1){
		printf("Test failed on: %s\n",current);
		printf("%s\n",c->keyvals[(c->hashf)((key_type)"1")%(c->buckets)].val);
		printf("%d\n",c->eviction->head->index);
		++failed;
	}

	current = "setting second element (int)";
	int a = 2;
	int * ap = &a;
	cache_set(c,(key_type)"22",(val_type)ap,sizeof(ap));
	if( *(int*)c->keyvals[(c->hashf)((key_type)"22")%(c->buckets)].val != 2 ||
		c->eviction->head->index!=4 ||
		c->eviction->tail->index!=7 ||
		c->occupied != 2){
		printf("Test failed on: %s\n",current);
		printf("%d\n",*(int*)c->keyvals[(c->hashf)((key_type)"22")%(c->buckets)].val);
		printf("%d\n",c->eviction->head->index );
		++failed;
	}

	current = "resetting a value in the cache";
	cache_set(c,(key_type)"1",(val_type)"33",3);
	if( strcmp(c->keyvals[(c->hashf)((key_type)"1")%(c->buckets)].val,"33")!=0 ||
		c->eviction->head->index != 7 ||
		c->eviction->tail->index != 4 ||
		c->occupied != 2){
		printf("Test failed on: %s\n",current);
		printf("%s\n",c->keyvals[(c->hashf)((key_type)"1")%(c->buckets)].val);
		printf("%d\n",c->eviction->head->index);
		++failed;
	}

	current = "overloading the cache's load factor";
	cache_set(c,(key_type)"3",(val_type)"val3",5);
	cache_set(c,(key_type)"4",(val_type)"val4",5);
	cache_set(c,(key_type)"5",(val_type)"val5",5);
	cache_set(c,(key_type)"6",(val_type)"val6",5);
	if( c->eviction->head->index != 17 ||
		c->eviction->head->next->index != 0 ||
		c->eviction->head->next->next->index != 9 ||
		c->eviction->head->next->next->next->index != 8 ||
		c->eviction->tail->prev->index != 7 ||
		c->eviction->tail->index != 4 ||
		c->occupied != 6 ||
		c->buckets != 20){
		printf("Test failed on: %s\n",current);
		printf("%d\n",c->eviction->head->index);
		printf("%d\n",c->eviction->head->next->index);
		printf("%d\n",c->eviction->head->next->next->index);
		printf("%d\n",c->eviction->head->next->next->next->index);
		printf("%d\n",c->eviction->tail->prev->index);
		printf("%d\n",c->eviction->tail->index);
		++failed;
	}

	current = "overloading the cache's maxmem";
	cache_set(c,(key_type)"7",(val_type)"123456789012345678901234567890\
		123456789012345678901234567890123456789012345678901234567890",91);
	if( c->eviction->head->index != 18 ||
		c->eviction->head->next->index != 17 ||
		c->eviction->tail->index != 17 ||
		c->occupied != 2 ||
		c->buckets != 20){
		printf("Test failed on: %s\n",current);
		printf("%d\n",c->eviction->head->index);
		printf("%d\n",c->eviction->tail->index);
		++failed;
	}
	
	if (failed==0) printf("Testing cache_set() successful\n");
	else printf("Testing cache_set() failed\n");
	destroy_cache(c);
	c = NULL;
}

void testing_cache_get(){
	int failed = 0;
	cache_t c = create_cache(100,NULL);

	char * current = "getting a val from an empty cache";
	uint8_t a[5];

	if(cache_get(c,(key_type)"1")!=NULL){
		printf("Test failed on: %s\n",current);
		++failed;
	}

	current = "getting a val from cache w/ one element";
	cache_set(c,(key_type)"1",(val_type)"val1",5);
	strcpy(a,cache_get(c,(key_type)"1"));
	if(strcmp(a,"val1")!=0){
		printf("Test failed on: %s\n",current);
		++failed;
	}

	cache_set(c,(key_type)"2",(val_type)"val2",5);
	cache_set(c,(key_type)"3",(val_type)"val3",5);
	cache_set(c,(key_type)"4",(val_type)"val4",5);
	cache_set(c,(key_type)"5",(val_type)"val5",5);

	current = "getting an old val from cache w/ multiple elements";
	strcpy(a,cache_get(c,(key_type)"1"));
	if(strcmp(a,"val1")!=0){
		printf("Test failed on: %s\n",current);
		++failed;
	}

	current = "getting a val from cache w/ multiple elements";
	strcpy(a,cache_get(c,(key_type)"3"));
	if(strcmp(a,"val3")!=0){
		printf("Test failed on: %s\n",current);
		++failed;
	}

	cache_set(c,(key_type)"6",(val_type)"val6",5);
	current = "getting a new val from cache after resize";
	strcpy(a,cache_get(c,(key_type)"6"));
	if(strcmp(a,"val6")!=0){
		printf("Test failed on: %s\n",current);
		++failed;
	}

	cache_set(c,(key_type)"2",(val_type)"val6",5);
	current = "getting an old val from cache after resize";
	strcpy(a,cache_get(c,(key_type)"2"));
	if(strcmp(a,"val6")!=0){
		printf("Test failed on: %s\n",current);
		++failed;
	}

	int x = 2;
	int * xp = &x;
	cache_set(c,(key_type)"7",(val_type)xp,sizeof(x));
	cache_set(c,(key_type)"6",(val_type)"val6",5);
	current = "getting a new val (int) from cache after resize";
	int * p = cache_get(c,(key_type)"7");
	if(*p != x){
		printf("%d",*p);
		printf("Test failed on: %s\n",current);
		++failed;
	}
	
	if (failed==0) printf("Testing cache_get() successful\n");
	else printf("Testing cache_get() failed\n");
	destroy_cache(c);
}

void testing_cache_delete(){
	int failed = 0;
	cache_t c = create_cache(100,NULL);

	char * current = "deleting a val empty cache";
	cache_delete(c,(key_type)"1");
	for(int i=0;i<c->buckets;++i){
		if(c->keyvals[i].key!=NULL||
			c->keyvals[i].val!=NULL){
		printf("Test failed on: %s\n",current);
		++failed;
		}
	}
	cache_set(c,(key_type)"1",(val_type)"val1",5);
	cache_set(c,(key_type)"2",(val_type)"val2",5);
	cache_set(c,(key_type)"3",(val_type)"val3",5);
	cache_set(c,(key_type)"4",(val_type)"val4",5);
	cache_set(c,(key_type)"5",(val_type)"val5",5);

	current = "deleting the first inserted val in a cache of multiple elements";
	cache_delete(c,(key_type)"1");
	if(cache_get(c,(key_type)"1")!=NULL){
		printf("Test failed on: %s\n",current);
		++failed;
	}

	current = "deleting the last inserted val in a cache of multiple elements";
	cache_delete(c,(key_type)"5");
	if(cache_get(c,(key_type)"1")!=NULL){
		printf("Test failed on: %s\n",current);
		++failed;
	}

	current = "deleting a val from a resized (by overload) cache";
	cache_set(c,(key_type)"1",(val_type)"val1",5);
	cache_set(c,(key_type)"5",(val_type)"val5",5);
	cache_set(c,(key_type)"6",(val_type)"val6",5);
	cache_delete(c,(key_type)"6");
	if(cache_get(c,(key_type)"6")!=NULL||
		c->buckets != 20){
		printf("%llu\n",c->buckets);
		printf("Test failed on: %s\n",current);
		++failed;
	}
	current = "automatic deletion from maxmemory overload";
	cache_set(c,(key_type)"7",(val_type)"123456789012345678901234567890\
		123456789012345678901234567890123456789012345678901234567890",91);
	//everything except for this and the most recent element in queue
	//should be evicted because of the memory overload. currently
	//the most recent element is under the key "5".
	if(cache_get(c,(key_type)"1")!=NULL||
		c->eviction->head->index!=17 ||
		c->buckets != 20 ||
		c->occupied != 2){
		printf("%d\n",c->eviction->head->index);
		printf("%d\n",c->eviction->tail->index);
		printf("%llu\n",c->buckets);
		printf("%llu\n",c->occupied);
		printf("Test failed on: %s\n",current);
		++failed;
	}

	if (failed==0) printf("Testing cache_delete() successful\n");
	else printf("Testing cache_delete() failed\n");
	destroy_cache(c);
}

void testing_cache_space_used(){
	int failed = 0;
	cache_t c = create_cache(100,NULL);

	char * current = "memory used by empty cache";
	uint64_t size = cache_space_used(c);
	if(size!=0){
		printf("Test failed on: %s\n",current);
		++failed;
	}

	current = "memory used by empty cache after deleting a (nonexistant)";
	cache_delete(c,(key_type)"1");
	size = cache_space_used(c);
	if(size!=0){
		printf("Test failed on: %s\n",current);
		++failed;
	}

	current = "memory used after inserting str \"val1\" (size 5)";
	cache_set(c,(key_type)"1",(val_type)"val1",5);
	size = cache_space_used(c);
	if(size!=5){
		printf("%llu\n",size);
		printf("Test failed on: %s\n",current);
		++failed;
	}
	current = "memory used after deleting str \"val1\" (size 5)";
	cache_delete(c,(key_type)"1");
	size = cache_space_used(c);
	if(size!=0){
		printf("%llu\n",size);
		printf("Test failed on: %s\n",current);
		++failed;
	}

	current = "memory used after inserting 5 elements of size 5";
	cache_set(c,(key_type)"1",(val_type)"val1",5);
	cache_set(c,(key_type)"2",(val_type)"val2",5);
	cache_set(c,(key_type)"3",(val_type)"val3",5);
	cache_set(c,(key_type)"4",(val_type)"val4",5);
	cache_set(c,(key_type)"5",(val_type)"val5",5);
	size = cache_space_used(c);
	if(size!=25){
		printf("%llu\n",size);
		printf("Test failed on: %s\n",current);
		++failed;
	}
	current = "memory used after resize (by overload)";
	cache_set(c,(key_type)"6",(val_type)"val6",5);
	size = cache_space_used(c);
	if(size!=30){
		printf("%llu\n",size);
		printf("Test failed on: %s\n",current);
		++failed;
	}
	current = "memory used by deleting a val from \
	a resized (by overload) cache";	
	cache_delete(c,(key_type)"6");
	size = cache_space_used(c);
	if(size!=25){
		printf("%llu\n",size);
		printf("Test failed on: %s\n",current);
		++failed;
	}
	current = "memory used after maxmemory overload and one automatic \
	deleting from LRU eviction";
	cache_set(c,(key_type)"7",(val_type)"123456789012345678901234567890\
		12345678901234567890123456789012345",76);
	size = cache_space_used(c);
	if(size!=96 ||
		c->occupied != 5){
		printf("%llu\n",size);
		printf("%llu\n", c->occupied);
		printf("Test failed on: %s\n",current);
		++failed;
	}

	current = "memory used after maxmemory overload and several automatic \
	deletions from LRU eviction";
	cache_set(c,(key_type)"7",(val_type)"123456789012345678901234567890",31);
	size = cache_space_used(c);
	if(size!=31 ||
		c->occupied != 1){
		printf("%llu\n",size);
		printf("%llu\n", c->occupied);
		printf("Test failed on: %s\n",current);
		++failed;
	}

	if (failed==0) printf("Testing cache_space_used() successful\n");
	else printf("Testing cache_space_used() failed\n");
	destroy_cache(c);
}
