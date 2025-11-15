#pragma once

#include <algorithm>
#include <memory>
#include <memory_resource>
#include <cassert>
#include <cstddef>

template<typename T, class Allocator = std::allocator<T>>
class DynamicArray {
private:
    Allocator allocator;
    T* data;
    std::size_t capacity;
    std::size_t size;

    void resize() {
        std::size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
        T* newData = allocator.allocate(newCapacity);
        for (size_t i = 0; i < size; ++i) {
            std::allocator_traits<Allocator>::construct(allocator, newData + i, std::move(data[i]));
            std::allocator_traits<Allocator>::destroy(allocator, data + i);
        }
        if(data) allocator.deallocate(data, capacity);
        data = newData;
        capacity = newCapacity;
    }


public:
    using value_type = T;
    using reference = T&;
    using pointer = T*;

    DynamicArray() : data(nullptr), capacity(0), size(0) {}

    explicit DynamicArray(const Allocator& alloc) : allocator(alloc), data(nullptr), capacity(0), size(0) {}

    ~DynamicArray() {
        clear();
        if (data) allocator.deallocate(data, capacity);
    }

    template<typename... Args>
    reference push_back(Args&&... args) {
        if (size >= capacity) resize();
        std::allocator_traits<Allocator>::construct(allocator, data + size, std::forward<Args>(args)...);
        return data[size++];
    }

    void pop_back() {
        assert(size > 0);
        std::allocator_traits<Allocator>::destroy(allocator, data + (size - 1));
        --size;
    }

    void clear() {
        while (size > 0) pop_back();
    }

    reference operator[](std::size_t idx) { assert(idx < size); return data[idx]; }
    const reference operator[](std::size_t idx) const { assert(idx < size); return data[idx]; }
    std::size_t getSize() const { return size; }
    bool empty() const { return size == 0; }

    class iterator {
        T* ptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        iterator(T* p) : ptr(p) {}
        T& operator*() { return *ptr; }
        iterator& operator++() { ++ptr; return *this; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }
    };
    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + size); }
};