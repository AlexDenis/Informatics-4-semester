typedef int TYPE;

void print_exit_message ();
	
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
int zero_array (struct array* inp);

//METADATA GETTERS
int get_datalen (struct array* inp);
int get_memlen (struct array* inp);

//PRINTING FUNCTION
int print_element (struct array* inp, int ind);
int print_array (struct array* inp);
int verbose_full_print (struct array* inp);
