/**
 * GraphicsBackend.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <TdECS/TdECSSystems/SystemUtils.hpp>
#include <Utils.hpp>
#include "GraphicsBackend.hpp"


void _createGrid() {
// vertical lines
  int grid_i = 0;
  int posx   = 0;
  while (posx <= K_DISPLAY_SIZE_X / 2) {
    graphicsBackend.gridVBOdata[grid_i]     = posx;
    graphicsBackend.gridVBOdata[grid_i + 1] = -K_DISPLAY_SIZE_Y / 2.0f;

    graphicsBackend.gridVBOdata[grid_i + 2] = posx;
    graphicsBackend.gridVBOdata[grid_i + 3] = K_DISPLAY_SIZE_Y / 2.0f;

    graphicsBackend.gridVBOdata[grid_i + 4] = -posx;
    graphicsBackend.gridVBOdata[grid_i + 5] = -K_DISPLAY_SIZE_Y / 2.0f;

    graphicsBackend.gridVBOdata[grid_i + 6] = -posx;
    graphicsBackend.gridVBOdata[grid_i + 7] = K_DISPLAY_SIZE_Y / 2.0f;

    grid_i += 12;
    posx += 16;
  }

  // horizontal lines
  int posy = 0;
  while (posy <= K_DISPLAY_SIZE_Y / 2) {
    graphicsBackend.gridVBOdata[grid_i]     = K_DISPLAY_SIZE_X / 2.0f;
    graphicsBackend.gridVBOdata[grid_i + 1] = posy;

    graphicsBackend.gridVBOdata[grid_i + 2] = -K_DISPLAY_SIZE_X / 2.0f;
    graphicsBackend.gridVBOdata[grid_i + 3] = posy;

    graphicsBackend.gridVBOdata[grid_i + 4] = K_DISPLAY_SIZE_X / 2.0f;
    graphicsBackend.gridVBOdata[grid_i + 5] = -posy;

    graphicsBackend.gridVBOdata[grid_i + 6] = -K_DISPLAY_SIZE_X / 2.0f;
    graphicsBackend.gridVBOdata[grid_i + 7] = -posy;

    grid_i += 12;
    posy += 16;
  }
}

void GraphicsBackend::initialize() {
  // Initialise GLFW
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    getchar();
    exit(1);
  }

  glfwWindowHint(GLFW_SAMPLES, 1);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  graphicsBackend.window = glfwCreateWindow(K_DISPLAY_SIZE_X, K_DISPLAY_SIZE_Y,
                                            "shape defense", NULL, NULL);
  if (graphicsBackend.window == NULL) {
    fprintf(stderr, "Failed to open GLFW window.\n");
    getchar();
    glfwTerminate();
    exit(1);
  }
  glfwMakeContextCurrent(graphicsBackend.window);

  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    exit(1);
  }

  // ensure we can capture the escape key being pressed below
  glfwSetInputMode(graphicsBackend.window, GLFW_STICKY_KEYS, GL_TRUE);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // pixel style
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // // enable blend
  // glEnable(GL_BLEND);
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  graphicsBackend.gridShader   = LoadShaders("shaders/grid.vs", "shaders/grid.fs");
  graphicsBackend.entShader    = LoadShaders("shaders/ent.vs", "shaders/ent.fs");
  graphicsBackend.effectShader = LoadShaders("shaders/effect.vs", "shaders/effect.fs");
  graphicsBackend.guiShader    = LoadShaders("shaders/gui.vs", "shaders/gui.fs");

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  graphicsBackend.gridVBOdata.resize(8000);
  graphicsBackend.entVBOdata.resize(3 * k_MAX_ENTS * triangles_per_ent * 3);
  graphicsBackend.entcolorVBOdata.resize(3 * k_MAX_ENTS * triangles_per_ent * 3);
  // effectVBOdata and guiVBOdata have constexpr sizes

  _createGrid();

  GraphicsBackend::createVAO(&gridVAO);
  GraphicsBackend::createVBO(&gridvertexVBO, gridVAO);
  GraphicsBackend::updateVBO(gridvertexVBO, gridVBOdata.data(),
                             sizeof(GLfloat) * gridVBOdata.size());

  GraphicsBackend::createVAO(&entVAO);
  GraphicsBackend::createVBO(&entvertexVBO, entVAO);
  GraphicsBackend::updateVBO(entvertexVBO, entVBOdata.data(),
                             sizeof(GLfloat) * entVBOdata.size());
  GraphicsBackend::createVBO(&entcolorVBO, entVAO);
  GraphicsBackend::updateVBO(entcolorVBO, entcolorVBOdata.data(),
                             sizeof(GLfloat) * entcolorVBOdata.size());

  GraphicsBackend::createVAO(&guiVAO);
  GraphicsBackend::createVBO(&guiVBO, guiVAO);
  GraphicsBackend::updateVBO(guiVBO, guiVBOdata.data(),
                             sizeof(GLfloat) * guiVBOdata.size());
  GraphicsBackend::createVBO(&guicolorVBO, guiVAO);
  GraphicsBackend::updateVBO(guicolorVBO, guicolorVBOdata.data(),
                             sizeof(GLfloat) * guicolorVBOdata.size());

  GraphicsBackend::createVAO(&effectVAO);
  GraphicsBackend::createVBO(&effectVBO, effectVAO);
  GraphicsBackend::updateVBO(effectVBO, effectVBOdata.data(),
                             sizeof(GLfloat) * effectVBOdata.size());
  GraphicsBackend::createVBO(&effectcolorVBO, effectVAO);
  GraphicsBackend::updateVBO(effectcolorVBO, effectcolorVBOdata.data(),
                             sizeof(GLfloat) * effectcolorVBOdata.size());

  // initialize text
  // Initialize the FreeType2 library
  if (FT_Init_FreeType(&ft)) {
    fprintf(stderr, "Could not init freetype library\n");
  }

  // Load a font
  if (FT_New_Face(ft, fontfilename, 0, &face)) {
    fprintf(stderr, "Could not open font %s\n", fontfilename);
  }

  textShader = LoadShaders("shaders/text.vs", "shaders/text.fs");

  attribute_coord = glGetAttribLocation(textShader, "coord");
  uniform_tex     = glGetUniformLocation(textShader, "tex");
  uniform_color   = glGetUniformLocation(textShader, "color");

  if (attribute_coord < 0) {
    printf("ERRRORRR\n");
  }

  if (uniform_tex < 0) {
    printf("ERRRORRR\n");
  }

  if (uniform_color < 0) {
    printf("ERRRORRR\n");
  }

  // Create the vertex buffer object
  glGenBuffers(1, &vbo);
}

void GraphicsBackend::render_text(const char *text, float x, float y, float sx, float sy) {
  const char   *p;
  FT_GlyphSlot g = face->glyph;
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Create a texture that will be used to hold one "glyph"
  GLuint tex;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glUniform1i(uniform_tex, 0);

  // We require 1 byte alignment when uploading texture data
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // Clamping to edges is important to prevent artifacts when scaling
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  // Linear filtering usually looks best for text
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Set up the VBO for our vertex data
  glEnableVertexAttribArray(attribute_coord);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);

  // Loop through all characters
  for (p = text; *p; p++) {

    // Try to load and render the character
    if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
      continue;

    // Upload the "bitmap", which contains an 8-bit grayscale image, as an alpha texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows, 0, GL_RED,
                 GL_UNSIGNED_BYTE, g->bitmap.buffer);

    // Calculate the vertex and texture coordinates
    float x2 = x + g->bitmap_left * sx;
    float y2 = -y - g->bitmap_top * sy;
    float w  = g->bitmap.width * sx;
    float h  = g->bitmap.rows * sy;

    point box[4] = {
        {x2, -y2, 0, 0},
        {x2 + w, -y2, 1, 0},
        {x2, -y2 - h, 0, 1},
        {x2 + w, -y2 - h, 1, 1},
    };

    // Draw the character on the screen
    glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Advance the cursor to the start of the next character
    x += (g->advance.x >> 6) * sx;
    y += (g->advance.y >> 6) * sy;
  }

  glDisableVertexAttribArray(attribute_coord);
  glDeleteTextures(1, &tex);
}

void GraphicsBackend::createVAO(GLuint *VAO) {
  glGenVertexArrays(1, VAO);
};

void GraphicsBackend::createVBO(GLuint *VBO, GLuint VAO) {
  glBindVertexArray(VAO);
  glGenBuffers(1, VBO);
};

void GraphicsBackend::updateVBO(GLuint VBO, void *dataPtr, size_t size) {
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, size, dataPtr, GL_STATIC_DRAW);
};

void GraphicsBackend::destroy() {
  // Cleanup VBO
  glDeleteBuffers(1, &graphicsBackend.gridvertexVBO);
  glDeleteVertexArrays(1, &graphicsBackend.gridVAO);

  glDeleteBuffers(1, &graphicsBackend.entvertexVBO);
  glDeleteBuffers(1, &graphicsBackend.entcolorVBO);
  glDeleteVertexArrays(1, &graphicsBackend.entVAO);

  glDeleteBuffers(1, &graphicsBackend.guiVBO);
  glDeleteVertexArrays(1, &graphicsBackend.guiVAO);

  glDeleteBuffers(1, &graphicsBackend.effectVBO);
  glDeleteBuffers(1, &graphicsBackend.effectcolorVBO);
  glDeleteVertexArrays(1, &graphicsBackend.effectVAO);

  glDeleteProgram(graphicsBackend.gridShader);
  glDeleteProgram(graphicsBackend.entShader);

  glfwTerminate();
}