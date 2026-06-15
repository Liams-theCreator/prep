#include "searchable_array_bag.hpp"

SearchableArrayBag::SearchableArrayBag(): ArrayBag() {}

SearchableArrayBag::SearchableArrayBag(const SearchableArrayBag &other): ArrayBag(other) {}

SearchableArrayBag &SearchableArrayBag::operator=(const SearchableArrayBag &other)
{
    if (this != &other)
        ArrayBag::operator=(other);
    return *this;
}

virtual SearchableArrayBag::~SearchableArrayBag() {}

virtual bool SearchableArrayBag::had(int val) const
{
    for(int i = 0; i < size; i++)
    {
        if (data[i] == val)
            return true;
    }
    return false;
}