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

TreeBag::~TreeBag()
{
    clear();
}


node *TreeBag::copy_node(const node *n)
{
    if (!n)
        return NULL;
    node *copy = new node;
    copy->value = n->value;
    copy->l = copy_node(n->l);
    copy->r = copy_node(n->r);
    return copy;
}

void TreeBag::insert(int val)
{
    node **current = &tree;
    while (*current)
    {
        if (val < (*current)->value)
            current = &(*current)->l;
        else
            current = &(*current)->r;
    }
    *current = new node;
    (*current)->value = val;
    (*current)->l = NULL;
    (*current)->r = NULL;
}
void TreeBag::insert(int *array, int size)
{
    if (!array || size <= 0)
        return ;
    for (int i = 0; i < size; i++)
        insert(array[i]);
}

void TreeBag::print() const
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

void TreeBag::clear()
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