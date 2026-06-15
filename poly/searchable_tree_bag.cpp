#include "searchable_tree_bag.hpp"

SearchableTreeBag::SearchableTreeBag(): TreeBag() {}

SearchableTreeBag::SearchableTreeBag(const SearchableTreeBag &other): TreeBag(other) {}

SearchableArrayBag &SearchableTreeBag::operator=(const SearchableTreeBag &other)
{
    if (this != &other)
        TreeBag::operator=(other);
    return *this;
}

virtual SearchableTreeBag::~SearchableTreeBag() {}

virtual bool SearchableTreeBag::had(int val) const
{
    node *current = tree;
    while (current)
    {
        if (current->value == val)
            return true;
        else if (val < current->value)
            current = current->l;
        else
            current = current->r;
    }
    return false;
}