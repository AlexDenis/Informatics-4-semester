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
