//
// Thread.cpp for  in /home/walbec_h/rendu_tek2/CPP/cpp_indie_studio/src/Server
// 
// Made by walbec_h
// Login   <walbec_h@epitech.net>
// 
// Started on  Wed Apr 27 21:55:33 2016 walbec_h
// Last update Wed Apr 27 22:17:54 2016 walbec_h
//

#include <iostream>
#include <string.h>
#include <cstring>
#include "Thread.hh"

Thread::Thread(void) :
		m_state(State::READY) {
}

Thread::~Thread(void) {
}

Thread::State Thread::getStatus(void) const {
    return m_state;
}

int Thread::startThread(void *(*waitConnection)(void *), void *arg) {
    if (pthread_create(&m_thread, NULL, waitConnection, arg)) {
        std::cerr << "Error during pthread_create" << std::endl;
        return 1;
    }
    m_state = State::RUN;
    return 0;
}

int Thread::joinThread(void) {
    if(pthread_join(m_thread, NULL)) {
        std::cerr << "Error during pthread_join" << std::endl;
        return 1;
    }
    m_state = State::DEAD;
    return 0;
}

int Thread::cancelThread()
{
  if (pthread_cancel(m_thread) != 0)
    return 1;
    m_state = State::DEAD;
  return 0;
}
