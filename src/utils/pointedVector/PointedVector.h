//
// Created by dimon on 07.06.2026.
//


#ifndef UNTITLED_POINTEDVECTOR_H
#define UNTITLED_POINTEDVECTOR_H

#include <vector>
#include <stdexcept>

template <class T>
class PointedVector {
private:
    std::vector<T> objects = std::vector<T>();
    mutable int pointer = 0;
    void normalisePointer() const;

public:
    T operator[](int index);
    T get(int index);
    T getSelected();
    T first();
    T last();
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
    void select(int pointer);
};

template <class T>
T PointedVector<T>::operator[](int index) {
    return objects.at(index);
}

template <class T>
T PointedVector<T>::get(int index) {
    if (index < 0) {index = objects.size() + index;}
    if (index < 0) {throw std::out_of_range("index out of range");}
    if (index >= objects.size()) {throw std::out_of_range("index out of range");}
    return objects[index];
}

template <class T>
T PointedVector<T>::getSelected() {
    if (this->isEmpty()) {throw std::out_of_range("Nothing to select");}
    this->normalisePointer();
    return objects[this->pointer];
}

template <class T>
T PointedVector<T>::first() {
    if (this->isEmpty()) {throw std::out_of_range("index out of range");}
    return objects[0];
}

template <class T>
T PointedVector<T>::last() {
    if (this->isEmpty()) {throw std::out_of_range("index out of range");}
    return objects[objects.size() - 1];
}

template <class T>
int PointedVector<T>::size() const {
    return objects.size();
}

template <class T>
int PointedVector<T>::getPointer() const {
    if (isEmpty()) {throw std::out_of_range("Nothing to select");}
    normalisePointer();
    return pointer;
}

template <class T>
bool PointedVector<T>::isEmpty() const {
    return objects.empty();
}

template <class T>
void PointedVector<T>::insert(int index, T value) {
    if (index < 0) {index = objects.size() + index;}
    if (index < 0) {throw std::out_of_range("index out of range");}
    if (index > objects.size()) {throw std::out_of_range("index out of range");}
    objects.insert(objects.begin() + index, value);
}

template <class T>
void PointedVector<T>::add(T value) {
    objects.push_back(value);
}

template <class T>
void PointedVector<T>::remove(const int index) {
    objects.erase(objects.begin() + index);
}

template <class T>
void PointedVector<T>::clear() {
    objects.clear();
}

template <class T>
void PointedVector<T>::stepForward(const int steps) {
    if (this->isEmpty()) {throw std::out_of_range("Nothing to select");}
    pointer += steps;
    normalisePointer();
}

template <class T>
void PointedVector<T>::stepForward() {
    stepForward(1);
}

template <class T>
void PointedVector<T>::stepBackward(const int steps) {
    if (this->isEmpty()) {throw std::out_of_range("Nothing to select");}
    pointer -= steps;
    normalisePointer();
}

template <class T>
void PointedVector<T>::stepBackward() {
    stepBackward(1);
}

template <class T>
void PointedVector<T>::select(int pointer) {
    if (this->isEmpty()) {throw std::out_of_range("Nothing to select");}
    this->pointer = pointer;
    this->normalisePointer();
}

template <class T>
void PointedVector<T>::normalisePointer() const {
    if (this->isEmpty()) {throw std::out_of_range("Nothing to select");}
    if (pointer < 0) {
        pointer = ((pointer*(-1)/objects.size() + 1)*objects.size() + pointer)%objects.size();
    } else if (pointer >= objects.size()) {
        pointer = pointer%objects.size();
    }
}

#endif //UNTITLED_POINTEDVECTOR_H