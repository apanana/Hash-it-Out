# Hash-it-Out
#### Alex Pan - HW3
Implementation of a cache with a LRU eviction policy in C

## Introduction
### Overview:
  * `readme.md`: the current file you are reading
  * `lru.h`: header-file for a doubly-linked list (a user provided struct that is necessary for the cache API)
  * `lru.c`: implementation of a doubly-linked list
  * `cache.h`: header file of the cache (the API)
  * `cache.c`: implementation of the cache
  * `test.c`: tests for the doubly-linked list and cache implementations  
  * `Makefile`: the makefile that links these files and creates an executable.

### To run:
  * `make`: creates object files
  * `./test.out`: runs both the cache and linked list tests
  * `make clean`: removes object files


## Implementation
### Collision Resolution:
The scheme I used for collision resolution was linear probing. The cache is created with a default hash function of h(k)=k%17. Obviously this is by far not the greatest of hash functions ever conceived, but the assumption is that the user can provide a better one and that the default function is simply there to make sure the cache works.

### Eviction Policy:
A LRU eviction policy was implemented by holding the indices of the all the occupied slots in the hash table inside of a doubly linked list. The list acts as a queue, so that anytime an action is performed on an entry in the hash table (ie. adding a new entry or altering a pre-existing entries value), the node containing the respective index of that entry is placed on the front of the queue. If the entry already exists, it is moved from its location to the front (so we don't end up with multiple copies of nodes referring to the same hash table slot). If an entry is removed from the hash table, it is removed from the queue.

### Performance:
####Queue
In the struct for my queue, I have pointers to the start and end nodes of a doubly-linked list. This allows quick access to the ends of the list, which is where we will be putting new elements, moving updated elements, and looking for information when doing evictions. Within the doubly-linked list implementation there are three main functions that affect the list: adding, updating, and deleting. Adding new elements is in constant time because we simply stick them on the front of the queue. Updating elements is kept in constant time because the function takes both a list and a pointer to a node in the list, so that we simply need to check for a few edge cases (all of which keep the runtime within O(1)) before moving it this node to the front. Similarly, deletions are kept in constant time because having a pointer to the node we want to delete means we don't have to iterate through the list to find it, and instead we can just immediately delete it after figuring out which case it falls under.
####Cache
To improve the expected runtimes of my functions, every entry in the hash table contains a key, a val, and a pointer to the entry's respective node in the queue (if it has one). There are two main functions in the cache: adding and removing. We expect adding key-val pairs to be constant time (which also relies on the user giving the cache a good hash function). In the case where we have to evict existing entries to make space for a new one, we reference the end of the queue to find the index of the LRU slot and evict the element in that slot. When deleting elements, the expected runtime is also constant (assuming the cache has a good hash function).

### Testing:
#### test.c
The `test.c` file contains tests for both the doubly-linked list and the cache implementations. Running the makefile creates an executable that runs the tests. There is more documentation of the specific cases that each test runs over in `test.c` and the testing functions will raise flags if any errors occur.

#### Valgrind
Valgrind was run on the executable to check for memory leaks and errors. This was absolutely brutal to debug because I was leaking tens of thousands of bytes and I raised a few thousand errors on the first run. Currently the tests raise 0 memory leaks and 0 errors from Valgrind.

