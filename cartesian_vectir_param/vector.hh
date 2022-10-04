#pragma once

#include <ostream>

#include <initializer_list>

#include "config.h"
using namespace std;

class Vector
{
public:
// DO NOT CHANGE THIS
    Vector(const Vector&) = default;
    Vector& operator=(const Vector&) = default;
    ~Vector() = default;
//

// Add suitable constructors
    Vector() = default;
    Vector(initializer_list<value> v)
    {
        auto* p = data(v);
        v.size() == NDIM;
    }
    // possibly more

// Public Member functions here
    Vector& operator+=(const Vector& rhs);
    Vector& operator-=(const Vector& rhs);
    Vector& operator*=(const value v);
    Vector& operator*(const value v);
    Vector& operator+=(const value v);
    Vector& operator+(const Vector& rhs);
    value & operator*(const Vector& rhs);
    value & operator[](const int v);



private:
// Private Member functions here
    value membre[NDIM];
// Member variables are ALWAYS private, and they go here
};

// Nonmember function operators go here
ostream& operator<<(ostream& out, Vector V);