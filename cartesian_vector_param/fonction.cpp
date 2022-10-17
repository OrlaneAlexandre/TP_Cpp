#include <iostream>
#include "config.h"
#include "vector.hh"
using namespace std; 

Vector::Vector(initializer_list<value> v)
{
        if (v.size() != NDIM)
         {
             runtime_error("taille incorecte");
         }
        auto i = v.begin();
        for (int j = 0; j < NDIM; j++)
        {
            this->membre[j] = *(i + j);
        }
}

Vector &Vector::operator+=(const Vector& rhs)
{
	Vector V = Vector{};
	for (int i = 0; i < NDIM; i++)
	{
		V.membre[i] = this->membre[i] + rhs.membre[i];
	}
	return V;
}

Vector& Vector::operator-=(const Vector& rhs)
{
	Vector V = Vector{};
	for (int i = 0; i < NDIM; i++)
	{
		V.membre[i] = this->membre[i] - rhs.membre[i];
	}
	return V;
}

Vector& Vector::operator*=(const value v)
{
	Vector V = Vector{};
	for (int i = 0; i < NDIM; i++)
	{
		V.membre[i] = this->membre[i] * v;
	}
	return V;
}

Vector& Vector::operator*(const value v)
{
	Vector V = Vector{};
	for (int i = 0; i < NDIM; i++)
	{
		V.membre[i] = this->membre[i] * v;
	}
	return V;
}

Vector& Vector::operator+=(const value v)
{
	Vector V = Vector{};
	for (int i = 0; i < NDIM; i++)
	{
		V.membre[i] = this->membre[i] + v;
	}
	return V;
}

Vector& Vector::operator+(const Vector& rhs)
{
	Vector V = Vector{};
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
	out << '{ ';
	for (int i = 0; i < NDIM; i++)
	{
		out << V[i];
	}
	out << '}';
	return out;
}
