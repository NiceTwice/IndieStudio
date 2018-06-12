//
// Thread.hh for  in /home/walbec_h/rendu_tek2/CPP/cpp_indie_studio/src/Server
// 
// Made by walbec_h
// Login   <walbec_h@epitech.net>
// 
// Started on  Wed Apr 27 21:55:29 2016 walbec_h
// Last update Wed Apr 27 22:17:08 2016 walbec_h
//

#ifndef __THREAD_HH__
# define __THREAD_HH__

# include <pthread.h>

class Thread {
public:
	enum State {
		READY = 0,
		RUN = 1,
		DEAD = 2
	};

protected:
	pthread_t m_thread;
	State m_state;

public:
	Thread(void);
	~Thread(void);

	State getStatus() const;

	int startThread(void *(*waitConnection)(void *), void *);
	int joinThread(void);
  	int cancelThread();
};

#endif
