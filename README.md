# Hash-it-Out
#### Alex Pan - HW3
Implementation of a cache with a LRU eviction policy in C

## Introduction
### File Overview:
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
### Some assumptions:
So in theory I'd expect a user to provide their own structs and methods for the eviction policy that can be modified or replaced relatively easily in the cache implementation. Looking at my code right now, I can see there are names that I could modify to make this more easy for the user of an actual API as well as some notes that I would certainly be including, both in a readme like this and in the headers. In terms of functionality though, I think the setup now still gets the job done.

### Collision Resolution:
The scheme I used for collision resolution was linear probing. The cache is created with a default hash function of h(k)=k%17. Obviously this is by far not the greatest of hash functions ever conceived, but the assumption is that the user can provide a better one and that the default function is simply there to make sure the cache works.

### Eviction Policy:
A LRU eviction policy was implemented by holding the indices of the all the occupied slots in the hash table inside of a doubly linked list. The list acts as a queue, so that anytime an action is performed on an entry in the hash table (ie. adding a new entry or altering a pre-existing entries value), the node containing the respective index of that entry is placed on the front of the queue. If the entry already exists, it is moved from its location to the front (so we don't end up with multiple copies of nodes referring to the same hash table slot). If an entry is removed from the hash table, it is removed from the queue.

### Performance:
####Queue
In the struct for my queue, I have pointers to the start and end nodes of a doubly-linked list. This allows quick access to the ends of the list, which is where we will be putting new elements, moving updated elements, and looking for information when doing evictions. Within the doubly-linked list implementation there are three main functions that affect the list: adding, updating, and deleting. Adding new elements is in constant time because we simply stick them on the front of the queue. Updating elements is kept in constant time because the function takes both a list and a pointer to a node in the list, so that we simply need to check for a few edge cases (all of which keep the runtime within O(1)) before moving it this node to the front. Similarly, deletions are kept in constant time because having a pointer to the node we want to delete means we don't have to iterate through the list to find it, and instead we can just immediately delete it after figuring out which case it falls under.
####Cache
To improve the expected runtimes of my functions, every entry in the hash table contains a key, a val, and a pointer to the entry's respective node in the queue (if it has one). There are three main functions in the cache: adding, removing, and getting the amount of memory stored. We expect adding key-val pairs to be constant time (which also relies on the user giving the cache a good hash function). In the case where we have to evict existing entries to make space for a new one, we reference the end of the queue to find the index of the LRU slot and evict the element in that slot. When deleting elements, the expected runtime is also constant (assuming the cache has a good hash function). To get the current stored amount of memory in constant time we look inside a value in the cache struct that keeps track of the amount of memory we've stored in the cache for us. This value is updated properly for adding new elements, altering elements, and deleting elements.

### Testing:
#### test.c
The `test.c` file contains tests for both the doubly-linked list and the cache implementations. Running the makefile creates an executable that runs the tests. There is more documentation of the specific cases that each test runs over in `test.c` and the testing functions will raise flags if any errors occur.

#### Valgrind
Valgrind was run on the executable to check for memory leaks and errors. This was absolutely brutal to debug because I was leaking tens of thousands of bytes and I raised a few thousand errors on the first run. Currently the tests raise 0 memory leaks and 0 errors from Valgrind.

### Comments:
So like all the other assignments, I feel like the end result is clunky because I am still in the process of learning C. It would certianly be faster to pair up with someone else, but as on all the assignments thus far, I feel compelled to write all my code myself for the sake of learning how to actually code in C. Valgrind debugging was absolutely brutal because of all the errors my code initially had, but ultimately very helpful in shaping my understanding of certain aspects of pointers and memory allocation. A huge improvement was having the makefile (which felt similar to having the leap from doing tests by hand to having a testing script on the last assignment, albeit a clunky one). I started this project feeling like I didn't understand pointers at all, and then gradually transitioning into the acceptance that they are just black magic. Humor aside, I found that this assignment and the tools I used were very helpful in actually building some understanding and intuition into pointers and memory allocation (both of which totally mystified me before this). Unfortunately, just getting this up and running properly without errors or leaks took me the full span of my nights and weekends in the last fortnight. However, given more time in the future, I would definitely like to come back and expand on this. Off the top of my head the first thing I'd like to build in would be threading capabilities, and perhaps thinking about more ways to abstract things for an actual API. Thanks for reading!

