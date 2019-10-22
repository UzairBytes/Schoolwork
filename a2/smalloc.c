#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "smalloc.h"



void *mem;
struct block *freelist;
struct block *allocated_list;
/* Reserves nbytes bytes of space from the memory region created by mem_init.
 * If the memory is reserved (allocated) successfully, Returns a pointer to the reserved memory. 
 * If the memory cannot be reserved (i.e. there is no block that is large enough to hold nbytes bytes), returns NULL
*/
void *smalloc(unsigned int nbytes) {
	//Initialize block pointers for freelist.
    struct block* current = freelist;
    struct block* previous = freelist;

    //Calculate the offset and, if it is non-zero, add it to nbytes.
    int offset = 0;
    if((nbytes % 8) != 0){
        offset = 8 - (nbytes %8 );
        nbytes = nbytes + offset;
    }

    //Traverse through freelist to find a block large enough to hold nbytes.
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
    //new memory. If current size is greater, then we do. Returns the address
    //of the block.
    if(current->size == nbytes){
        previous->next = current->next;
        current->next = allocated_list;
        allocated_list = current;
        return current->addr;
    }
    
    if(current->size > nbytes){
        struct block* new_node = malloc(sizeof(struct block));
        new_node->addr = current->addr;
        new_node->size = nbytes;
        new_node->next = allocated_list;
        allocated_list = new_node;

        current->addr = (current->addr) + nbytes;
        current->size = current->size - nbytes;
        return new_node->addr;
    }
    
    return NULL;
}

/* Returns memory allocated by smalloc to the list of free blocks so that it might be reused later.
 * If the specified address is not found, returns -1.
 */
int sfree(void *addr) {
    //Initialize block pointers from allocated list.
	struct block* current = allocated_list;
    struct block* previous = allocated_list;

    //Traverse through allocated list to find the block with the
    //specified address.
    while(current !=NULL){
        if(current->addr == addr){
            break;
        }
        previous = current;
        current = current->next;
    }

    //If current has reached NULL, then there is no block with the
    //specified address so we can end the function and return -1.
    if(current == NULL){
        return -1;
    }
    
    //Modifies the linked list so current can no longer be accessed
    //by traversing the allocated list.
    previous->next = current->next;
    current->next = freelist;
    freelist = current;

    return 0;
    
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

