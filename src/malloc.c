/* malloc.c: POSIX API Implementation */

#include "malloc/counters.h"
#include "malloc/freelist.h"

#include <assert.h>
#include <string.h>

/* Functions */
/**
 * Allocate specified amount memory.
 * @param   size    Amount of bytes to allocate.
 * @return  Pointer to the requested amount of memory.
 **/
void *malloc(size_t size) {
    // Initialize counters
    init_counters();

    // Handle empty size
    if (!size) {
        return NULL;
    }

    // Search free list for any available block with matching size
    Block *block = free_list_search(size);
    if(block) {
        block = block_split(block, size);
        if(block) {
            block_detach(block);
        }
    } else { 
        block = block_allocate(size);
    }

    // Could not find free block or allocate a block, so just return NULL
    if (!block) {
        return NULL;
    }

    // Check allocate block makes sense
    assert(block->capacity >= block->size);
    assert(block->size     == size);
    assert(block->next     == block);
    assert(block->prev     == block);

    // Update counters
    Counters[MALLOCS]++;
    Counters[REQUESTED] += size;

    // Return data address associated with block
    return block->data;
}

/**
 * Release previously allocated memory.
 * @param   ptr     Pointer to previously allocated memory.
 **/
void free(void *ptr) {
    if (!ptr) {
        return;
    }

    Block *block = BLOCK_FROM_POINTER(ptr);

    // Update counters
    Counters[FREES]++;

    // Try to release block, otherwise insert into free list

    if(block_release(block)) { 
	return;
    } else {
	free_list_insert(block);
    }

}

/**
 * Allocate memory with specified number of elements and with each element set
 * to 0.
 * @param   nmemb   Number of elements.
 * @param   size    Size of each element.
 * @return  Pointer to requested amount of memory.
 **/
void *calloc(size_t nmemb, size_t size) {

    init_counters();

    if (!size || !nmemb) {
    	return NULL;
    }

    void* block = malloc(nmemb*size);
    memset(block, 0, nmemb*size);

    // Update Counters	
    Counters[CALLOCS]++;

    return block;

}

/**
 * Reallocate memory with specified size.
 * @param   ptr     Pointer to previously allocated memory.
 * @param   size    Amount of bytes to allocate.
 * @return  Pointer to requested amount of memory.
 **/
void *realloc(void *ptr, size_t size) {
    // Implement realloc
    if(!ptr) {
        return malloc(size);
    }

    Block *block = BLOCK_FROM_POINTER(ptr);
    if(block->size >= size) {
        return ptr;
    }

    void *new = malloc(size);
    if(!new) {
        return NULL;
    }

    // Update Counters	
    Counters[REALLOCS]++;


    memcpy(new, ptr, block->size);
    free(ptr);
    return new;



}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
