#include "array_bag.hpp"

ArrayBag::ArrayBag(): data(0), size(0) {}

ArrayBag(const ArrayBag &other)
{
    if (other.size > 0)
    {
        data = new int[other.size];
        size = other.size;
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }
}
ArrayBag &operator=(const ArrayBag &other)
{
    if (this != other)
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

virtual ArrayBag::~ArrayBag()
{
    clear();
}

virtual void TreeBag::insert(int val)
{
    int *tmp = new int[size + 1];
    for (int i = 0; i < size; i++)
        tmp[i] = data[i];
    tmp[size] = val;
    delete[] data;
    data = tmp;
    size++;
}

virtual void TreeBag::insert(int *array, int size)
{
    if (!array || size <= 0)
        return ;
    for (int i = 0; i < size ; i++)
        insert(data[i]);
}

virtual void TreeBag::print() const
{
    for (int i = 0; i < size; i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;
}

virtual void TreeBag::clear()
{
    if (data)
        delete[] data;
    data = NULL;
    size = 0;
}