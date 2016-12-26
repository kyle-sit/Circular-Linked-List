#include <stdio.h>
#include "list.h"
#include "stack.h"

/*-------------------------------------------------------------------------- 
Function Name:         delete_Stack
Purpose:               Calls delete list 
Description:           stack is front for a list that is truly deleted
Input:                 @param is a stack pointer pointer pointing to 
			memory we want to deallocate
Result:                none
--------------------------------------------------------------------------*/
void delete_Stack (Stack ** spp) {
        delete_List (spp);
}

/*-------------------------------------------------------------------------- 
Function Name:         isempty_Stack
Purpose:               Checks if the stack is empty
Description:           Since stack is a front for list we actually check
			if the list is empty.
Input:                 @param this_stack is a pointer to the stack we want
			to check
Result:			return true or false
--------------------------------------------------------------------------*/
long isempty_Stack (Stack * this_stack) {
        return isempty_List (this_stack);
}

/*-------------------------------------------------------------------------- 
Function Name:         new_Stack
Purpose:               Create a new stack
Description:           Actually allocates memory for a list
Input:                 @param copy_func is the function used for driver2
			@param delete_func is the function used for
			deallocating memory
			@param write_func is the function used to write
			the stack to the stream
Result:                the new stack
--------------------------------------------------------------------------*/
Stack * new_Stack (void *(*copy_func) (void *),
        void (*delete_func) (void *),
        FILE *(*write_func) (void *, FILE *)) {

        return new_List (copy_func, delete_func, write_func);
}

/*-------------------------------------------------------------------------- 
Function Name:         pop
Purpose:               Remove the top item of the stack
Description:           Actually calls remove list to remove the top node
Input:                 @param this_stack is a pointer to the stack to pop
Result:                A stack smaller by one
--------------------------------------------------------------------------*/
void * pop (Stack * this_stack) {
        return remove_List (this_stack, END);
}

/*-------------------------------------------------------------------------- 
Function Name:         push
Purpose:               Insert an item to the top of the stack
Description:           Uses list's insert to actually insert an item into
			the top of the list
Input:                 @param this_stack is a pointer to the stack to push 
			onto
			@param element is the element to push on
Result:                
--------------------------------------------------------------------------*/
long push (Stack * this_stack, void * element) {
        return insert (this_stack, element, END);
}

/*-------------------------------------------------------------------------- 
Function Name:         top
Purpose:               View the top item of the stack
Description:           Use list's view to see the top item of the list
Input:                 @param this_stack is the stack we want to view
Result:                Return the return of view
--------------------------------------------------------------------------*/
void * top (Stack * this_stack) {
        return view (this_stack, END);
}

/*-------------------------------------------------------------------------- 
Function Name:         write_Stack
Purpose:               Used to write the stack out to the stream
Description:           Calls list's write to display 
Input:                 @param this_stack is the stack we want to write out
			@param stream is the stream we write onto
Result:                A stream containing the written stack to display
--------------------------------------------------------------------------*/
FILE * write_Stack (Stack * this_stack, FILE * stream) {
        return write_List (this_stack, stream);
}
