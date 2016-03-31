#ifndef BUFFER_H
#define BUFFER_H

#include <sstream>
#include <fstream>
#include <GL/gl.h>

class cBuffer {
  private:
	int width, height;
	unsigned char *buffer;
  protected:
  public:
	cBuffer(const int WIDTH, const int HEIGHT);
	void save(bool video);
	~cBuffer();
};

#endif