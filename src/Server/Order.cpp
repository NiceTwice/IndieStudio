//
// Created by debruy_p on 27/04/16.
//

#include <cstring>
#include <ctime>
#include <cstdint>
#include <iostream>
#include "Order.hh"


Order::Order(TYPE type, size_t size, void *data) {
    _size = sizeof(TYPE) + sizeof(size_t) + size;
    _data = new char[_size];
    *((TYPE *) _data) = type;
    *((size_t *) ((char*)_data + sizeof(TYPE))) = size;
    for (int i = 0; i < size ; ++i) {
        ((char*)_data + sizeof(TYPE) + sizeof(size_t))[i] = ((char *) data)[i];
    }
}

Order::~Order() {
    delete[]((char*)_data);
}

size_t Order::getSize() const {
    return _size;
}

void *Order::getData() const {
    return _data;
}

Order::TYPE Order::getType() const {
    return *((TYPE*)_data);
}