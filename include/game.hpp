#pragma once

#include <SDL2/SDL.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

using namespace glimac;

class Game{
public:

  SDL_Window *window;
  SDL_GLContext glcontext;

  Game();
  ~Game();

  void initProgram(Program*, GLuint *, GLuint *, GLuint *, GLint *);

};

