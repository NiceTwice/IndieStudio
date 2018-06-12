//
// Created by debruy_p on 08/05/16.
//

#include <string.h>
#include <iostream>
#include "Order.hh"

Order::Order(TYPE type, size_t size, void *data) {
    _size = sizeof(TYPE) + sizeof(size_t) + size;
    _data = new char[_size];
    *((TYPE *) _data) = type;
    *((size_t *) ((char*)_data + sizeof(TYPE))) = size;
    for (int i = 0; i < size; ++i) {
        ((char *) ((char*)_data + sizeof(TYPE) + sizeof(size_t)))[i] = ((char *) data)[i];
    }

}

Order::~Order() {
    //if (_data)
    //delete[] (_data);
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

