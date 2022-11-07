#pragma once
#include <functional>
template <typename T>
ref class List
{
public:
    virtual int get_size() = 0;

    virtual bool is_empty() = 0;

    virtual bool is_not_empty() {
        return !is_empty();
    }

    virtual void add(T* value) = 0;

    virtual bool insert(int index, T* value) = 0;

    virtual T* get(int index) = 0;

    virtual T* remove(int index) = 0;
};

