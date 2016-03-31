#include "joystick.h"

cJoystick::cJoystick() {
	active = false;
	joystick_fd = 0;
	joystick_ev = new js_event();
	joystick_st = new joystick_state();
	joystick_fd = open(JOYSTICK_DEV, O_RDONLY | O_NONBLOCK);
	if (joystick_fd > 0) {
		ioctl(joystick_fd, JSIOCGNAME(256), name);
		ioctl(joystick_fd, JSIOCGVERSION, &version);
		ioctl(joystick_fd, JSIOCGAXES, &axes);
		ioctl(joystick_fd, JSIOCGBUTTONS, &buttons);
		std::cout << "   Name: " << name << std::endl;
		std::cout << "Version: " << version << std::endl;
		std::cout << "   Axes: " << (int)axes << std::endl;
		std::cout << "Buttons: " << (int)buttons << std::endl << std::endl;
		joystick_st->axis.reserve(axes);
		joystick_st->button.reserve(buttons);
		active = true;
		pthread_create(&thread, 0, &cJoystick::loop, this);
	}
}

cJoystick::~cJoystick() {
	if (joystick_fd > 0) {
		active = false;
		pthread_join(thread, 0);
		close(joystick_fd);
	}
	delete joystick_st;
	delete joystick_ev;
	joystick_fd = 0;
}

void* cJoystick::loop(void *obj) {
	while (reinterpret_cast<cJoystick *>(obj)->active) reinterpret_cast<cJoystick *>(obj)->readEv();
}

void cJoystick::readEv() {
	int bytes = read(joystick_fd, joystick_ev, sizeof(*joystick_ev));
	if (bytes > 0) {
		joystick_ev->type &= ~JS_EVENT_INIT;
		if (joystick_ev->type & JS_EVENT_BUTTON) {
			joystick_st->button[joystick_ev->number] = joystick_ev->value;
		}
		if (joystick_ev->type & JS_EVENT_AXIS) {
			joystick_st->axis[joystick_ev->number] = joystick_ev->value;
		}
	}
}

joystick_position cJoystick::joystickPosition(int n) {
	joystick_position pos;

	if (n > -1 && n < buttons) {
		int i0 = n*2, i1 = n*2+1;
		float x0 = joystick_st->axis[i0]/32767.0f, y0 = -joystick_st->axis[i1]/32767.0f;
		float x  = x0 * sqrt(1 - pow(y0, 2)/2.0f), y  = y0 * sqrt(1 - pow(x0, 2)/2.0f);

		pos.x = x0;
		pos.y = y0;
		
		pos.theta = atan2(y, x);
		pos.r = sqrt(pow(y, 2) + pow(x, 2));
	} else {
		pos.theta = pos.r = pos.x = pos.y = 0.0f;
	}
	return pos;
}

bool cJoystick::buttonPressed(int n) {
	return n > -1 && n < buttons ? joystick_st->button[n] : 0;
}