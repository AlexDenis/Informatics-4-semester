#include "stdio.h"
#include "malloc.h"
#include "assert.h"
#include "array.h"

#define check(COND) { if (COND) { } else { fprintf (stderr, "Condition '%s' is false!\n", #COND); assert (0); } }

const int DEF_LEN    = 10;
const int MEM_STEP   = 10;
const int MAX_DATASZ = 301; 

enum {UNABLE_TO_ALLOCATE_MEMORY,
      ELEMENT_NOT_ADDED,
      WRITE_TO_UNALLOCATED_MEMORY,
      GARBAGE_READ};
      
const char* ERRORS [] = {"Unable to allocate memory for %i elements, max count is %i.\n",
			 "Element not added.\n",
			 "Trying to write to unallocated memory - element %i. Max number is %i. I'll drop that.\n",
			 "Trying to read garbage from not filled memory at index %i. Max ind %i.\n"};

struct array
{
	TYPE* data;
	int memlen;
	int datalen;
};

void print_exit_message ()
{
	if (arrays_count == 0) printf ("%s", OK_EXITING);
	else printf ("%s", NOT_OK_EXITING);
}

int pointer_valid (struct array* inp)
{
	if (inp != 0) return 1;
	else return 0;
}

int change_memsz (struct array* inp, int newmemlen)
{
	check (pointer_valid (inp))
	
	if (newmemlen > MAX_DATASZ)
	{
		fprintf (stderr, ERRORS [UNABLE_TO_ALLOCATE_MEMORY],newmemlen, MAX_DATASZ);
		
		return 0;
	}
	
	if (inp -> memlen == 0)
	{
		inp -> data = (TYPE*) malloc (sizeof (TYPE) * newmemlen);
		inp -> memlen = newmemlen;
	}
	
	else
	{
		printf ("reallocating with new mem len %i\n", newmemlen);
		inp -> data = (TYPE*) realloc (inp -> data, newmemlen * sizeof (TYPE));
		inp -> memlen = newmemlen;
	}
	
	return 1;
}

int init_array (struct array* inp)
{
	check (pointer_valid (inp))
	
	inp -> data    = 0;
	inp -> memlen  = 0;
	inp -> datalen = 0;
	
	int suc = change_memsz (inp, DEF_LEN);
	
	arrays_count ++;
	
	return suc;
}

int zero_array (struct array* inp)
{
	check (pointer_valid (inp))
	
	int i = 0;
	for (; i < inp -> datalen; i ++) inp -> data [i] = 0;
	inp -> datalen = 0;
	
	return 1;
}

int delete_array (struct array* inp)
{
	check (pointer_valid (inp))
	
	free (inp -> data);
	inp -> datalen = 0;
	inp -> memlen  = 0;
	
	arrays_count --;
	
	return 1;
}
