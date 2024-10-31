#pragma once

#include <gtest/gtest.h>

template<typename T>
class MyVector {
private:
    T* data;          // Указатель на массив элементов
    size_t capacity;  // Вместимость массива
    size_t size;      // Текущий размер

public:
    // Конструктор
    // Конструктор
    MyVector() : data(nullptr), capacity(0), size(0) {}

    // Копирующий конструктор
    MyVector(const MyVector& other) : data(nullptr), capacity(other.capacity), size(other.size) {
        if (capacity > 0) {
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i]; // Копируем элементы
            }
        }
    }

    // Оператор перемещения
    MyVector(MyVector&& other) noexcept 
        : data(other.data), capacity(other.capacity), size(other.size) {
        other.data = nullptr; // Указываем на nullptr, чтобы предотвратить двойное освобождение
        other.capacity = 0;
        other.size = 0;
    }

    // Оператор присваивания
    MyVector& operator=(const MyVector& other) {
        if (this != &other) { // Проверяем на самоприсваивание
            delete[] data; // Освобождаем старые данные
            capacity = other.capacity;
            size = other.size;
            if (capacity > 0) {
                data = new T[capacity];
                for (size_t i = 0; i < size; ++i) {
                    data[i] = other.data[i]; // Копируем элементы
                }
            } else {
                data = nullptr; // Если capacity == 0
            }
        }
        return *this;
    }

    // Деструктор
    ~MyVector() {
        delete[] data;
    }

    // Метод для изменения размера
    void resize(size_t new_capacity) {
        if (new_capacity == capacity) return; // Если новый размер равен текущему, ничего не делаем
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i]; // Копируем старые данные
        }
        delete[] data; // Освобождаем старый массив
        data = new_data; // Указываем на новый массив
        capacity = new_capacity; // Обновляем вместимость
    }

    // Метод для добавления элемента
    void push_back(const T& value) {
        if (size >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2); // Увеличиваем размер
        }
        data[size++] = value; // Добавляем элемент
    }

    // Метод для получения размера
    size_t get_size() const {
        return size;
    }

    // Метод для доступа к элементам
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