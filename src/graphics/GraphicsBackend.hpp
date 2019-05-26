#pragma once
/**
 * GraphiscBackend.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <common/CircularBuffer.hpp>
#include <common/shader.hpp>

class GraphicsBackend;

extern GraphicsBackend graphicsBackend;

// TODO: consider using GPU instancing
class GraphicsBackend {
 public:
  static constexpr int triangles_per_ent = 8;

  // consider making circular buffers resizable
  // and then only using circular buffers
  std::vector<GLfloat> backgroundVBOdata;
  std::vector<GLfloat> entVBOdata;
  std::vector<GLfloat> entcolorVBOdata;

  CircularBuffer effectVBOdata      = CircularBuffer(7200);
  CircularBuffer effectcolorVBOdata = CircularBuffer(10800);
  CircularBuffer guiVBOdata         = CircularBuffer(72000);
  CircularBuffer guicolorVBOdata    = CircularBuffer(108000);

  GLuint backgroundVAO;
  GLuint entVAO;
  GLuint guiVAO;
  GLuint effectVAO;

  GLuint backgroundVBO;
  GLuint entvertexVBO;
  GLuint entcolorVBO;
  GLuint guiVBO;
  GLuint guicolorVBO;
  GLuint effectVBO;
  GLuint effectcolorVBO;

  GLuint backgroundShader;
  GLuint entShader;
  GLuint effectShader;
  GLuint guiShader;

  GLuint heatmapTex;

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
};