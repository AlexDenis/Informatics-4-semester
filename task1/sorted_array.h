typedef int TYPE;

void print_exit_message ();
	
enum {SUCCESFULLY_CREATED,
	  NO_ERRORS,
	  UNABLE_TO_ALLOCATE_MEMORY,
      ELEMENT_NOT_ADDED,
      WRITE_TO_UNALLOCATED_MEMORY,
      GARBAGE_READ,
      ELEMENT_NOT_FOUND,
      INVALID_POINTER};
      
const char* ERRORS [] = {"Massive was succesfully created",
						 "No errors occured",
			 			 "Unable to allocate memory for %i elements, max count is %i\n",
						 "Element not added",
						 "Trying to write to unallocated memory - element %i. Max number is %i.\n",
						 "Trying to read garbage from not filled memory at index %i. Max ind %i",
						 "Element %i not found", 
						 "You've got invalid pointer"};

struct array;

//MEMORY CONTROL
int change_memsz (struct array* inp, int newmemlen);
int init_array (struct array* inp);
int delete_array (struct array* inp);

//WORK WITH DATA
int add_element (struct array* inp, TYPE new_element);
int remove_element (struct array* inp, int position);
int find_element(struct array* inp, TYPE element_to_be_found);    
int change_element (struct array* inp, int ind, TYPE new_element);   
int change_element (struct array* inp, int ind, TYPE new_element);
int zero_array (struct array* inp);

//METADATA GETTERS
int get_datalen (struct array* inp);
int get_memlen (struct array* inp);

//PRINTING FUNCTION
int print_element (struct array* inp, int ind);
int print_array (struct array* inp);
int verbose_full_print (struct array* inp);

