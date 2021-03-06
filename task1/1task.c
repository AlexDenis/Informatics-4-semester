#include "stdio.h"
#include "malloc.h"
#include "assert.h"
#include "sorted_array.h"


#define test( FUNC, CORRECT_ERR_CODE ) \
if (FUNC != CORRECT_ERR_CODE) { \
printf ("Unexpected error or absence of expected error!\n"); \
 notpassed ++;} \
 else { printf ("Function %s created with right error code '%s'.\n", #FUNC, ERRORS_1[CORRECT_ERR_CODE]); \
 passed ++;}
 
 const char* ERRORS_1 [] = {"Massive was succesfully created",
						 "No errors occured",
			 			 "Unable to allocate memory for %i elements, max count is %i\n",
						 "Element not added",
						 "Trying to write to unallocated memory - element %i. Max number is %i.\n",
						 "Trying to read garbage from not filled memory at index %i. Max ind %i",
						 "Element %i not found", 
						 "You've got invalid pointer"};
 
int main ()
{
	int notpassed = 0;
	int passed = 0;
	
	struct array array1;
	
	check (init_array (&array1))
	
	test (add_element (&array1, 1), NO_ERRORS)
	
	test (add_element (&array1, 8), NO_ERRORS)
	
	test (change_element(&array1, 12, 33), WRITE_TO_UNALLOCATED_MEMORY)
	
	test (change_element(&array1, 1, 33), NO_ERRORS)
	
	test (add_element (&array1, 41), NO_ERRORS)
	
	test (add_element (&array1, 3), NO_ERRORS)
	
	test (add_element (&array1, 9), NO_ERRORS)
	
	
	test (elements_sum (&array1), NO_ERRORS)
	
	test (add_element (&array1, 13), NO_ERRORS)
	
	test (verbose_full_print (&array1), NO_ERRORS)
	
	test (remove_element (&array1, 4), NO_ERRORS)
	
	test (print_array (&array1), NO_ERRORS)
	
	test (find_element(&array1, 120), ELEMENT_NOT_FOUND)
	
	test (print_array (&array1), NO_ERRORS)
	
	test (print_array (&array1), NO_ERRORS)
	
	test (print_element(&array1, 40), GARBAGE_READ)
	
	test (zero_array   (&array1), NO_ERRORS)
	
	test (print_array (&array1), NO_ERRORS)
	
	printf ("datalen = %i, memlen = %i\n", get_datalen (&array1), get_memlen (&array1));
	
	for (int i = 0; i < 305; i ++)
		check (add_element (&array1, 41)); 
	
	printf ("Passed %i, not passed %i.\n", passed, notpassed);
	
	test (delete_array (&array1), NO_ERRORS)
	
	print_exit_message ();
	
	return 0;
}
