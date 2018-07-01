
#include "TrGraphics.hpp"

int SDL_Deleter::boop = 0;


sdl_texture_pt TrSDL::null_texture() {
  return sdl_texture_pt(nullptr);
}

ttf_font_pt TrSDL::null_font() {
  return ttf_font_pt(nullptr);
}