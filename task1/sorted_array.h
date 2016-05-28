#ifndef sort_arr
#define sort_arr

#define check(COND) { if (COND) { } else { fprintf (stderr, "Condition '%s' is false!\n", #COND); assert (0); } }


typedef int TYPE;
	
enum {SUCCESFULLY_CREATED,
	  NO_ERRORS,
	  UNABLE_TO_ALLOCATE_MEMORY,
      ELEMENT_NOT_ADDED,
      WRITE_TO_UNALLOCATED_MEMORY,
      GARBAGE_READ,
      ELEMENT_NOT_FOUND,
      INVALID_POINTER};

struct array
{
	TYPE* data;
	int memlen;
	int datalen;
};

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
int elements_sum (struct array* inp);
int zero_array (struct array* inp);

//METADATA GETTERS
int get_datalen (struct array* inp);
int get_memlen (struct array* inp);

//PRINTING FUNCTION
int print_element (struct array* inp, int ind);
int print_array (struct array* inp);
int verbose_full_print (struct array* inp);

void print_exit_message ();

#endif
#undef sort_arr
