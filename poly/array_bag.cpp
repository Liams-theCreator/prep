#include "array_bag.hpp"
#include <iostream>
#include <cstddef>

ArrayBag::ArrayBag(): data(0), size(0) {}

ArrayBag::ArrayBag(const ArrayBag &other): data(0), size(0)
{
    if (other.size > 0)
    {
        data = new int[other.size];
        size = other.size;
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }
}
ArrayBag &ArrayBag::operator=(const ArrayBag &other)
{
    if (this != &other)
    {
        clear();
        if (other.size > 0)
        {
            data = new int[other.size];
            size = other.size;
            for (int i = 0; i < size; i++)
                data[i] = other.data[i];
        }
    }
    return *this;
}

ArrayBag::~ArrayBag()
{
    clear();
}

void ArrayBag::insert(int val)
{
    int *tmp = new int[size + 1];
    for (int i = 0; i < size; i++)
        tmp[i] = data[i];
    tmp[size] = val;
    delete[] data;
    data = tmp;
    size++;
}

void ArrayBag::insert(int *array, int size)
{
    if (!array || size <= 0)
        return ;
    for (int i = 0; i < size ; i++)
        insert(array[i]);
}

void ArrayBag::print() const
{
    for (int i = 0; i < size; i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;
}

void ArrayBag::clear()
{
    if (data)
        delete[] data;
    data = NULL;
    size = 0;
}