#ifndef MOUSE_H
#define MOUSE_H

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <linux/input.h>

#define MOUSE_DEV "/dev/input/event1"

struct mouse_state {
	int axis[2];
	int button[3];
};

class cMouse {
  private:
	pthread_t thread;
	bool active;
	int mouse_fd;
	input_event *mouse_ev;
	mouse_state mouse_st;
	char name[256];

  protected:
  public:
	cMouse();
	~cMouse();
	static void* loop(void* obj);
	void readEv();
	mouse_state getMouseState();
};

#endif