#include "vect2.hpp"

vect2::vect2(): x(0), y(0) {}
vect2::vect2(int _x, int _y): x(_x), y(_y) {}
vect2::vect2(const vect2 &other): x(other.x), y(other.y) {}
vect2 &vect2::operator=(const vect2 &other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
    }
    return *this;
}
vect2::~vect2() {}


int &vect2::operator[](int index)
{
    if (index == 0)
        return x;
    return y;
}
const int &vect2::operator[](int index) const
{
    if (index == 0)
        return x;
    return y;
}


vect2 vect2::operator+(const vect2 &other) const
{
    return vect2(x + other.x, y + other.y);
}
vect2 vect2::operator-(const vect2 &other) const
{
    return vect2(x - other.x, y - other.y);
}
vect2 vect2::operator*(int scalar) const
{
    return vect2(x * scalar, y * scalar);
}
vect2 vect2::operator-() const
{
    return vect2(-x, -y);
}


vect2 &vect2::operator+=(const vect2 &other)
{
    x += other.x;
    y += other.y;
    return *this;
}
vect2 &vect2::operator-=(const vect2 &other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}
vect2 &vect2::operator*=(int scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}


vect2 &vect2::operator++()
{
    ++x;
    ++y;
    return *this;
}
vect2 vect2::operator++(int)
{
    vect2 tmp(*this);
    ++(*this);
    return tmp;
}
vect2 &vect2::operator--()
{
    --x;
    --y;
    return *this;
}
vect2 vect2::operator--(int)
{
    vect2 tmp(*this);
    --(*this);
    return tmp;
}


bool vect2::operator!=(const vect2 &other) const
{
    return !(*this == other);
}
bool vect2::operator==(const vect2 &other) const
{
    return (x == other.x && y == other.y);
}


vect2 operator*(int scalar, const vect2 &other)
{
    return other * scalar;
}
std::ostream &operator<<(std::ostream &os, const vect2 &other)
{
    os << "{" << other[0] << ", " << other[1] << "}";
    return os;
}