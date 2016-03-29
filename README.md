# Software Cache
#### Alex Pan - HW3 (Post-Submission)
Implementation of a cache with a LRU eviction policy in C

### Information:
This is an updated version of the cache from HW3 (Hash-it-out). To see the submitted version of the cache, please see the branch `submitted(old)`. I have removed the makefile and tests from this branch since they no longer apply to the updated version. Currently this passes all "necessary" tests (ie tests of behavior specifically defined by our spec) in the HW4 repository `TestyCache`. 

### Fixes in this version:
* Lots of cleanup to the API. The header file `cache.h` is now the default one that was provided to us. The only change being one that was specified - adding a paramter to `create_cache()` for passing a hash function. The LRU files remain unchanged since I was primarily concerned with cleaning up the cache implementation. The struct definitions have been moved over to `cache.c`. I am unsure whether this would be called "best practice" but this mainly just serves the purpose of keeping our given API clean.
* Changed the default hash function into a modified jenkins hash, using an implementation by Alex Ledger
* Created seperate function calls for linear probing, adding elements, and updating elements. While there are now more functions, this makes it a little easier to actually figure out what is happening at a glance when looking at the functions specified in the API. 

### Notes on testing:
* To use this in the testing suite we made for HW4, simply replace relevant source files and make sure to update `cache_get_wrapper()` inside of `cache_wrapper.c`. This version of the cache adheres to the API so we don't need to have a special case, but to save time (ie replacing cache_get_wrapper with cache_get in every test file) just modify the wrapper function instead of deleting it.
* Running this should pass all our tests.

### Changes to come:
* Will be looking at other groups' submissions for HW4 to see if there were any bugs in my cache our testing did not catch. Patches will be made accordingly. 
* Hopefully I will find the time eventually (probably post semester) to add a slab allocator and multi-threading capabilities.
* One last note: I will be using whichever version of this cache is most up-to-date for the networking assignment.