#ifndef UNTITLED_POINTEDVECTOR_H
#define UNTITLED_POINTEDVECTOR_H

#include <vector>
#include <stdexcept>

template <class T>
class PointedVector {
    std::vector<T> objects;
    mutable int pointer = 0;
    void normalisePointer() const;

public:
    PointedVector() = default;
    const T& operator[](int index) const;
    const T& get(int index) const;
    const T& getSelected() const;
    const T& first() const;
    const T& last() const;

    int size() const;
    int getPointer() const;
    bool isEmpty() const;

    void insert(int index, T value);
    void add(T value);
    void remove(int index);
    void clear();
    void stepForward(int steps);
    void stepForward();
    void stepBackward(int steps);
    void stepBackward();
    void select(int newPointer);
};








template <class T>
const T& PointedVector<T>::operator[](int index) const {
    return objects[index];
}

template <class T>
const T& PointedVector<T>::get(int index) const {
    if (index < 0) { index = static_cast<int>(objects.size()) + index; }
    if (index < 0 || index >= static_cast<int>(objects.size())) {
        throw std::out_of_range("index out of range");
    }
    return objects[index];
}

template <class T>
const T& PointedVector<T>::getSelected() const {
    if (this->isEmpty()) { throw std::out_of_range("Nothing to select"); }
    this->normalisePointer();
    return objects[this->pointer];
}

template <class T>
const T& PointedVector<T>::first() const {
    if (this->isEmpty()) { throw std::out_of_range("index out of range"); }
    return objects[0];
}

template <class T>
const T& PointedVector<T>::last() const {
    if (this->isEmpty()) { throw std::out_of_range("index out of range"); }
    return objects[objects.size() - 1];
}

template <class T>
int PointedVector<T>::size() const {
    return static_cast<int>(objects.size());
}

template <class T>
int PointedVector<T>::getPointer() const {
    if (this->isEmpty()) { throw std::out_of_range("Nothing to select"); }
    this->normalisePointer();
    return this->pointer;
}

template <class T>
bool PointedVector<T>::isEmpty() const {
    return objects.empty();
}

template <class T>
void PointedVector<T>::insert(int index, T value) {
    if (index < 0) { index = static_cast<int>(objects.size()) + index; }
    if (index < 0 || index > static_cast<int>(objects.size())) {
        throw std::out_of_range("index out of range");
    }
    objects.insert(objects.begin() + index, std::move(value));
}

template <class T>
void PointedVector<T>::add(T value) {
    objects.push_back(std::move(value));
}

template <class T>
void PointedVector<T>::remove(int index) {
    if (index < 0) { index = static_cast<int>(objects.size()) + index; }
    if (index < 0 || index >= static_cast<int>(objects.size())) {
        throw std::out_of_range("index out of range");
    }
    objects.erase(objects.begin() + index);
}

template <class T>
void PointedVector<T>::clear() {
    objects.clear();
    pointer = 0;
}

template <class T>
void PointedVector<T>::stepForward(int steps) {
    if (this->isEmpty()) { throw std::out_of_range("Nothing to select"); }
    pointer += steps;
    normalisePointer();
}

template <class T>
void PointedVector<T>::stepForward() {
    stepForward(1);
}

template <class T>
void PointedVector<T>::stepBackward(int steps) {
    if (this->isEmpty()) { throw std::out_of_range("Nothing to select"); }
    pointer -= steps;
    normalisePointer();
}

template <class T>
void PointedVector<T>::stepBackward() {
    stepBackward(1);
}

template <class T>
void PointedVector<T>::select(int newPointer) {
    if (this->isEmpty()) { throw std::out_of_range("Nothing to select"); }
    this->pointer = newPointer;
    this->normalisePointer();
}

template <class T>
void PointedVector<T>::normalisePointer() const {
    if (this->isEmpty()) { throw std::out_of_range("Nothing to select"); }
    if (pointer < 0) {
        pointer = ((pointer * (-1) / static_cast<int>(objects.size()) + 1) * static_cast<int>(objects.size()) + pointer) % static_cast<int>(objects.size());
    } else if (pointer >= static_cast<int>(objects.size())) {
        pointer = pointer % static_cast<int>(objects.size());
    }
}

#endif // UNTITLED_POINTEDVECTOR_H