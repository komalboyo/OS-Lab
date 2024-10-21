#include <stdio.h>
#include <stdlib.h>

// Define the structure and typedefs
struct mab {
    int offset;
    int size;
    int allocated;
    struct mab *next;
    struct mab *prev;
};
typedef struct mab Mab;
typedef Mab* MabPtr;

MabPtr last_allocated = NULL; // For Next Fit tracking

// Function prototypes
MabPtr memChk(MabPtr m, int size); // check if memory available
MabPtr memAlloc(MabPtr m, int size, int policy); // allocate memory
MabPtr memFree(MabPtr m); // free memory block
MabPtr memMerge(MabPtr m); // merge adjacent blocks
MabPtr memSplit(MabPtr m, int size); // split memory block

// Check if there is a memory block of at least 'size' free
MabPtr memChk(MabPtr m, int size) {
    MabPtr current = m;
    while (current != NULL) {
        if (!current->allocated && current->size >= size) {
            return current; // Found a suitable block
        }
        current = current->next;
    }
    return NULL; // No suitable block found
}

// Allocate memory based on the policy
MabPtr memAlloc(MabPtr m, int size, int policy) {
    MabPtr selectedBlock = NULL;
    MabPtr current = m;
    
    switch (policy) {
        case 1: // First Fit
            while (current != NULL) {
                if (!current->allocated && current->size >= size) {
                    selectedBlock = current;
                    break;
                }
                current = current->next;
            }
            break;
        
        case 2: // Best Fit
            while (current != NULL) {
                if (!current->allocated && current->size >= size) {
                    if (selectedBlock == NULL || current->size < selectedBlock->size) {
                        selectedBlock = current;
                    }
                }
                current = current->next;
            }
            break;
        
        case 3: // Worst Fit
            while (current != NULL) {
                if (!current->allocated && current->size >= size) {
                    if (selectedBlock == NULL || current->size > selectedBlock->size) {
                        selectedBlock = current;
                    }
                }
                current = current->next;
            }
            break;
        
        case 4: // Next Fit
            if (last_allocated == NULL) last_allocated = m;
            current = last_allocated;
            while (current != NULL) {
                if (!current->allocated && current->size >= size) {
                    selectedBlock = current;
                    break;
                }
                current = current->next;
            }
            if (selectedBlock == NULL) {
                current = m; // Wrap around if no block found after last_allocated
                while (current != last_allocated) {
                    if (!current->allocated && current->size >= size) {
                        selectedBlock = current;
                        break;
                    }
                    current = current->next;
                }
            }
            last_allocated = selectedBlock;
            break;
        
        default:
            printf("Unknown allocation policy\n");
            return NULL;
    }

    if (selectedBlock != NULL) {
        if (selectedBlock->size > size) {
            // Split block if necessary
            memSplit(selectedBlock, size);
        }
        selectedBlock->allocated = 1; // Mark block as allocated
    } else {
        printf("No suitable block available for allocation\n");
    }

    return selectedBlock;
}

// Free a memory block
MabPtr memFree(MabPtr m) {
    m->allocated = 0; // Mark block as free
    // Merge adjacent free blocks
    if (m->prev && !m->prev->allocated) {
        m = memMerge(m->prev);
    }
    if (m->next && !m->next->allocated) {
        m = memMerge(m);
    }
    return m;
}

// Merge two adjacent free blocks
MabPtr memMerge(MabPtr m) {
    if (m->next && !m->next->allocated) {
        // Merge current block with the next block
        MabPtr nextBlock = m->next;
        m->size += nextBlock->size; // Increase size of current block
        m->next = nextBlock->next; // Bypass the next block
        if (nextBlock->next) {
            nextBlock->next->prev = m;
        }
        free(nextBlock); // Free the memory for the merged block
    }
    return m;
}

// Split a memory block
MabPtr memSplit(MabPtr m, int size) {
    if (m->size > size) {
        // Create a new block for the remaining memory
        MabPtr newBlock = (MabPtr) malloc(sizeof(Mab));
        newBlock->offset = m->offset + size;
        newBlock->size = m->size - size;
        newBlock->allocated = 0;
        newBlock->next = m->next;
        newBlock->prev = m;
        
        if (m->next) {
            m->next->prev = newBlock;
        }
        
        m->next = newBlock;
        m->size = size;
    }
    return m;
}

// Utility function to create a new memory block
MabPtr createBlock(int offset, int size, int allocated) {
    MabPtr newBlock = (MabPtr) malloc(sizeof(Mab));
    newBlock->offset = offset;
    newBlock->size = size;
    newBlock->allocated = allocated;
    newBlock->next = NULL;
    newBlock->prev = NULL;
    return newBlock;
}

// Utility function to print memory blocks
void printMemory(MabPtr head) {
    MabPtr current = head;
    while (current != NULL) {
        printf("Block offset: %d, size: %d, allocated: %d\n", current->offset, current->size, current->allocated);
        current = current->next;
    }
}

int main() {
    // Create a simple memory structure
    MabPtr block1 = createBlock(0, 100, 0);
    MabPtr block2 = createBlock(100, 200, 0);
    MabPtr block3 = createBlock(300, 150, 0);
    
    // Link blocks
    block1->next = block2;
    block2->prev = block1;
    block2->next = block3;
    block3->prev = block2;
    
    printMemory(block1);
    
    printf("\nAllocating 50 bytes using Best Fit...\n");
    memAlloc(block1, 50, 2); // Best Fit
    printMemory(block1);
    
    printf("\nAllocating 100 bytes using Worst Fit...\n");
    memAlloc(block1, 100, 3); // Worst Fit
    printMemory(block1);
    
    printf("\nAllocating 80 bytes using First Fit...\n");
    memAlloc(block1, 80, 1); // First Fit
    printMemory(block1);
    
    printf("\nAllocating 30 bytes using Next Fit...\n");
    memAlloc(block1, 30, 4); // Next Fit
    printMemory(block1);
    
    printf("\nFreeing the first allocated block...\n");
    memFree(block1);
    printMemory(block1);
    
    return 0;
}
