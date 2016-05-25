#include "sorted_array_2.h"

template <class TYPE> class data_structure
{
	public:
	
	TYPE* data;
	int memlen;
	int datalen;
	
	 data_structure () { }
	~data_structure () { }
	
	virtual int get_datalen ()
	{
		return datalen;
	}

	int get_memlen ()
	{
		return memlen;
	}
	
	virtual int add_element (TYPE new_element) { }
	
	int change_memsz (TYPE newmemlen)
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
};

template <class TYPE> class alternative_array: public data_structure <int>
{
	private:
	
	std::vector<TYPE> vec;
	
	public:
	
	alternative_array (): data_structure () {}
	~alternative_array () {}
	
	int init_array ()
	{	
		arrays_count ++;
		
		return 1;
	}

	int delete_array ()
	{
		return 1;
	}
	
	int get_datalen ()
	{
		vec.size ();
	}
	
	int add_element (TYPE new_element)
	{
		return vec.push_back (new_element);
	}

	int remove_element_from_end ()
	{
		vec.pop_back ();
		
		return 1;
	}
};

template <class TYPE> class array: public data_structure <int>
{
	private:
	
	public:
	
	 array (): data_structure () {}
	~array () {}
	
	int init_array ()
	{
		data    = 0;
		memlen  = 0;
		datalen = 0;
		
		int suc = change_memsz (DEF_LEN);
		
		arrays_count ++;
		
		return suc;
	}

	int delete_array ()
	{
		free (data);
		datalen = 0;
		memlen  = 0;
	
		arrays_count --;
		
		return 1;
	}
	
	int add_element (TYPE new_element)
	{
		return add_element_to_end (new_element);
	}
	
	int add_element_to_end (TYPE new_element)
	{
		int success = 1;
	
		if (datalen + 1 >= memlen)
		{
			success = change_memsz (memlen + MEM_STEP);
		}
	
		if (success == 1) data [datalen ++] = new_element;
		//else fprintf (stderr, ERRORS [ELEMENT_NOT_ADDED]);
	
		return success;
	}
	
	int remove_element_from_end ()
	{
		datalen --;
	
		return 1;
	}

	int change_element (int ind, TYPE new_element)
	{
		data [ind] = new_element;
		return 1;
	}
};
