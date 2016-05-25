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
};
