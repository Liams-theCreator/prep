#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set
{
    private:
        searchable_bag *bag;
    public:
        set();
        set(searchable_bag &b);
        set(const set &other);
        set &operator=(const set &other);
        ~set();

        void insert(int val);
        void insert(int *array, int size);
        void print() const;
        void clear();
        
        void has(int val) const;

};

#endif