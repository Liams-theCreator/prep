#ifndef SEARCHABLEBAG_HPP
#define SEARCHABLEBAG_HPP

#include "bag.hpp"

class searchable_bag : public Bag 
{
    public:
        virtual bool has(int val) const = 0;
        virtual ~searchable_bag() {}
};

#endif