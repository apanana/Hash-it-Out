# Hash-it-Out
Implementation of a cache with a LRU eviction policy in C

## Introduction
### Overview:
  * `readme.md`: the current file you are reading
  * `lru.h`: header-file for a doubly-linked list (a user provided struct that is necessary for our cache API)
  * `lru.c`: implementation of a doubly-linked list
  * `cache.h`: header file of the cache (our API)
  * `cache.c`: implementation of the cache
  * `test.c`: tests for the doubly-linked list and cache implementations  
  * `Makefile`: the makefile that links our files and creates an executable.

### To run:
  * `make`: creates object files
  * `./test.out`: runs both the cache and linked list tests
  * `make clean`: removes object files


## Implementation
### Collision Resolution:
The scheme I used for collision resolution was linear probing. The cache is created with a default hash function of h(k)=k%17. Obviously this is by far not the greatest of hash functions ever conceived, but the assumption is that the user can provide a better one and that the default function is simply there to make sure the cache works.

### Eviction Policy:
A LRU eviction policy was implemented by holding the indices of the all the occupied slots in the hash table inside of a doubly linked list. The list acts as a queue, so that anytime an action is performed on an entry in the hash table (ie. adding a new entry or altering a pre-existing entries value), the node containing the respective index of that entry is placed on the front of the queue. If the entry already exists, it is moved from its location to the front (so we don't end up with multiple copies of nodes referring to the same hash table slot). If an entry is removed from the hash table, it is removed from the queue.
