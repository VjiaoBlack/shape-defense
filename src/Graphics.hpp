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

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <common/shader.hpp>
#include <MY.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

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

class CircularBuffer {
 public:
  int m_length;
  int m_head = 0; // most recently added
  int m_tail = 0; // least recently added

  std::vector<float> m_arr;
  std::vector<bool>  m_alive;

  CircularBuffer(int length)
      : m_length(length) {
    m_arr.resize(length);
    m_alive.resize(length);
  };

  // TODO: optimize these for bulk add/removes
  int add(float elem);
  bool remove(int pos);

  size_t size() { return m_length; }
  float *data() { return m_arr.data(); }

 private:
};

class GraphicsBackend {
 public:
  static constexpr int triangles_per_ent = 8;

  // consider making circular buffers resizable
  // and then only using circular buffers
  std::vector<GLfloat> gridVBOdata;
  std::vector<GLfloat> entVBOdata;
  std::vector<GLfloat> entcolorVBOdata;

  CircularBuffer effectVBOdata      = CircularBuffer(720);
  CircularBuffer effectcolorVBOdata = CircularBuffer(1080);
  CircularBuffer guiVBOdata         = CircularBuffer(720);
  CircularBuffer guicolorVBOdata    = CircularBuffer(1080);

  GLuint gridVAO;
  GLuint entVAO;
  GLuint guiVAO;
  GLuint effectVAO;

  GLuint gridvertexVBO;
  GLuint entvertexVBO;
  GLuint entcolorVBO;
  GLuint guiVBO;
  GLuint guicolorVBO;
  GLuint effectVBO;
  GLuint effectcolorVBO;

  GLuint gridShader;
  GLuint entShader;
  GLuint effectShader;
  GLuint guiShader;

  GLFWwindow *window;

  GraphicsBackend() {};

  void initialize();
  void destroy();

  static void createVAO(GLuint *VAO);
  static void createVBO(GLuint *VBO, GLuint VAO);
  static void updateVBO(GLuint VBO, void *dataPtr, size_t size);

  GLint attribute_coord;
  GLint uniform_tex;
  GLint uniform_color;

  struct point {
    GLfloat x;
    GLfloat y;
    GLfloat s;
    GLfloat t;
  };

  GLuint vbo;

  FT_Library ft;
  FT_Face    face;

  const char *fontfilename = "neris.thin.ttf";

  GLuint textShader;

  void render_text(const char *text,
                   float x,
                   float y,
                   float sx,
                   float sy);
  void displayText();
};

extern GraphicsBackend graphicsBackend;

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
