//
// Created by Marian Mutu on 17.04.2022.
//

#ifndef RETEADESOCIALIZARE_TADARRAY_H
#define RETEADESOCIALIZARE_TADARRAY_H

#include <iostream>
using namespace std;

template <class T>
class Array{
private:
    T elems[100];
    int noEntites;
public:
    Array();
    Array(const Array<T>& array);
    ~Array();
    void push_back(T elem);
    void deleteElem(int pos);
    T getElem(int pos);
    void setElemPos(int pos, T el);
    int size();
    Array<T> &operator=(const Array<T> &array);
};

template<class T>
Array<T>::Array() {
    this->noEntites = 0;
}

template<class T>
Array<T>::Array(const Array<T> &array) {
//    this->elems = new T[array.noEntites + 1];
    this->noEntites = array.noEntites;
    for(int i = 0; i < array.noEntites; i++){
        this->elems[i] = array.elems[i];
    }
}

template<class T>
Array<T>::~Array() {
//    if(this->elems)
//        delete []elems;
}

template<class T>
void Array<T>::push_back(T elem) {
//    this->elems = new T[noEntites++];
        this->elems[this->noEntites++] = elem;
}

template<class T>
void Array<T>::deleteElem(int pos) {
    if(this->elems)
        this->elems[pos] = this->elems[--this->noEntites];
}

template<class T>
T Array<T>::getElem(int pos) {
    return this->elems[pos];
}

template<class T>
int Array<T>::size() {
    return this->noEntites;
}

template<class T>
void Array<T>::setElemPos(int pos, T el) {
    if(this->elems)
        this->elems[pos] = el;
}


template<class T>
Array<T> &Array<T>::operator=(const Array<T> &array) {
    noEntites = array.noEntites;
    for(int i = 0; i < array.noEntites; i++) {
        this->elems[i] = array.elem[i];
    }
    return *this;
}

#endif //RETEADESOCIALIZARE_TADARRAY_H
