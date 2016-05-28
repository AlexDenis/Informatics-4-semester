#include "stdio.h"
#include "malloc.h"
#include "assert.h"
#include <iostream>
#include <exception>
#include <vector>

using namespace std;

#define check(COND) { if (COND) { } else { fprintf (stderr, "Condition '%s' is false!\n", #COND); assert (0); } }

class memexc   		 : public exception { const char * what () const throw () { return "Unable to allocate requested memory.																					\n"; } };
class addexc         : public exception { const char * what () const throw () { return "Element not added.\n"; } };
class unallocmemexc  : public exception { const char * what () const throw () { return "Trying to write to unallocated 																							memory.\n"; } };
class garbagereadexc : public exception { const char * what () const throw () { return "Trying to read garbage from not 																						filled memory.\n"; } };

const int DEF_LEN    = 10;
const int MEM_STEP   = 50;
const int MAX_DATASZ = 301; 

int arrays_count = 0;
const char* OK_EXITING     = "You've deleted all the arrays.\n";
const char* NOT_OK_EXITING = "You've not deleted all the arrays.\n'";

void print_exit_message ()
{
	if (arrays_count == 0) printf ("%s", OK_EXITING);
	else printf ("%s", NOT_OK_EXITING);
}

int pointer_valid (void* inp)
{
	if (inp != 0) return 1;
	else return 0;
}

//------------------------DATA STRUCTURE----------------------------

template <class TYPE> class data_structure
{
	public:
	
	TYPE* data;
	int memlen;
	int datalen;
	
	//data_structure () { }
	//~data_structure () { }
	
	virtual int get_datalen ();
	int get_memlen ();
	virtual int add_element (TYPE new_element) = 0;           // pure virtual function
	int change_memsz (TYPE newmemlen);
};

template <class TYPE>
int data_structure <TYPE> :: get_datalen ()
{
		return datalen;
}

template <class TYPE>	
int data_structure <TYPE> :: get_memlen ()
{
		return memlen;
}

template <class TYPE>
int data_structure <TYPE> :: change_memsz (TYPE newmemlen)
{
	if (memlen == 0)
	{
		check (!pointer_valid (data))
			
		data = (TYPE*) malloc (sizeof (TYPE) * newmemlen);
		memlen = newmemlen;
	}
	
	else
	{
		check (pointer_valid (data))
			
		printf ("reallocating with new mem len %i\n", newmemlen);
		data = (TYPE*) realloc (data, newmemlen * sizeof (TYPE));
		memlen = newmemlen;
	}
	
	return 1;
}

// ------------------ALTERNATIVE ARRAY -------------------------------

template <class TYPE> class alternative_array: public data_structure <TYPE>
{
	private:
	
	std::vector<TYPE> vec;
	
	public:
	
	//alternative_array (): data_structure () {}
	//~alternative_array () {}
	
	int init_array ();
	int delete_array ();
	int get_datalen ();
	int add_element (TYPE new_element);
	int remove_element_from_end ();
};

template <class TYPE>
int alternative_array <TYPE> :: init_array ()
{	
	arrays_count ++;
		
	return 1;
}

template <class TYPE>
int alternative_array <TYPE> :: delete_array ()
{
	return 1;
}

template <class TYPE>
int alternative_array <TYPE> :: get_datalen ()
{
	return vec.size ();
}

template <class TYPE>
int alternative_array <TYPE> ::add_element (TYPE new_element)
{
	return vec.push_back (new_element);
}

template <class TYPE>
int alternative_array <TYPE> ::remove_element_from_end ()
{
	vec.pop_back ();
		
	return 1;
}

//----------ARRAY------------------------------------------------------

template <class TYPE> class array: public data_structure <TYPE>
{
	private:
	
	public:
	
	//array (): data_structure () {}
	//~array () {}
	
	int init_array ();
	int delete_array ();
	int add_element (TYPE new_element);
	int add_element_to_end (TYPE new_element);
	int remove_element_from_end ();
	int change_element (int ind, TYPE new_element);
	int zero_array ();
	int bubble_sort ();
	int print_element (int ind);
	int print_array ();
	int verbose_full_print ();
};

template <class TYPE>
int array <TYPE> :: init_array ()
{
	this->data    = 0;
	this->memlen  = 0;
	this->datalen = 0;
		
	int suc = this->change_memsz (DEF_LEN);
		
	arrays_count ++;
		
	return suc;
}

template <class TYPE>
int array <TYPE> :: delete_array ()
{
	free (this->data);
	this->datalen = 0;
	this->memlen  = 0;
	
	arrays_count --;
		
	return 1;
}

template <class TYPE>
int array <TYPE> :: add_element (TYPE new_element)
{
	return add_element_to_end (new_element);
}

template <class TYPE>
int array <TYPE> :: add_element_to_end (TYPE new_element)
{
	int success = 1;
	
	if (this->datalen + 1 >= this->memlen)
	{
		success = this->change_memsz (this->memlen + MEM_STEP);
	}
	
	if (success == 1) this->data [this->datalen ++] = new_element;
	
	return success;
}

template <class TYPE>
int array <TYPE> :: remove_element_from_end ()
{
	this->datalen --;
	
	return 1;
}

template <class TYPE>
int array <TYPE> :: change_element (int ind, TYPE new_element)
{
	this->data [ind] = new_element;
	return 1;
}

template <class TYPE>
int array <TYPE> :: zero_array ()
{
	int i = 0;
	for (; i < this->datalen; i ++) this->data [i] = 0;
	this->datalen = 0;
	
	return 1;
}

template <class TYPE>
int array <TYPE> :: bubble_sort ()
{
	for (int i = this->datalen; i > 0; i --)
	{
		for (int j = 0; j < i - 1; j ++)
		{
			if (this->data [j] < this->data [j + 1])
			{
				TYPE temp = this->data [j];
				this->data [j] = this->data [j + 1];
				this->data [j + 1] = temp;
			}
		}
	}
	
	int success = 1;

	for (int i = 0; i < this->datalen - 1; i ++)
		if (this->data [i] < this->data [i + 1]) success = 0;
		
	return success;
}

template <class TYPE>
int array <TYPE> :: print_element (int ind)
{
	printf ("%i", this->data [ind]);
	
	return 1;
}

template <class TYPE>
int array <TYPE> :: print_array ()
{
	for (int i = 0; i < this->datalen; i ++)
	{
		print_element (i);
		printf (" ");
	}

	printf ("\n");

	return 1;
}

template <class TYPE>
int array <TYPE> :: verbose_full_print ()
{
	printf ("---------------------------------------------------------------\n");
	printf ("Printing data about obj at %x: \nAllocated memory %i bytes (for %i elements), used %i b, %i el.\n",
		this, (this->memlen) * sizeof (TYPE), this->memlen, (this->datalen) * sizeof (TYPE), this->datalen);
	printf ("Printing data in the array:\n");
	print_array ();
	
	return 1;
}

//-------------------SORTED ARRAY------------------------------------------------------

template <class TYPE> class sorted_array: public array <TYPE>
{
	public:
	
	//sorted_array (): array () { }
	//~sorted_array () { }
	
	int add_element (TYPE new_element);
	int search (TYPE val);
};

template <class TYPE>
int sorted_array <TYPE> :: add_element (TYPE new_element)
{
	this->add_element_to_end (new_element);
	this->bubble_sort ();
}

template <class TYPE>
int sorted_array <TYPE> :: search (TYPE val)
{
	int ind = -1;
		
	for (int i = 0; i < this->datalen; i ++)
		if (this->data [i] == val)
			ind = i;
}
