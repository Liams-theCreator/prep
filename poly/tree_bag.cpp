#include "tree_bag.hpp"

TreeBag::TreeBag(): tree(0) {}

TreeBag::TreeBag(const TreeBag &other): tree(0)
{
    tree = copy_node(other.tree);
}

TreeBag &TreeBag::operator=(const TreeBag &other)
{
    if (this != &other)
    {
        clear();
        tree = copy_node(other.tree);
    }
    return *this;
}

virtual TreeBag::~TreeBag()
{
    clear();
}


void TreeBag::copy_node(const node *n);
virtual void TreeBag::insert(int val);
virtual void TreeBag::insert(int *array, int size);

virtual void TreeBag::print() const
{
    print_node(tree);
    std::cout << std::endl;
}

void TreeBag::print_node(const node *n) const
{
    if (!n)
        return ;
    print_node(n->l);
    std::cout << n->value << " ";
    print_node(n->r);
}

virtual void TreeBag::clear()
{
    destroy_tree(tree);
    tree = NULL;
}

void TreeBag::destroy_tree(node *n)
{
    if (!n)
        return ;
    destroy_tree(n->l);
    destroy_tree(n->r);
    delete n;
}