#include "MyInt.hpp"
#include <ctime>
#include <iostream>
#include <initializer_list>

#ifndef ARRAY_HPP
#define ARRAY_HPP

namespace cs540
{

class Array
{
    friend std::ostream &operator<<(std::ostream &os, const Array &obj)
    {
        int i;
        for(i=0; i<obj.arr_size; i++)
        {
            if(i<obj.arr_size-1) std::cout << obj.arr[i] << ", ";
            else std::cout << obj.arr[i];
        }
        return os;
    };
public:
    int arr_size;
    MyInt *arr;
    Array();
    Array(std::initializer_list<MyInt> in);
    Array(const Array &obj);
    Array(Array &&obj);
    Array &operator=(const Array &obj);
    Array &operator=(Array &&obj);
    ~Array();
    static void move_performance_test();
};

Array::Array()
{
    arr_size = 0;
    arr = nullptr;
}

Array::Array(std::initializer_list<MyInt> in)
{
    int i = 0;
    arr_size = in.size();
    arr = new MyInt[arr_size];
    std::initializer_list<MyInt>::iterator it;
    for(it = in.begin(); it!=in.end(); ++it)
    {
        arr[i] = *it;
        i++;
    }
}

Array::Array(const Array &obj)
{
    int i;
    arr = new MyInt[obj.arr_size];
    for(i=0; i<obj.arr_size; i++)
    {
        MyInt mi(obj.arr[i]);
        arr[i] = mi;
        MyInt::count++;
    }
    arr_size = obj.arr_size;
}

Array::Array(Array &&obj)
{
    arr_size = obj.arr_size;
    arr = obj.arr;
    obj.arr_size = 0;
    obj.arr = nullptr;
}


Array &Array::operator=(const Array &obj)
{
    if(arr != nullptr) delete [] arr;
    int i;
    arr = new MyInt[obj.arr_size];
    for(i=0; i<obj.arr_size; i++)
    {
        MyInt mi(obj.arr[i]);
        arr[i] = mi;
        MyInt::count++;
    }
    arr_size = obj.arr_size;
    return *this;
}

Array &Array::operator=(Array &&obj)
{
    arr_size = obj.arr_size;
    arr = obj.arr;
    obj.arr_size = 0;
    obj.arr = nullptr;
    return *this;
}

Array::~Array()
{
    if(arr != nullptr) delete [] arr;
}

void Array::move_performance_test()
{
    std::cout << "\nPerformance test (1000000 Copy/Move Constructor calls each):\n";

    int i;
    double elapsed_secs;
    std::clock_t begin = clock();
    for(i=0; i<1000000; i++)
    {
        cs540::Array test_arr{1, 2, 3};
        cs540::Array cpy_arr{test_arr};
    }
    std::clock_t end = clock();
    elapsed_secs = double(end - begin) / double(CLOCKS_PER_SEC)*1000;
    std::cout << "Copy Constructor Elapsed Time: " << elapsed_secs << " msecs" << std::endl;

    begin = clock();
    for(i=0; i<1000000; i++)
    {
        cs540::Array test_arr{1, 2, 3};
        cs540::Array cpy_arr{std::move(test_arr)};
    }
    end = clock();
    elapsed_secs = double(end - begin) / double(CLOCKS_PER_SEC)*1000;
    std::cout << "Move Constructor Elapsed Time: " << elapsed_secs << " msecs" << std::endl;
}

#endif // ARRAY_HPP

}
