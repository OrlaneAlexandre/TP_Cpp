#include <iostream>
#include "config.h"
#include "vector.hh"
using namespace std; 

Vector::Vector()
{
        for (int j = 0; j < NDIM; j++)
        {
            this->membre[j] = 0;
        }
}

Vector::Vector(initializer_list<value> v)
{
        auto p = data();
        for (int j = 0; j < NDIM; j++)
        {
            this->membre[j] = p[j];
        }
}

Vector &Vector::operator+=(const Vector& rhs)
{
	for (int i = 0; i < NDIM; i++)
	{
		this->membre[i] += rhs.membre[i];
	}
	return *this;
}

Vector& Vector::operator-=(const Vector& rhs)
{
	for (int i = 0; i < NDIM; i++)
	{
		this->membre[i] -= rhs.membre[i];
	}
	return *this;
}

Vector& Vector::operator*=(const value v)
{
	for (int i = 0; i < NDIM; i++)
	{
		this->membre[i] *= v;
	}
	return *this;
}

Vector& Vector::operator*(const value v)
{
	auto V = Vector{};
	for (int i = 0; i < NDIM; i++)
	{
		V.membre[i] = this->membre[i] * v;
	}
	return V;
}

Vector& Vector::operator+=(const value v)
{
	for (int i = 0; i < NDIM; i++)
	{
		this->membre[i] += v;
	}
	return *this;
}

Vector& Vector::operator+(const Vector& rhs)
{
	auto V = Vector{};
	for (int i = 0; i < NDIM; i++)
	{
		V.membre[i] = this->membre[i] + rhs.membre[i];
	}
	return V;
}

value& Vector::operator*(const Vector& rhs)
{
	value somme = 0;
	for (int i = 0; i < NDIM; i++)
	{
		somme += this->membre[i] * rhs.membre[i];
	}
	return somme ;
}

value& Vector::operator[](const int v)
{
	return this->membre[v];
}

ostream& operator<<(ostream& out, Vector V)
{
	out << '{';
	out << v[0];
	for (int i = 1; i < NDIM; i++)
	{
		out << ',';
		out << V[i];
	}
	out << '}';
	return out;
}
