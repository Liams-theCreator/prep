#ifndef TREEBAG_HPP
#define TREEBAG_HPP

#include "bag.hpp"

class TreeBag : public Bag
{
	protected:
		struct node 
		{
			node *l;
			node *r;
			int val;
		};
		node *tree;
	private:
		void destroy_tree(node *n);
		void print_node(const node *n) const ;
		node *copy_node(const node *n);
	public:
		TreeBag();
		TreeBag(const TreeBag &other);
		TreeBag &operator=(const TreeBag &other);
		virtual ~TreeBag();

		virtual void insert(int val);
		virtual void insert(int *array, int size);
		virtual void print() const ;
		virtual void clear();
};

#endif