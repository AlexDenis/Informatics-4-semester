#include "array.cpp"

#define try_check( CALL ) \
try \
{ \
CALL;\
} \

catch (exception& ex) \
{ \
	fprintf (stderr, "%s", ex.what ()); \
	err_count ++; \
} \
tests_passed ++;

int main ()
{
	int err_count    = 0;
	int tests_passed = 0;
	
	array <int>* array1 = new array <int> ();
	array <int>* array2 = new array <int> ();
	
	try_check (array1->init_array ())
	try_check (array2 -> init_array ())
	
	try_check (array1 -> verbose_full_print ())
	
	try_check (array1 -> add_element (5))
	try_check (array1 -> add_element_to_end (1))
	try_check (array1 -> add_element_to_end (8))
	try_check (array1 -> add_element_to_end (41))
	try_check (array1 -> add_element_to_end (3))
	try_check (array1 -> add_element_to_end (3))
	try_check (array1 -> add_element_to_end (8))
	try_check (array1 -> add_element_to_end (13))
	
	try_check (array1 -> verbose_full_print ())
	
	try_check (array1 -> remove_element_from_end ())
	
	try_check (array1 -> print_array ())

	
	return 0;
}
