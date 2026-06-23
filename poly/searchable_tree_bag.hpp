#ifndef SEARCHABLETREEBAG_HPP
#define SEARCHABLETREEBAG_HPP

#include "tree_bag.hpp"
#include "searchable_bag.hpp"

class SearchableTreeBag: public TreeBag, public searchable_bag
{
    public:
        SearchableTreeBag();
        SearchableTreeBag(const SearchableTreeBag &other);
        SearchableTreeBag &operator=(const SearchableTreeBag &other);
        ~SearchableTreeBag();

        virtual bool has(int val) const;
};

#endif