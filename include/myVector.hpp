#pragma once

#include <gtest/gtest.h>
#include <stdexcept> 

template<typename T>
class MyVector {
private:
    T* data;          
    size_t capacity;  
    size_t size;      

public:
    MyVector() : data(nullptr), capacity(0), size(0) {}

    MyVector(const MyVector& other) : data(nullptr), capacity(other.capacity), size(other.size) {
        if (capacity > 0) {
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) { 
                data[i] = other.data[i]; 
            }
        }
    }
    
    MyVector(MyVector&& other) noexcept 
        : data(other.data), capacity(other.capacity), size(other.size) {
        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) { 
            delete[] data; 
            capacity = other.capacity;
            size = other.size;
            if (capacity > 0) {
                data = new T[capacity];
                for (size_t i = 0; i < size; ++i) {
                    data[i] = other.data[i]; 
                }
            } 
            else {
                data = nullptr; 
            }
        }
        return *this;
    }

    ~MyVector() {
        delete[] data;
    }

    void resize(size_t new_capacity) {
        if (new_capacity == capacity) return; 
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size && i < new_capacity; ++i) { 
            new_data[i] = data[i]; 
        }
        delete[] data; 
        data = new_data; 
        capacity = new_capacity; 
        size = (size < new_capacity) ? size : new_capacity;
    }

    void push_back(const T& value) {
        if (size >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value; 
    }

    size_t get_size() const {
        return size;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
};
