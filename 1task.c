#include "sorted_array.c"

int main ()
	{
	struct array array1;
	struct array array2;
	
	check (init_array (&array1))
	check (init_array (&array2))
	
	check (verbose_full_print (&array1))
	
	check (add_element(&array1, 5))
	check (add_element (&array1, 1))
	check (add_element (&array1, 8))
	check (add_element (&array1, 41))
	check (add_element (&array1, 3))
	check (add_element (&array1, 9))
	check (add_element (&array1, 13))
	check (verbose_full_print (&array1))
	check (remove_element (&array1, 4))
	check (print_array (&array1))
	
	check (find_element(&array1, 8))
	
	check (print_array (&array1))
	
	check (change_element (&array1, 3, 7))
	check (print_array (&array1))
	
	check (zero_array   (&array1))
	check (print_array (&array1))
	printf ("datalen = %i, memlen = %i\n", get_datalen (&array1), get_memlen (&array1));
	
	for (int i = 0; i < MAX_DATASZ + 5; i ++)
		/*check (*/add_element_to_end (&array2, 41);//)
	
	check (delete_array (&array1))
	print_exit_message ();
	check (delete_array (&array2))
	print_exit_message ();
	
	return 0;
	}
