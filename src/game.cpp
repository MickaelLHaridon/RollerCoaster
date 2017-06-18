#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <assert.h>

#include "game.hpp"

using namespace glimac;

Game::Game(){
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  this->window = SDL_CreateWindow(
                                        "RollerCoaster", 400, 200, 640, 640,
                                        SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

  // Check that the window was successfully created
  if (window == NULL) {
    // In the case that the window could not be made...
    printf("Could not create window: %s\n", SDL_GetError());
  }

  this->glcontext = SDL_GL_CreateContext(window);

  GLint error;
  if(GLEW_OK != (error = glewInit())) {
    std::cerr << "Impossible d'initialiser Glew" << std::endl;
  }

  std::cout << glGetString(GL_VERSION) << std::endl;
}

Game::~Game(){
  SDL_GL_DeleteContext(this->glcontext);
	SDL_Quit();
}

void Game::initProgram(Program *program, GLuint *locationMVPMatrix, GLuint *locationMVMatrix, GLuint *locationNormalMatrix,GLint *uTexture){

  *program = loadProgram(
                         "assets/shaders/3D.vs.glsl",
                         "assets/shaders/normals.fs.glsl"
                         );
  program->use();

  *locationMVPMatrix = glGetUniformLocation(program->getGLId(), "uMVPMatrix");
  *locationMVMatrix = glGetUniformLocation(program->getGLId(), "uMVMatrix");
  *locationNormalMatrix = glGetUniformLocation(program->getGLId(), "uNormalMatrix");
  *uTexture = glGetUniformLocation(program->getGLId(), "uTexture");
}
