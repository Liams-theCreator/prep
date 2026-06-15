#ifndef BAG_HPP
#define BAG_HPP

class Bag
{
	public:
		virtual ~Bag() {};

		virtual void insert(int val) = 0;
		virtual void insert(int *array, int size) = 0;
		virtual void print() const = 0;
		virtual void clear() = 0;
};

#endif