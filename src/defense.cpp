/**
 * defense.cpp
 *
 * Victor Jiao
 *
 *
 */

#define GLM_SWIZZLE
#define GLM_INLINE

#include "Game.hpp"
#include <execinfo.h>
#include <signal.h>
#include <unistd.h>

#include <GLFW/glfw3.h>


void handler(int sig) {
  constexpr int k_max_entries = 32;
  void *array[k_max_entries];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, k_max_entries);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}


int main(int argv, char *argc[]) {
  signal(SIGSEGV, handler);   // install our handler

  shared_ptr<Game> renderer = make_shared<Game>();
  renderer->run();
  renderer.reset();
//  TTF_Quit();
//  SDL_Quit();
  return 0;
}