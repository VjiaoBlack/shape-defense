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
#include "Utils.hpp"
#include <MY.hpp>

void addTriangle(std::vector<GLfloat>& buf, int pos,
                 glm::vec2 a, glm::vec2 b, glm::vec2 c);

//template <typename T>
class CircularBuffer {
 public:
  static constexpr int k_length = 900;
  int m_head = 0; // most recently added
  int m_tail = 0; // least recently added
//  std::array<T, CircularBuffer::k_length> m_arr;
  std::array<float, CircularBuffer::k_length> m_arr;
  std::array<bool,  CircularBuffer::k_length> m_alive;

  CircularBuffer();

  // TODO: optimize these for bulk add/removes
//  int  add   (T   elem);
  int  add   (float   elem);
  bool remove(int pos);

  size_t size() { return CircularBuffer::k_length; }
//  T*     data() { return m_arr.data(); }
  float* data() { return m_arr.data(); }

 private:
};

class GraphicsBackend {
 public:
  static constexpr int triangles_per_ent = 8;

  std::vector<GLfloat> gridVBOdata;
  std::vector<GLfloat> entVBOdata;
  std::vector<GLfloat> enthealthVBOdata;
//  CircularBuffer<GLfloat> effectVBOdata;
//  CircularBuffer<GLfloat> guiVBOdata;
  CircularBuffer effectVBOdata;
  CircularBuffer guiVBOdata;

  GLuint gridVAO;
  GLuint entVAO;
  GLuint guiVAO;
  GLuint effectVAO;

  GLuint gridvertexVBO;
  GLuint entvertexVBO;
  GLuint enthealthVBO;
  GLuint guiVBO;
  GLuint effectVBO;

  GLuint gridShader;
  GLuint entShader;

  GLFWwindow* window;


  GraphicsBackend() {};

  void initialize();
  void destroy();

//  void loadShader();
//  void useShader();

  static void createVAO(GLuint* VAO);
  static void createVBO(GLuint* VBO, GLuint VAO);
  static void updateVBO(GLuint VBO, void* dataPtr, size_t size);

  // for fixed-sized data sources like Ents, use 1-1 mapping
  // for dynamic-sized data sources like firing lasers, use circular buffer
 private:

};

extern GraphicsBackend graphicsBackend;
constexpr int triangles_per_ent = 8;



struct Renderer {
  Renderer() = default;
};

struct Window {
  Window() = default;
};

using namespace std;


