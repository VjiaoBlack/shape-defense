#pragma once
/**
 * TrGraphics.hpp
 *
 * Victor Jiao
 *
 * Stores wrappers for SDL2
 */

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <memory>

#define GLM_FORCE_PURE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <graphics/GraphicsBackend.hpp>

void addTriangle(std::vector<GLfloat> &buf,
                 int       pos,
                 glm::vec2 a,
                 glm::vec2 b,
                 glm::vec2 c);

void addEnt(std::vector<GLfloat> &buf,
            int       pos,
            glm::vec2 xy,
            float     width,
            float     thickness);

constexpr int triangles_per_ent = 8;

// TODO: do we need to cache-optimize this more?
// TODO: ... do we need to space-optimize this more?
struct Triangle {
  std::array<int, 6> m_indices;
  std::array<int, 9> m_colors;

  bool            m_hasColor    = false;
  CircularBuffer *m_buffer      = nullptr;
  CircularBuffer *m_colorBuffer = nullptr;

  Triangle() {};

  Triangle(CircularBuffer *buffer,
           glm::vec2 p1,
           glm::vec2 p2,
           glm::vec2 p3);

  Triangle(CircularBuffer *buffer,
           CircularBuffer *colorBuffer,
           glm::vec2 p1,
           glm::vec2 p2,
           glm::vec2 p3,
           glm::vec3 color);

  void update(glm::vec3 color);

  void update(glm::vec2 p1,
              glm::vec2 p2,
              glm::vec2 p3,
              glm::vec3 color);

  void destroy();
};

class Camera {
 public:
  static glm::vec2 pos;
  static glm::vec2 vel;

  static constexpr glm::vec2 dim = glm::vec2(1600, 900);
};


class World {
 public:
  static constexpr glm::ivec2 dim  = glm::ivec2(400, 300);
  static constexpr int        size = dim.x * dim.y;
};

