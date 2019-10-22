#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "smalloc.h"



void *mem;
struct block *freelist;
struct block *allocated_list;


void *smalloc(unsigned int nbytes) {
	//TODO
    struct block* current = freelist;
    struct block* previous = freelist;

    //Calculate the offset and, if it is non-zero, add it to nbytes.
    int offset = 0;
    if((nbytes % 8) != 0){
        offset = 8 - (nbytes %8 );
        nbytes = nbytes + offset;
    }

    //Iterate through freelist to find a block large enough to hold nbytes.
    while(current != NULL){
        if(current->size >= nbytes){
            break;
        }
        previous = current;
        current = current->next;
    }
    //If current has reached NULL, then there isn't any block large enough
    //for nbytes and we can end the function.
    if(current == NULL){
        return NULL;
    }
    //If the current size is equal to nbytes, we don't need to allocate any
    //new memory. If current size is greater, then we do.
    if((current->size) > nbytes){
        struct block* new_node = malloc(sizeof(struct block));
        new_node->addr = current->addr;
        new_node->size = nbytes;
        new_node->next = allocated_list;
        allocated_list = new_node;

        current->addr = (current->addr) + nbytes;
        current->size = current->size - nbytes;
        return new_node->addr;
    }
    if((current->size) == nbytes){
        previous->next = current->next;
        current->next = allocated_list;
        allocated_list = current;
        return current->addr;

    }
    return NULL;
}


int sfree(void *addr) {
	//TODO
    return -1;
}


/* Initialize the memory space used by smalloc,
 * freelist, and allocated_list
 * Note:  mmap is a system call that has a wide variety of uses.  In our
 * case we are using it to allocate a large region of memory. 
 * - mmap returns a pointer to the allocated memory
 * Arguments:
 * - NULL: a suggestion for where to place the memory. We will let the 
 *         system decide where to place the memory.
 * - PROT_READ | PROT_WRITE: we will use the memory for both reading
 *         and writing.
 * - MAP_PRIVATE | MAP_ANON: the memory is just for this process, and 
 *         is not associated with a file.
 * - -1: because this memory is not associated with a file, the file 
 *         descriptor argument is set to -1
 * - 0: only used if the address space is associated with a file.
 */
void mem_init(int size) {
    mem = mmap(NULL, size,  PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if(mem == MAP_FAILED) {
         perror("mmap");
         exit(1);
    }

    //Initialize freelist array
    freelist = malloc(sizeof(struct block));
	
    //Set values for freelist

    freelist->addr = mem;
    freelist->size = size;
    freelist->next = NULL;
        
}

void mem_clean(){

	//TODO
}

