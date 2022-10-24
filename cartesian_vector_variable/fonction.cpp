#include "vector.hh"
#include "config.h"

using namespace std;

Vector::Vector(size_t T)
{
    this->membre = make_unique<value[]>(T);
    this->taille = T;

    for (int i = 0; i < T; i++) {
        this->membre[i] = 0;
    }
}

Vector::Vector(initializer_list<value> v)
{
    size_t T = v.size();
    auto* p = v.begin();

    this->membre = make_unique<value[]>(T);
    this->taille = T;

    for (int i = 0; i < T; i++) {
        this->membre[i] = *(p + i);
    }
}

size_t Vector::size() const
{
    return this->taille;
}


Vector& Vector::operator+=(const Vector& rhs)
{
    if (this->taille != rhs.taille)
    {
        throw runtime_error("Incompatible size");
    }

    for (int i = 0; i < this->taille; i++) 
    {
        this->membre[i] += rhs.membre[i];
    }
    return *this;
}


Vector& Vector::operator-=(const Vector& rhs)
{
    if (this->taille != rhs.taille)
    {
        throw runtime_error("Incompatible size");
    }

    for (int i = 0; i < this->taille; i++)
    {
        this->membre[i] -= rhs.membre[i];
    }
    return *this;
}


Vector& Vector::operator+=(value v)
{
    for (int i = 0; i < this->taille; i++)
    {
        this->membre[i] -= v;
    }
    return *this;
}

Vector& Vector::operator*=(value v)
{
    for (int i = 0; i < this->taille; i++)
    {
        this->membre[i] *= v;
    }
    return *this;
}


Vector Vector::operator+(const Vector& rhs) const
{
    if (this->taille != rhs.taille)
    {
        throw runtime_error("Incompatible size");
    }

    Vector V = Vector(this->taille);
    for (int i = 0; i < this->taille; i++) 
    {
        V.membre[i] = this->membre[i] + rhs.membre[i];
    }
    return V;
}

Vector Vector::operator+(value v) const
{
    Vector V = Vector(this->taille);
    for (int i = 0; i < this->taille; i++)
    {
        V.membre[i] = this->membre[i] + v;
    }
    return V;
}

value Vector::operator*(const Vector& rhs) const
{
    if (this->taille != rhs.taille)
    {
        throw runtime_error("Incompatible size");
    }

    value V = 0;
    for (int i = 0; i < this->taille; i++)
    {
        V += this->membre[i] * rhs.membre[i];
    }
    return V;
}


Vector Vector::operator*(value v) const
{
    Vector V = Vector(this->taille);
    for (int i = 0; i < this->taille; i++)
    {
        V.membre[i] = this->membre[i] * v;
    }
    return V;
}

value& Vector::operator[](size_t idx)
{
    if (idx > this->taille)
    {
        throw std::runtime_error("Incorrect index");
    }
    return this->membre[idx];
}

value Vector::operator[](size_t idx) const
{
    if (idx > this->taille)
    {
        throw std::runtime_error("Incorrect index");
    }
    return this->membre[idx];
}

Vector operator*(const value& s, const Vector& v)
{
    size_t T = v.size();
    Vector V = Vector(T);
    for (int i = 0; i < T; i++) 
    {
        V[i] = s * v[i];
    }
    return V;

}

Vector operator+(const value& s, const Vector& v)
{
    size_t T = v.size();
    Vector V = Vector(T);
    for (int i = 0; i < T; i++) 
    {
        V[i] = s + v[i];
    }
    return V;
}

ostream& operator<<(ostream& out, const Vector& v)
{
    size_t T = v.size();
    out << '{';
    out << v[0];
    for (int i = 1; i < T; i++)
    {
        out << ',';
        out << v[i];
    }
    out << '}';
    return out;
}

