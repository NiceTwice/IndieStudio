//
// Created by fisun_s on 21/04/16.
//

#include <iostream>
#include <vector>
#include "Thread.hpp"
#include "TutorialApplication.h"
#include "GameMenu.hh"

pthread_mutex_t     g_lock = PTHREAD_MUTEX_INITIALIZER;

void            *thread_func(void *param){
    GameMenu    *game = (GameMenu*)param;

    Server *server = TutorialApplication::getSingleton().getServer();
    while (game->isRunning()) {
        server->communication();
    }
    return NULL;
}

Thread::Thread(void *(*func)(void *), void *param) {
    this->funtion = func;
    this->param = param;
}

Thread::~Thread() {

}

void Thread::launch(void) {
    pthread_create(&(this->_me), NULL, funtion, param);
}

void Thread::stop(void) {
    pthread_join(this->_me, NULL);
}



