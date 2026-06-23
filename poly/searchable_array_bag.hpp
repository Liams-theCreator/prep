#ifndef SEARCHABLEARRAYBAG_HPP
#define SEARCHABLEARRAYBAG_HPP

#include "array_bag.hpp"
#include "searchable_bag.hpp"

class SearchableArrayBag: public ArrayBag, public searchable_bag
{
    public:
        SearchableArrayBag();
        SearchableArrayBag(const SearchableArrayBag &other);
        SearchableArrayBag &operator=(const SearchableArrayBag &other);
        ~SearchableArrayBag();

        virtual bool has(int val) const;
};

#endif
