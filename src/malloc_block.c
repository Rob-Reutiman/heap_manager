/* malloc_block.c: Block Structure */

#include "malloc/block.h"
#include "malloc/counters.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/* Functions */

/**
 * Allocate a new block on the heap using sbrk:
 *
 *  1. Determined aligned amount of memory to allocate.
 *  2. Allocate memory on the heap.
 *  3. Set allocage block properties.
 *
 * @param   size    Number of bytes to allocate.
 * @return  Pointer to data portion of newly allocate block.
 **/
Block *	block_allocate(size_t size) {
    // Allocate block
    intptr_t allocated = sizeof(Block) + ALIGN(size);
    Block *  block     = sbrk(allocated);
    if (block == SBRK_FAILURE) {
    	return NULL;
    }

    // Record block information
    block->capacity = ALIGN(size);
    block->size     = size;
    block->prev     = block;
    block->next     = block;

    // Update counters
    Counters[HEAP_SIZE] += allocated;
    Counters[BLOCKS]++;
    Counters[GROWS]++;
    return block;
}

/**
 * Attempt to release memory used by block to heap if:
 *
 *  1. the block is at the end of the heap.
 *  2. the block capacity meets the trim threshold.
 *
 * @param   block   Pointer to block to release.
 * @return  Whether or not the release completed successfully.
 **/
bool	block_release(Block *block) {
    // Implement block release
    
    if( block->capacity + sizeof(Block) >= TRIM_THRESHOLD && (intptr_t)block->data+block->capacity == (intptr_t)sbrk(0) ) {

        size_t allocated = sizeof(Block) + block->capacity;
    
        if(sbrk(-allocated) == SBRK_FAILURE) {
            return false;
        }

        Counters[BLOCKS]--;
        Counters[SHRINKS]++;
        Counters[HEAP_SIZE] -= allocated;

        return true;
    } 

    return false;
}

/**
 * Detach specified block from its neighbors.
 *
 * @param   block   Pointer to block to detach.
 * @return  Pointer to detached block.
 **/
Block * block_detach(Block *block) {
    // Detach block from neighbors by updating previous and next block
    
    // Handle neighbors
    block->prev->next = block->next;
    block->next->prev = block->prev;

    // Handle block
    block->prev = block;
    block->next = block;

    return block;
}

/**
 * Attempt to merge source block into destination.
 *
 *  1. Compute end of destination and start of source.
 *
 *  2. If they both match, then merge source into destination by giving the
 *  destination all of the memory allocated to source.
 *
 * @param   dst     Destination block we are merging into.
 * @param   src     Source block we are merging from.
 * @return  Whether or not the merge completed successfully.
 **/
bool	block_merge(Block *dst, Block *src) {
    // Implement block merge

    if( (intptr_t)src == (intptr_t)(dst->data + dst->capacity) ) {

        dst->capacity += sizeof(Block) + src->capacity;

        Counters[MERGES]++;
        Counters[BLOCKS]--;
        return true;

    }
 
    return false;
}

/**
 * Attempt to split block with the specified size:
 *
 *  1. Check if block capacity is sufficient for requested aligned size and
 *  header Block.
 *
 *  2. Split specified block into two blocks.
 *
 * @param   block   Pointer to block to split into two separate blocks.
 * @param   size    Desired size of the first block after split.
 * @return  Pointer to original block (regardless if it was split or not). 
 **/
Block * block_split(Block *block, size_t size) {
    // Implement block split
    if(!block) {
        return NULL;
    }
    
    if(block->capacity > (sizeof(Block) + ALIGN(size)) ) {

        Block *new_block = (Block*) (block->data + ALIGN(size) );

        // Updating new block
        new_block->prev = block;
        new_block->next = block->next;
        new_block->next->prev = new_block;
        new_block->capacity = block->capacity - sizeof(Block) - ALIGN(size);
        new_block->size = new_block->capacity;

        // Updating split block
        block->next = new_block;
        block->capacity = ALIGN(size);
        block->size = size;

        Counters[SPLITS]++;
        Counters[BLOCKS]++;

    } else {

        block->size = size;

    }

    return block;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
