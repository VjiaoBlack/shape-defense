#include "Graphics.hpp"


#include <TdECS/TdECSSystems/SystemUtils.hpp>
#include <Utils.hpp>
#include <cstring>


GraphicsBackend graphicsBackend;

// TODO: refactor into a .obj file, or similar
void addEnt(std::vector<GLfloat>& buf, int pos,
            glm::vec2 xy, float width, float thickness) {
  glm::vec2 off_vec = glm::vec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2);

  // left
  addTriangle(buf, pos + 9 * 0,
              xy - off_vec,
              xy - off_vec + glm::vec2(thickness, 0),
              xy - off_vec + glm::vec2(0, width));

  addTriangle(buf, pos + 9 * 1,
              xy - off_vec + glm::vec2(thickness, 0),
              xy - off_vec + glm::vec2(thickness, width),
              xy - off_vec + glm::vec2(0, width));

  // right
  addTriangle(buf, pos + 9 * 2,
              xy - off_vec + glm::vec2(width, 0),
              xy - off_vec + glm::vec2(width - thickness, 0),
              xy - off_vec + glm::vec2(width - thickness, width));

  addTriangle(buf, pos + 9 * 3,
              xy - off_vec + glm::vec2(width, 0),
              xy - off_vec + glm::vec2(width, width),
              xy - off_vec + glm::vec2(width - thickness, width));

  // bottom
  addTriangle(buf, pos + 9 * 4,
              xy - off_vec + glm::vec2(thickness, 0),
              xy - off_vec + glm::vec2(width - thickness, 0),
              xy - off_vec + glm::vec2(width - thickness, thickness));

  addTriangle(buf, pos + 9 * 5,
              xy - off_vec + glm::vec2(thickness, 0),
              xy - off_vec + glm::vec2(thickness, thickness),
              xy - off_vec + glm::vec2(width - thickness, thickness));

  // top
  addTriangle(buf, pos + 9 * 6,
              xy - off_vec + glm::vec2(thickness, width),
              xy - off_vec + glm::vec2(width - thickness, width),
              xy - off_vec + glm::vec2(width - thickness, width - thickness));

  addTriangle(buf, pos + 9 * 7,
              xy - off_vec + glm::vec2(thickness, width),
              xy - off_vec + glm::vec2(thickness, width - thickness),
              xy - off_vec + glm::vec2(width - thickness, width - thickness));
}

int CircularBuffer::add(float elem) {
  if (m_head == m_tail - 1 || (m_head == m_length - 1 && m_tail == 0)) {
    return false; // full
  }

  // if we're simply already on a valid element,
  // move until we get to an empty space
  while (m_alive[m_head]) {
    m_head++;

    if (m_head >= m_length) {
      m_head -= m_length;
    }
    if (m_head == m_tail - 1 || (m_head == m_length - 1 && m_tail == 0)) {
      return false; // full
    }
  }
  m_arr[m_head] = elem;
  m_alive[m_head] = true;
  int past = m_head;
  m_head++;

  if (m_head >= m_length) {
    m_head -= m_length;
  }

  return past;
}

bool CircularBuffer::remove(int pos) {
  if (!m_alive[pos]) {
    return false;
  }

  m_alive[pos] = false;
  m_arr[pos]   = 0.0;

  if (pos == m_tail) {
    m_tail++;

    // keep advancing tail until the next alive element, or empty
    while (!m_alive[m_tail] && m_tail != m_head) {
      m_tail++;
    }
  }

  return true;
}

void _createGrid() {
// vertical lines
  int grid_i = 0;
  int posx = 0;
  while (posx <= K_DISPLAY_SIZE_X / 2) {
    graphicsBackend.gridVBOdata[grid_i    ] = posx;
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
    graphicsBackend.gridVBOdata[grid_i    ] = K_DISPLAY_SIZE_X / 2.0f;
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
    fprintf( stderr, "Failed to initialize GLFW\n" );
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
    fprintf( stderr, "Failed to open GLFW window.\n" );
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

  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

  // pixel style
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//  // enable blend
//  glEnable(GL_BLEND);
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  graphicsBackend.gridShader = LoadShaders( "shaders/grid.vs", "shaders/grid.fs" );
  graphicsBackend.entShader  = LoadShaders( "shaders/ent.vs" , "shaders/ent.fs"  );
  graphicsBackend.effectShader = LoadShaders( "shaders/effect.vs", "shaders/effect.fs" );
  graphicsBackend.guiShader  = LoadShaders( "shaders/gui.vs" , "shaders/gui.fs"  );

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
  /* Initialize the FreeType2 library */
  if (FT_Init_FreeType(&ft)) {
    fprintf(stderr, "Could not init freetype library\n");
  }

  /* Load a font */
  if (FT_New_Face(ft, fontfilename, 0, &face)) {
    fprintf(stderr, "Could not open font %s\n", fontfilename);
  }

  textShader = LoadShaders("shaders/text.vs", "shaders/text.fs");

  attribute_coord = glGetAttribLocation(textShader, "coord");
  uniform_tex = glGetUniformLocation(textShader, "tex");
  uniform_color = glGetUniformLocation(textShader, "color");

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
  const char *p;
  FT_GlyphSlot g = face->glyph;
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  /* Create a texture that will be used to hold one "glyph" */
  GLuint tex;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glUniform1i(uniform_tex, 0);

  /* We require 1 byte alignment when uploading texture data */
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  /* Clamping to edges is important to prevent artifacts when scaling */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  /* Linear filtering usually looks best for text */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  /* Set up the VBO for our vertex data */
  glEnableVertexAttribArray(attribute_coord);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);

  /* Loop through all characters */
  for (p = text; *p; p++) {

    /* Try to load and render the character */
    if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
      continue;

    /* Upload the "bitmap", which contains an 8-bit grayscale image, as an alpha texture */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows, 0, GL_RED,
                 GL_UNSIGNED_BYTE, g->bitmap.buffer);

    /* Calculate the vertex and texture coordinates */
    float x2 = x + g->bitmap_left * sx;
    float y2 = -y - g->bitmap_top * sy;
    float w = g->bitmap.width * sx;
    float h = g->bitmap.rows * sy;

    point box[4] = {
        {x2, -y2, 0, 0},
        {x2 + w, -y2, 1, 0},
        {x2, -y2 - h, 0, 1},
        {x2 + w, -y2 - h, 1, 1},
    };

    /* Draw the character on the screen */
    glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    /* Advance the cursor to the start of the next character */
    x += (g->advance.x >> 6) * sx;
    y += (g->advance.y >> 6) * sy;
  }

  glDisableVertexAttribArray(attribute_coord);
  glDeleteTextures(1, &tex);
}

void GraphicsBackend::displayText() {
  float sx = 2.0 / K_DISPLAY_SIZE_X;
  float sy = 2.0 / K_DISPLAY_SIZE_Y;

  glUseProgram(textShader);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  /* White background */
//  glClearColor(0.5, 0.5, 0.5, 0.5);
//  glClear(GL_COLOR_BUFFER_BIT);

  /* Enable blending, necessary for our alpha texture */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  GLfloat black[4] = { 0, 0, 0, 1 };
  GLfloat red[4] = { 1, 0, 0, 1 };
  GLfloat transparent_green[4] = { 0, 1, 0, 0.5 };

  /* Set font size to 48 pixels, color to black */
  FT_Set_Pixel_Sizes(face, 0, 48);
  glUniform4fv(uniform_color, 1, black);

  /* Effects of alignment */
  render_text("The Quick Brown Fox Jumps Over The Lazy Dog", -1 + 8 * sx, 1 - 50 * sy, sx, sy);
  render_text("The Misaligned Fox Jumps Over The Lazy Dog", -1 + 8.5 * sx, 1 - 100.5 * sy, sx, sy);

  /* Scaling the texture versus changing the font size */
  render_text("The Small Texture Scaled Fox Jumps Over The Lazy Dog", -1 + 8 * sx, 1 - 175 * sy, sx * 0.5, sy * 0.5);
  FT_Set_Pixel_Sizes(face, 0, 24);
  render_text("The Small Font Sized Fox Jumps Over The Lazy Dog", -1 + 8 * sx, 1 - 200 * sy, sx, sy);
  FT_Set_Pixel_Sizes(face, 0, 48);
  render_text("The Tiny Texture Scaled Fox Jumps Over The Lazy Dog", -1 + 8 * sx, 1 - 235 * sy, sx * 0.25, sy * 0.25);
  FT_Set_Pixel_Sizes(face, 0, 12);
  render_text("The Tiny Font Sized Fox Jumps Over The Lazy Dog", -1 + 8 * sx, 1 - 250 * sy, sx, sy);
  FT_Set_Pixel_Sizes(face, 0, 48);

  /* Colors and transparency */
  render_text("The Solid Black Fox Jumps Over The Lazy Dog", -1 + 8 * sx, 1 - 430 * sy, sx, sy);

  glUniform4fv(uniform_color, 1, red);
  render_text("The Solid Red Fox Jumps Over The Lazy Dog", -1 + 8 * sx, 1 - 330 * sy, sx, sy);
  render_text("The Solid Red Fox Jumps Over The Lazy Dog", -1 + 28 * sx, 1 - 450 * sy, sx, sy);

  glUniform4fv(uniform_color, 1, transparent_green);
  render_text("The Transparent Green Fox Jumps Over The Lazy Dog", -1 + 8 * sx, 1 - 380 * sy, sx, sy);
  render_text("The Transparent Green Fox Jumps Over The Lazy Dog", -1 + 18 * sx, 1 - 440 * sy, sx, sy);

//  glutSwapBuffers();

  glDisable(GL_BLEND);

}



void GraphicsBackend::createVAO(GLuint* VAO) {
  glGenVertexArrays(1, VAO);
};

void GraphicsBackend::createVBO(GLuint* VBO, GLuint VAO) {
  glBindVertexArray(VAO);
  glGenBuffers(1, VBO);
};

void GraphicsBackend::updateVBO(GLuint VBO, void* dataPtr, size_t size) {
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

Triangle::Triangle(CircularBuffer* buffer, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3)
  : m_buffer(buffer)
  , m_hasColor(false) {
  m_indices[0] = m_buffer->add(p1.x - K_DISPLAY_SIZE_X / 2.0);
  m_indices[1] = m_buffer->add(p1.y - K_DISPLAY_SIZE_Y / 2.0);

  m_indices[2] = m_buffer->add(p2.x - K_DISPLAY_SIZE_X / 2.0);
  m_indices[3] = m_buffer->add(p2.y - K_DISPLAY_SIZE_Y / 2.0);

  m_indices[4] = m_buffer->add(p3.x - K_DISPLAY_SIZE_X / 2.0);
  m_indices[5] = m_buffer->add(p3.y - K_DISPLAY_SIZE_Y / 2.0);

}

Triangle::Triangle(CircularBuffer* buffer, CircularBuffer* colorBuffer,
                   glm::vec2 p1, glm::vec2 p2, glm::vec2 p3,
                   glm::vec3 color)
  : m_buffer(buffer)
  , m_colorBuffer(colorBuffer)
  , m_hasColor(true) {
  m_indices[0] = m_buffer->add(p1.x - K_DISPLAY_SIZE_X / 2.0);
  m_indices[1] = m_buffer->add(p1.y - K_DISPLAY_SIZE_Y / 2.0);
  m_indices[2] = m_buffer->add(p2.x - K_DISPLAY_SIZE_X / 2.0);
  m_indices[3] = m_buffer->add(p2.y - K_DISPLAY_SIZE_Y / 2.0);
  m_indices[4] = m_buffer->add(p3.x - K_DISPLAY_SIZE_X / 2.0);
  m_indices[5] = m_buffer->add(p3.y - K_DISPLAY_SIZE_Y / 2.0);

  m_colors[0] = m_colorBuffer->add(color.r);
  m_colors[1] = m_colorBuffer->add(color.g);
  m_colors[2] = m_colorBuffer->add(color.b);
  m_colors[3] = m_colorBuffer->add(color.r);
  m_colors[4] = m_colorBuffer->add(color.g);
  m_colors[5] = m_colorBuffer->add(color.b);
  m_colors[6] = m_colorBuffer->add(color.r);
  m_colors[7] = m_colorBuffer->add(color.g);
  m_colors[8] = m_colorBuffer->add(color.b);
}

void Triangle::update(glm::vec3 color) {
  if (m_buffer && m_hasColor) {
    m_colorBuffer->m_arr[m_colors[0]] = color.r;
    m_colorBuffer->m_arr[m_colors[1]] = color.g;
    m_colorBuffer->m_arr[m_colors[2]] = color.b;
    m_colorBuffer->m_arr[m_colors[3]] = color.r;
    m_colorBuffer->m_arr[m_colors[4]] = color.g;
    m_colorBuffer->m_arr[m_colors[5]] = color.b;
    m_colorBuffer->m_arr[m_colors[6]] = color.r;
    m_colorBuffer->m_arr[m_colors[7]] = color.g;
    m_colorBuffer->m_arr[m_colors[8]] = color.b;
  }
}

void Triangle::update(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec3 color) {
  if (m_buffer) {
    m_buffer->m_arr[m_indices[0]] = p1.x - K_DISPLAY_SIZE_X / 2.0;
    m_buffer->m_arr[m_indices[1]] = p1.y - K_DISPLAY_SIZE_Y / 2.0;
    m_buffer->m_arr[m_indices[2]] = p2.x - K_DISPLAY_SIZE_X / 2.0;
    m_buffer->m_arr[m_indices[3]] = p2.y - K_DISPLAY_SIZE_Y / 2.0;
    m_buffer->m_arr[m_indices[4]] = p3.x - K_DISPLAY_SIZE_X / 2.0;
    m_buffer->m_arr[m_indices[5]] = p3.y - K_DISPLAY_SIZE_Y / 2.0;

    if (m_hasColor) {
      this->update(color);
    }
  }
}

void Triangle::destroy() {
  if (m_buffer) {
    m_buffer->remove(m_indices[0]);
    m_buffer->remove(m_indices[1]);
    m_buffer->remove(m_indices[2]);
    m_buffer->remove(m_indices[3]);
    m_buffer->remove(m_indices[4]);
    m_buffer->remove(m_indices[5]);
    m_buffer = nullptr;

    if (m_hasColor) {
      m_colorBuffer->remove(m_colors[0]);
      m_colorBuffer->remove(m_colors[1]);
      m_colorBuffer->remove(m_colors[2]);
      m_colorBuffer->remove(m_colors[3]);
      m_colorBuffer->remove(m_colors[4]);
      m_colorBuffer->remove(m_colors[5]);
      m_colorBuffer->remove(m_colors[6]);
      m_colorBuffer->remove(m_colors[7]);
      m_colorBuffer->remove(m_colors[8]);
    }
  }
}