# Operating Systems Project 04: Heap Management

For this project, I created a library that interacts with the OS to perform heap management on behalf of a user process. 

We utilize a circular doubly-linked free list to keep track of only the free blocks of previously allocated blocks that are no longer in use. We can then search this free list for a free block to re-use. If no such block exists, we simply grow the heap with sbrk(). Free() will insert released blocks to the free list to make them available for future re-use. 

Additional features include: 
1. Aligning all memory allocations to the nearest word size. 
2. Multiple search algorithms (First Fit, Best Fit, and Worst Fit). 
3. Shrinking the heap when a block is released. 
4. Splitting a block when it is re-used. 
5. Merging a block when it is inserted into the free list. 
6. Implementation of calloc and realloc functions. 
7. Tracking the number of operations performed by the allocator and the amount of internal fragmentation and external fragmentation. 
