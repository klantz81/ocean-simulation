all: lib/keyboard.o lib/joystick.o lib/mouse.o lib/glhelper.o lib/timer.o lib/misc.o lib/obj.o lib/complex.o lib/vector.o lib/buffer.o lib/fft.o
	g++ main.cc lib/keyboard.o lib/joystick.o lib/mouse.o lib/glhelper.o lib/timer.o lib/misc.o lib/obj.o lib/complex.o lib/vector.o lib/buffer.o lib/fft.o -o bin/main -L/usr/lib `sdl-config --cflags --libs` -lSDL_ttf -lSDL_image -lGL -lGLU -lGLEW -lglut -lpthread

lib/keyboard.o: src/keyboard.h src/keyboard.cc
	g++ src/keyboard.cc -c -o lib/keyboard.o

lib/joystick.o: src/joystick.h src/joystick.cc
	g++ src/joystick.cc -c -o lib/joystick.o

lib/mouse.o: src/mouse.h src/mouse.cc
	g++ src/mouse.cc -c -o lib/mouse.o

lib/glhelper.o: src/glhelper.h src/glhelper.cc
	g++ src/glhelper.cc -c -o lib/glhelper.o

lib/timer.o: src/timer.h src/timer.cc
	g++ src/timer.cc -c -o lib/timer.o

lib/misc.o: src/misc.h src/misc.cc
	g++ src/misc.cc -c -o lib/misc.o

lib/obj.o: src/obj.h src/obj.cc
	g++ src/obj.cc -c -o lib/obj.o

lib/complex.o: src/complex.h src/complex.cc
	g++ src/complex.cc -c -o lib/complex.o

lib/vector.o: src/vector.h src/vector.cc
	g++ src/vector.cc -c -o lib/vector.o

lib/buffer.o: src/buffer.h src/buffer.cc
	g++ src/buffer.cc -c -o lib/buffer.o

lib/fft.o: src/fft.h src/fft.cc
	g++ src/fft.cc -c -o lib/fft.o

clean:
	@rm -f *~ src/*~ lib/* bin/*
