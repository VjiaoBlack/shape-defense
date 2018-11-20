
#include "Graphics.hpp"

int SDL_Deleter::boop = 0;


sdl_texture_pt SDL::null_texture() {
  return sdl_texture_pt(nullptr);
}

ttf_font_pt SDL::null_font() {
  return ttf_font_pt(nullptr);
}