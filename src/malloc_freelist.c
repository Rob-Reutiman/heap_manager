/* malloc_freelist.c: Free List Implementation
 *
 * The FreeList is an unordered doubly-linked circular list containing all the
 * available memory allocations (memory that has been previous allocated and
 * can be re-used).
 **/

#include "malloc/counters.h"
#include "malloc/freelist.h"
#include <unistd.h>
#include <string.h>

/* Global Variables */

Block FreeList = {-1, -1, &FreeList, &FreeList};

/* Functions */

/**
 * Search for an existing block in free list with at least the specified size
 * using the first fit algorithm.
 * @param   size    Amount of memory required.
 * @return  Pointer to existing block (otherwise NULL if none are available).
 **/
Block * free_list_search_ff(size_t size) {
    // Implement first fit algorithm

    for(Block *curr = FreeList.next; curr != &FreeList; curr = curr->next) {
        if(curr->capacity >= size) {
    	    return curr;
        }
    }

    return NULL;

}

/**
 * Search for an existing block in free list with at least the specified size
 * using the best fit algorithm.
 * @param   size    Amount of memory required.
 * @return  Pointer to existing block (otherwise NULL if none are available).
 **/
Block * free_list_search_bf(size_t size) {
    // Implement best fit algorithm
    
    Block *optimal = NULL;

    for(Block *curr = FreeList.next; curr != &FreeList; curr = curr->next) {
        if(optimal == NULL && curr->size >= size) {
            optimal = curr;
        }
        if(optimal) {
            if(curr->size < optimal->size && curr->size >= size) {
                optimal = curr;
            }
        }
    }

    return optimal;
    
}

/**
 * Search for an existing block in free list with at least the specified size
 * using the worst fit algorithm.
 * @param   size    Amount of memory required.
 * @return  Pointer to existing block (otherwise NULL if none are available).
 **/
Block * free_list_search_wf(size_t size) {
    // Implement worst fit algorithm
 
    Block * worst = NULL;

    for(Block *curr = FreeList.next; curr != &FreeList; curr = curr->next) {
        if(worst == NULL && curr->size >= size) {
           worst = curr;
        }       
        if(worst) {
            if(curr->size > worst->size && curr->size >= size) {
                worst = curr;
            } 
        }  
    } 

    return worst;
}

/**
 * Search for an existing block in free list with at least the specified size.
 *
 * Note, this is a wrapper function that calls one of the three algorithms
 * above based on the compile-time setting.
 *
 * @param   size    Amount of memory required.
 * @return  Pointer to existing block (otherwise NULL if none are available).
 **/
Block * free_list_search(size_t size) {
    Block * block = NULL;
#if	defined FIT && FIT == 0
    block = free_list_search_ff(size);
#elif	defined FIT && FIT == 1
    block = free_list_search_bf(size);
#elif	defined FIT && FIT == 2
    block = free_list_search_wf(size);
#endif

    if (block) {
        Counters[REUSES]++;
    }
    return block;
}

/**
 * Insert specified block into free list.
 *
 * Scan the free list and attempt to merge specified block into an existing
 * block (or a current block into the specified block, updating the pointers
 * appropriately).
 *
 * If a merge is not possible, then simply add the block to the end of the free
 * list.
 * @param   block   Pointer to block to insert into free list.
 **/
void	free_list_insert(Block *block) {
    // Implement free list insertion

    Block *curr = FreeList.next;
	
    while(curr != &FreeList) {
	if(block_merge(curr, block)) {
	    return;
	}
        if(block_merge(block, curr) ) {
            block->prev = curr->prev;
            block->next = curr->next;

            curr->prev->next = block;
            curr->next->prev = block;

            return;
        }
        curr = curr->next;
    }

    block->prev = FreeList.prev;
    block->next = &FreeList;
		
    FreeList.prev->next = block;
    FreeList.prev = block;
    
}

/**
 * Return length of free list.
 * @return  Length of the free list.
 **/
size_t  free_list_length() {
    // Implement free list length

    size_t length = 0;

    for(Block *curr = FreeList.next; curr != &FreeList; curr = curr->next) {
        length++;	
    }

    return length;

}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
