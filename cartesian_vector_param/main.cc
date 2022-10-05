// vector-test.cc
#include <iostream>

#include "vector.hh"
#include "fonction.cpp"
#include <vector>
#include <string.h> //strcmp
using namespace std;

#if NDIM == 2
void test1()
{
    auto u = Vector{};
    // This needs an constructor accepting a std::initializer_list
    auto v = Vector{ 4, 7 };
    auto t = Vector{ -1, 6 };

    cout << u + v << '\n'; // {4,7}
    u += Vector{ 1, 8 };
    cout << u << '\n'; // {1,8}
    t -= u;
    cout << t << '\n'; // {-2,-2}
    cout << t * 3 << '\n'; // {-6,-6}
    cout << u * v << '\n'; // 60

}
#elif NDIM == 3
void test1()
{
    auto u = Vector{};
    // This needs an constructor accepting a std::initializer_list
    auto v = Vector{ 4, 7, -1 };
    auto t = Vector{ -1, 6, 77 };

    cout << u + v << '\n'; // {4,7,-1}
    u += Vector{ 1, 8, -11 };
    cout << u << '\n'; // {1,8,-11}
    t -= u;
    cout << t << '\n'; // {-2,-2,88}
    cout << t * 3 << '\n'; // {-6,-6,264}
    cout << u * v << '\n'; // 71
}
#else
void test1()
{
    auto u = Vector{};
    for (size_t i = 0; i < NDIM; ++i)
        u[i] = i;
    cout << u;
    cout.put('\n');
}
#endif

vector<Vector>
generate(size_t n)
{
    auto v = vector<Vector>(n);
    // Set some values
    for (size_t i = 0; i < NDIM; ++i)
        {
            for (size_t j = 0; j < n; ++j)
                {
                    auto& vv = v[j]; // Reference to one of your Vectors
                    vv[i] = (value) i+j;
                }
        }
    return v;
}

// Takes the number of Vectors used as an argument
void testAdd(size_t n)
{
    auto v = generate(n);
    // Add to each Vector his right neighbour
    for (size_t i = 1; i < n; ++i)
        v[i-1] += v[i];
    // Sum them up
    auto sum = Vector(); // Expected to be all zeros
    for (const auto& other : v)
        sum = sum + other;
    // Print for verif
    cout << sum << '\n';
}

// Takes as input the number of vectors
// As well a as a list of actions to perform
// scaling and offset will use two arguments from argv,
// all others will be performed on two neighbouring elements
// In the end a pairwise dot-product is calculated and summed up for all
void testVar(size_t n, int argc, char* argv[])
{
    if (n&1)
        throw runtime_error("Need an even number of elements.");

    auto v = generate(n);
    for (int idx = 0; idx < argc; ++idx)
        {
            if (strcmp(argv[idx], "add") == 0 )
                {
                    for (size_t i = 1; i < n; ++i)
                        v[i-1] += v[i];
                }
            else if (strcmp(argv[idx], "scale") == 0)
                {
                    ++idx;
                    auto s = (value) std::atoll(argv[idx]);
                    for (auto& vv : v)
                        vv *= s;
                }
            else if (strcmp(argv[idx], "offset") == 0)
                {
                    ++idx;
                    auto s = (value) std::atoll(argv[idx]);
                    for (auto& vv : v)
                        vv += s;
                }

        }
    value sum = 0;
    for (size_t i = 1; i < n; i += 2)
        sum += v[i-1]*v[i];
    cout << sum;
    cout.put('\n');
}




int main(int argc, char* argv[])
{
    if (argc <= 2)
        throw runtime_error("Expects: first arg, number of elements, other args, instructions to run");
    size_t n_elem = atol(argv[1]);
    if (strcmp(argv[2], "test1") == 0)
        test1();
    else if (strcmp(argv[2], "testAdd") == 0)
        testAdd(n_elem);
    else
        testVar(n_elem, argc - 2, &(argv[2]));

    return 0;
}
