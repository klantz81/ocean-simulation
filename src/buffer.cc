#include "buffer.h"

cBuffer::cBuffer(const int WIDTH, const int HEIGHT) : width(WIDTH), height(HEIGHT) {
	buffer = 0;
	buffer = new unsigned char [WIDTH * HEIGHT * 4];
}

cBuffer::~cBuffer() {
	if (buffer) delete [] buffer;
}

void cBuffer::save(const bool video) {
	static int i = 0;
	std::stringstream out;
	if (video) {
		if      (i < 10)
			out << "video000" << (i++) << ".tga";
		else if (i < 100)
			out << "video00" << (i++) << ".tga";
		else if (i < 1000)
			out << "video0" << (i++) << ".tga";
		else if (i < 10000)
			out << "video" << (i++) << ".tga";
	} else {
		out << "capture" << (i++) << ".tga";
	}
	std::string s = out.str();
	
	glReadPixels(0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, buffer);

	std::fstream of(s.c_str(), std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);

	char header[18] = { 0 };
	header[2]  = 2;
	header[12] = width & 0xff;
	header[13] = width >> 8;
	header[14] = height & 0xff;
	header[15] = height >> 8;
	header[16] = 32;

	of.write(header, 18);
	of.write((char *)buffer, width * height * 4);
}