#ifndef ARRAYBAG_HPP
#define ARRAYBAG_HPP

#include "bag.hpp"

class ArrayBag : virtual public Bag
{
	protected:
		int *data;
		int size;
	public:
		ArrayBag();
		ArrayBag(const ArrayBag &other);
		ArrayBag &operator=(const ArrayBag &other);
		virtual ~ArrayBag();

		virtual void insert(int val);
		virtual void insert(int *array, int size);
		virtual void print() const ;
		virtual void clear();
};


#endif