# Project 04: Heap Management

This is [Project 04] of [CSE.30341.FA19].

## Student

- Robert Reutiman (rreutima@nd.edu)

## Brainstorming

The following are questions that should help you in thinking about how to
approach implementing [Project 03].  For this project, responses to these
brainstorming questions are not required.

### Block

1. When **releasing** a `Block`:

    1. How do you determine if the `Block` you are releasing is at the end of
       the heap?

    2. How do you compute how much was actually allocated for the `Block`
       (including the header)?
       
    3. How do you adjust the heap pointer.

2. When **detaching** a `Block`, what pointers need to be updated?

3. When **merging** two `Block`s:

    1. How do you determine the **end** of the destination `Block`?

    2. How do you determine the **start** of the source `Block`?
    
    3. What is the **capacity** of the **merged** `Block`?

4. When **splitting** a `Block`:

    1. What do you do if the `Block`'s **capacity** is not large enough for a
       new `Block` header and the **aligned** `size`?
       
    2. What is the address of the new `Block` you split off?
    
    3. What is the capacity of the new `Block` you split off?

    4. What are the pointers of the new `Block`?
    
    5. What must be updated for the original `Block` (after the split)?

### Counters

1. What do we need to keep track of to compute the **internal fragmentation**
   of the **Free List**?

2. What do we need to keep track of to compute the **external fragmentation**
   of the **Free List**?

### Free List

1. What are we looking for in the **First Fit** algorithm?

2. What are we looking for in the **Best Fit** algorithm?

3. What are we looking for in the **Worst Fit** algorithm?

4. When we **insert** into the **Free List**:
    
    1. When do we want to **merge** blocks?

    2. What pointers needed to be updated when we **merge** blocks?

    3. What happens when we can't perform a merge in the middle of the
       **FreeList**?

### POSIX

1. During a `malloc`, when do we **split** a `Block`, **allocate** a `Block`,
   and `detach` a `Block`?
   
2. When we `free`, when do we try to **release** a `Block` and what happens if
   that fails?
   
3. What happens during a `calloc`?

4. What happens during a `realloc`?

## Reflection

1. When does **internal fragmentation** and **external fragmentation** occur?

	Internal fragmentation occurs when our allocator hands out chunks of memory
	larger than requested. Any unasked for (and thus unused) space is internal
	fragmentation.

	External Fragmentation occurs when there is not enough contigous space in 
	a single block although we have enough space overall for an allocaiton.

2. Considering the following questions, discuss which heap management strategy
   is the **best** (based on your implementation and your testing or
   experimentation):
   
    - Which heap management strategy requires the least amount of heap space?

	Best Fit
    
    - Which heap management strategy was the fastest?

	First Fit

    - Which heap management strategy exhibited the least fragmentation?
    
	Worst fit exhibits the least external fragmentation.
	Best fit exhibits the least internal fragmentation.
	

	In my opinion, the best strategy is Best Fit simply because it has the 
	most notable advantages. It minimizes both heap space external fragmentation,
	which, compared to our other approaches, appears to be have the most upside.


## Errata

> Describe any known errors, bugs, or deviations from the requirements.

## Extra Credit

> Describe what extra credit (if any) that you implemented.

[Project 04]:       https://www3.nd.edu/~pbui/teaching/cse.30341.fa19/project04.html
[CSE.30341.FA19]:   https://www3.nd.edu/~pbui/teaching/cse.30341.fa19/
