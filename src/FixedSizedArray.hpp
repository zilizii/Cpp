#pragma once
#include <initializer_list>
#include <cassert>
#include <algorithm>

template<typename T>
class FixedSizedArray {
private:
    struct iterator {
        using Category   = std::forward_iterator_tag;
        using Distance   = std::ptrdiff_t;
        using value_type = T;
        using Pointer    = T*;
        using Reference  = T&;

        iterator(T* ptr) : mPtr(ptr) {}

        iterator operator++() {
            ++mPtr;
            return *this;
        }

        iterator operator++(T) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Reference operator*() const {
            return *mPtr;
        }

        Pointer operator->() {
            return mPtr;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return lhs.mPtr == rhs.mPtr;
        }
        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return lhs.mPtr != rhs.mPtr;
        }

    private:
        Pointer mPtr;
    };

    T* mData;
    size_t mCapacity;

public:
    FixedSizedArray(int capacity);
    FixedSizedArray(std::initializer_list<T> l);
    ~FixedSizedArray();

    T& operator[](size_t indexOf);
    size_t capacity();
    iterator begin();
    iterator end();
};

template<typename T>
FixedSizedArray<T>::FixedSizedArray(int capacity) : mCapacity(capacity) {
    mData = new T[capacity];
}

template<typename T>
FixedSizedArray<T>::FixedSizedArray(std::initializer_list<T> l) : FixedSizedArray(l.size()) {
    std::copy(l.begin(), l.end(), mData);
}

template<typename T>
FixedSizedArray<T>::~FixedSizedArray() {
    delete[] mData;
}

template<typename T>
T& FixedSizedArray<T>::operator[](size_t indexOf) {
    assert(indexOf < mCapacity);
    return mData[indexOf];
}

template<typename T>
size_t FixedSizedArray<T>::capacity() {
    return mCapacity;
}

template<typename T>
typename FixedSizedArray<T>::iterator FixedSizedArray<T>::begin() {
    return iterator(mData);
}

template<typename T>
typename FixedSizedArray<T>::iterator FixedSizedArray<T>::end() {
    return iterator(mData + mCapacity);
}