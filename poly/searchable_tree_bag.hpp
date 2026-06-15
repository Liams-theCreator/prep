#ifndef SEARCHABLETREEBAG_HPP
#define SEARCHABLETREEBAG_HPP

#include "array_bag.hpp"
#include "searchable_bag.hpp"

class SearchableTreeBag : public TreeBag, public searchable_bag
{
    public:
        SearchableTreeBag();
        SearchableTreeBag(const SearchableTreeBag &other);
        SearchableArrayBag &operator=(const SearchableTreeBag &other);
        virtual ~SearchableTreeBag();

        virtual bool had(int val) const;
};

#endif