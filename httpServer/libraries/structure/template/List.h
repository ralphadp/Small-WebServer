//
// Created by root on 08-02-20.
//

#ifndef STRUCTURE_TEMPLATE_LIST_H
#define STRUCTURE_TEMPLATE_LIST_H

#include <iostream>
#include "../String.h"

namespace Template {

    template<class T>
    class List {
        unsigned int m_INDEX = 0;
        T** m_ptr;
    public:
        List();

        ~List();

        void add(T value);

        const char* print();

        T operator[](unsigned int index);

        T operator[](unsigned int index) const;

        void clear();

        unsigned int getLength() const;
    };

    template<class T>
    List<T>::List() :
            m_INDEX(0), m_ptr(0) {
    }

    template<class T>
    List<T>::~List() {
        clear();
    }

    template<class T>
    void List<T>::add(T value) {
        T **pre = m_ptr;

        if (!pre) {
            pre = new T *[2];
        }

        if (m_INDEX) {
            T **aux = new T *[m_INDEX + 2];
            for (int index = 0; index <= m_INDEX - 1; index++) {
                aux[index] = pre[index];
            }
            delete[] pre;
            pre = aux;
        }
        pre[m_INDEX] = new T(value);
        pre[++m_INDEX] = 0;

        m_ptr = pre;
    }

    template<class T>
    const char* List<T>::print() {
        T** stack = m_ptr;
        Structure::String out("[");

        while (*stack) {
            T* str = *stack;
            out += "\"";
            out += *str;
            out += "\"";
            stack++;
            if (*stack) {
                out += ",";
            }
        }
        out += "]";

        return out.value();
    }

    template<class T>
    T List<T>::operator[](unsigned int index) {
        if (index >= 0 && index < m_INDEX) {

            return *m_ptr[index];
        }

        try {
            return T();
        }
        catch (T exception) {
            return 0;
        }
    }

    template<class T>
    T List<T>::operator[](unsigned int index) const {
        if (index >= 0 && index < m_INDEX) {

            return *m_ptr[index];
        }

        try {
            return T();
        }
        catch (T exception) {
            return 0;
        }
    }

    template<class T>
    void List<T>::clear() {
        for (int index = 0; index < m_INDEX; index++) {
            delete m_ptr[index];
        }

        delete [] m_ptr;
        m_ptr = 0;
        m_INDEX = 0;
    }

    template<class T>
    unsigned int List<T>::getLength() const {
        return m_INDEX;
    }
}

#endif //STRUCTURE_TEMPLATE_LIST_H
