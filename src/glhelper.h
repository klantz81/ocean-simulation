#ifndef GLHELPER_H
#define GLHELPER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "misc.h"

SDL_Surface* my_SDL_init(const int WIDTH, const int HEIGHT, const bool fullscreen);

void setupTexture(GLuint& texture);
void setupTexture(GLuint& texture, SDL_Surface *s);
void setupTextureFloat(GLuint& texture, int w, int h, const float texturef[]);
void deleteTexture(GLuint& texture);

void setupCubeMap(GLuint& texture);
void setupCubeMap(GLuint& texture, SDL_Surface *xpos, SDL_Surface *xneg, SDL_Surface *ypos, SDL_Surface *yneg, SDL_Surface *zpos, SDL_Surface *zneg);
void deleteCubeMap(GLuint& texture);

void createProgram(GLuint& glProgram, GLuint& glShaderV, GLuint& glShaderF, const char* vertex_shader, const char* fragment_shader);
void releaseProgram(GLuint& glProgram, GLuint glShaderV, GLuint glShaderF);

void saveTGA(unsigned char* buffer, int width, int height, bool video = false);

void glerror(const char* prepend);

#endif
