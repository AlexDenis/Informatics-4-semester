#include "stdio.h"
#include "malloc.h"
#include "assert.h"
#include "sorted_array.h"

#define check(COND) { if (COND) { } else { fprintf (stderr, "Condition '%s' is false!\n", #COND); assert (0); } }

//gcc -fprofile-arcs -ftest-coverage -std=c99 1task.c -o 1task
//gcov -b ./1task.c | tee output.txt
// valgrind --leak-check=full --leak-resolution=med ./1task

const int DEF_LEN    = 10;
const int MEM_STEP   = 10;
const int MAX_DATASZ = 301; 

int arrays_count = 0;
const char* OK_EXITING = "You've deleted all the arrays.\n";
const char* NOT_OK_EXITING = "You've not deleted all the arrays.\n'";

enum {UNABLE_TO_ALLOCATE_MEMORY,
      ELEMENT_NOT_ADDED,
      WRITE_TO_UNALLOCATED_MEMORY,
      GARBAGE_READ,
      ELEMENT_NOT_FOUND};
      
const char* ERRORS [] = {"Unable to allocate memory for %i elements, max count is %i.\n",
			 "Element not added.\n",
			 "Trying to write to unallocated memory - element %i. Max number is %i. I'll drop that.\n",
			 "Trying to read garbage from not filled memory at index %i. Max ind %i.\n",
			 "Element %i not found.\n"};

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
		fprintf (stderr, ERRORS [UNABLE_TO_ALLOCATE_MEMORY], newmemlen, MAX_DATASZ);
		
		return 0;
	}
	
	else if (inp -> memlen == 0)
	{
		inp -> data = (TYPE*) calloc (newmemlen, sizeof(TYPE));
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
	//check (pointer_valid (inp))
	
	free (inp -> data);
	inp -> datalen = 0;
	inp -> memlen  = 0;
	
	arrays_count --;
	
	return 1;
}

int find_element(struct array* inp, TYPE element_to_be_found)
{
    check (pointer_valid (inp))
    
    int first = 0;
    int last = (inp -> datalen) - 1;
    int middle = (first+last)/2;
    
    while (first <= last)
    {
        if (inp -> data [middle] < element_to_be_found) 
            first = middle + 1;
            
        else if (inp -> data[middle] == element_to_be_found) 
        {
            printf("%d found at location %d.\n", element_to_be_found, middle);
            break;
        }
        
        else last = middle - 1;
 
      middle = (first + last)/2;
    }
    
    if (first > last) 
        fprintf (stderr, ERRORS [ELEMENT_NOT_FOUND], element_to_be_found);  
    
    return 1;
}

int add_element (struct array* inp, TYPE new_element)
{
    check (pointer_valid (inp))
	
	int success = 1;
	
	if (inp -> datalen + 1 >= inp -> memlen)
	{
		success = change_memsz (inp, inp -> memlen + MEM_STEP);
	}
	
	if (success == 1)
	{
	    inp -> datalen ++;        
	
	    int i = inp->datalen;
	    while ((i > 0) && (new_element < inp -> data [i - 1]))
        {   
            inp -> data [i] = inp-> data [i - 1];
            i = i - 1;
        }
    
        inp -> data [i] = new_element;
    }
    
    return success;
    
}

int remove_element (struct array* inp, int pos)
{
   check (pointer_valid (inp))
    
   for (int i = pos; i < inp -> datalen; i++) 
   {
       inp -> data [i] = inp -> data [i+1];
   }
   inp -> datalen--;        
        
   return 1;
}

int change_element (struct array* inp, int ind, TYPE new_element)           
{
	check (pointer_valid (inp))
	if (ind >= inp -> memlen)
	{
		printf (ERRORS [WRITE_TO_UNALLOCATED_MEMORY], ind, inp -> datalen);
		return 0;
	}
		
	else 	
	{
		inp -> data [ind] = new_element;
		return 1;
	}
}

int get_datalen (struct array* inp)
{
	check (pointer_valid (inp))
	
	return inp -> datalen;
}

int get_memlen (struct array* inp)
{
	check (pointer_valid (inp))
	
	return inp -> memlen;
}

int print_element (struct array* inp, int ind)
{
	check (pointer_valid (inp))
	
	if (ind >= inp -> datalen)
	{
		printf (ERRORS [GARBAGE_READ], ind, inp -> datalen);
		
		return 0;
	}
	
	printf ("%i", inp -> data [ind]);
	
	return 1;
}

int print_array (struct array* inp)
{
	check (pointer_valid (inp))
	
	int i = 0;
	
	for (; i < inp -> datalen; i ++)
	{
		print_element (inp, i);
		printf (" ");
	}
	
	printf ("\n");
	
	return 1;
}

int verbose_full_print (struct array* inp)
{
	check (pointer_valid (inp))
	
	printf ("---------------------------------------------------------------\n");
	printf ("Printing data about obj at %x: \nAllocated memory %i bytes (for %i elements), used %i b, %i el.\n",
		    /*(unsigned int)*/ inp, (inp -> memlen) * sizeof (TYPE), inp -> memlen, (inp -> datalen) * sizeof (TYPE), 
		    inp -> datalen);
	printf ("Printing data in the array:\n");
	print_array (inp);
	
	return 1;
}
