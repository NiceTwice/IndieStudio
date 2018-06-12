//
// Created by fisun_s on 21/04/16.
//

#ifndef PIPETEST_THREAD_HPP
#define PIPETEST_THREAD_HPP


#include <string>
#include <fstream>
#include <map>
#include <pthread.h>
#include "Order.hh"

class Thread {
    pthread_t           _me;
    void                *(*funtion)(void *);
    void                *param;
public:
    Thread(void *(*func)(void *), void *param);
    ~Thread();
    void    launch(void);
    void    stop(void);
};


#endif //PIPETEST_THREAD_HPP
