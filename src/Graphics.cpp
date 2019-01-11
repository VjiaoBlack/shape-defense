#include "Graphics.hpp"


#include <TdECS/TdECSSystems/SystemUtils.hpp>
#include <cstring>

GraphicsBackend graphicsBackend;

//template<typename T>
//CircularBuffer<T>::CircularBuffer() {
CircularBuffer::CircularBuffer() {

}

//template<typename T>
//  int CircularBuffer<T>::add(T elem) {
int CircularBuffer::add(float elem) {
  if (m_head == m_tail - 1 || (m_head == k_length - 1 && m_tail == 0)) {
    return false; // full
  }
  printf("add %d\n", m_head);

  m_arr[m_head] = elem;
  m_alive[m_head] = true;
  int past = m_head;
  m_head++;

  if (m_head >= k_length) {
    m_head -= k_length;
  }

  return past;
}

//template<typename T>
//    bool CircularBuffer<T>::remove(int pos) {
bool CircularBuffer::remove(int pos) {
  if (!m_alive[pos]) {
    return false;
  }
  printf("remove %d\n", pos);

//  memset(&m_arr[pos], 0, sizeof(T));
//  memset(&m_arr[pos], 0, sizeof(float));
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
  if( !glfwInit() )
  {
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

  graphicsBackend.gridShader = LoadShaders( "grid.vs", "grid.fs" );
  graphicsBackend.entShader  = LoadShaders( "ent.vs" , "ent.fs"  );

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  graphicsBackend.gridVBOdata.resize(8000);
  graphicsBackend.entVBOdata.resize(3 * k_MAX_ENTS * triangles_per_ent * 3);
  graphicsBackend.enthealthVBOdata.resize(k_MAX_ENTS * triangles_per_ent * 3);
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
  GraphicsBackend::createVBO(&enthealthVBO, entVAO);
  GraphicsBackend::updateVBO(enthealthVBO, enthealthVBOdata.data(),
                             sizeof(GLfloat) * enthealthVBOdata.size());

  GraphicsBackend::createVAO(&guiVAO);
  GraphicsBackend::createVBO(&guiVBO, guiVAO);
  GraphicsBackend::updateVBO(guiVBO, guiVBOdata.data(),
                             sizeof(GLfloat) * guiVBOdata.size());

  GraphicsBackend::createVAO(&effectVAO);
  GraphicsBackend::createVBO(&effectVBO, effectVAO);
  GraphicsBackend::updateVBO(effectVBO, effectVBOdata.data(),
                             sizeof(GLfloat) * effectVBOdata.size());
};

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
  glDeleteBuffers(1, &graphicsBackend.enthealthVBO);
  glDeleteVertexArrays(1, &graphicsBackend.entVAO);

  glDeleteBuffers(1, &graphicsBackend.guiVBO);
  glDeleteVertexArrays(1, &graphicsBackend.guiVAO);

  glDeleteBuffers(1, &graphicsBackend.effectVBO);
  glDeleteVertexArrays(1, &graphicsBackend.effectVAO);

  glDeleteProgram(graphicsBackend.gridShader);
  glDeleteProgram(graphicsBackend.entShader);

  glfwTerminate();
}
