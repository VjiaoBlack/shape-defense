
#include "Game.hpp"
#include "RenderLoop/GameLoop.hpp"
#include "RenderLoop/MainMenuLoop.hpp"

#include <deque>
#include <ECS/Entity.hpp>

#include <Graphics.hpp>

set<int>  Game::m_keysDown;
set<int>  Game::m_keysDownPrev;
set<char> Game::m_buttonsDown;
set<char> Game::m_buttonsDownPrev;

double Game::m_mouseX;
double Game::m_mouseY;


#include <signal.h>

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{

  // only show severe errors
  if (severity != GL_DEBUG_SEVERITY_NOTIFICATION
//      && severity != GL_DEBUG_SEVERITY_LOW
//      && severity != GL_DEBUG_SEVERITY_MEDIUM
      ) {
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
             ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
             type, severity, message );

//    raise(SIGSEGV);
//    exit(0);
    // nothing?
  }


}

// During init, enable debug output

Game::Game()
  : m_quit(false)
  , m_gameStateTransition(nullptr)
  , m_deltaTime(0)
  , m_frames(0)
  , m_frameRate(30) {
  graphicsBackend.initialize();

  glEnable              ( GL_DEBUG_OUTPUT );
  glDebugMessageCallback( MessageCallback, 0 );

  // initialize framerate counter
  m_deltaTime = 0;
  m_frames = 0;
  m_frameRate = 30;

  // use glfw callbacks
  glfwSetKeyCallback(graphicsBackend.window, Game::key_callback);
  glfwSetCursorPosCallback(graphicsBackend.window, Game::cursor_pos_callback);
  glfwSetMouseButtonCallback(graphicsBackend.window, Game::mouse_button_callback);

  // setup entities
  m_entitySystem = make_unique<System>();
  Entity::addEntity<EntityType::BASE>(this, m_entitySystem.get());

  // setup game loop
  auto tempmenu = make_shared<MainMenuLoop>(this);
  m_gameStateStack.push_back(std::move(tempmenu));
}

Game::~Game() {
  while (!m_gameStateStack.empty()) {
    m_gameStateStack.pop_back();
  }

  graphicsBackend.destroy();
}

void Game::run() {
  while (!m_quit) {
    // TODO: consider GLFW time?
    clock_t beginFrame = clock();

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    glfwPollEvents();

    // draw Background
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glUseProgram(graphicsBackend.backgroundShader);
    glBindVertexArray(graphicsBackend.backgroundVAO);

    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, graphicsBackend.heatmapTex);
    glUniform1i(2, 0);

    glBindBuffer(GL_ARRAY_BUFFER, graphicsBackend.backgroundVBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                          4 * sizeof(float), (void*) (0 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                          4 * sizeof(float), (void*) (2 * sizeof(float)));

    glUniform2i(3, World::dim.x, World::dim.y);
    glUniform2f(4, Camera::dim.x, Camera::dim.y);
    glUniform2f(5, Camera::pos.x, Camera::pos.y);

    glDrawArrays(GL_TRIANGLES, 0, graphicsBackend.backgroundVBOdata.size() / 4);

    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_gameStateTransition) {
      m_gameStateTransition->render(this);
      RenderLoop *loop = m_gameStateTransition->update(this);
      if (!loop) {
        m_gameStateTransition.reset(nullptr);
      }
    } else if (m_gameStateStack.back()) {
      m_gameStateStack.back()->render(this);
      RenderLoop *loop = m_gameStateStack.back()->update(this);
    } else {
      LOG_FAT("No RenderLoop in render stack\n");
      exit(1);
    }

    // draw ents
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glUseProgram(graphicsBackend.entShader);
    glBindVertexArray(graphicsBackend.entVAO);

    // ent shapes
    glEnableVertexAttribArray(0);
    GraphicsBackend::updateVBO(graphicsBackend.entvertexVBO,
                               graphicsBackend.entVBOdata.data(),
                               sizeof(GLfloat) * graphicsBackend.entVBOdata.size());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // ent healths
    glEnableVertexAttribArray(1);
    GraphicsBackend::updateVBO(graphicsBackend.entcolorVBO,
                               graphicsBackend.entcolorVBOdata.data(),
                               sizeof(GLfloat) * graphicsBackend.entcolorVBOdata.size());
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glUniform2i(3, World::dim.x, World::dim.y);
    glUniform2f(4, Camera::dim.x, Camera::dim.y);
    glUniform2f(5, Camera::pos.x, Camera::pos.y);

    glDrawArrays(GL_TRIANGLES, 0, graphicsBackend.entVBOdata.size());

    // draw effects
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUseProgram(graphicsBackend.effectShader);
    glBindVertexArray(graphicsBackend.effectVAO);
    glEnableVertexAttribArray(0);
    GraphicsBackend::updateVBO(graphicsBackend.effectVBO,
                               graphicsBackend.effectVBOdata.data(),
                               sizeof(GLfloat) * graphicsBackend.effectVBOdata.size());
    glBindBuffer(GL_ARRAY_BUFFER, graphicsBackend.effectVBO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);
    GraphicsBackend::updateVBO(graphicsBackend.effectcolorVBO,
                               graphicsBackend.effectcolorVBOdata.data(),
                               sizeof(GLfloat) * graphicsBackend.effectcolorVBOdata.size());
    glBindBuffer(GL_ARRAY_BUFFER, graphicsBackend.effectcolorVBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glUniform2i(3, World::dim.x, World::dim.y);
    glUniform2f(4, Camera::dim.x, Camera::dim.y);
    glUniform2f(5, Camera::pos.x, Camera::pos.y);

    glDrawArrays(GL_TRIANGLES, 0, graphicsBackend.effectVBOdata.size());

    // draw GUI
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glUseProgram(graphicsBackend.guiShader);
    glBindVertexArray(graphicsBackend.guiVAO);
    glEnableVertexAttribArray(0);
    GraphicsBackend::updateVBO(graphicsBackend.guiVBO,
                               graphicsBackend.guiVBOdata.data(),
                               sizeof(GLfloat) * graphicsBackend.guiVBOdata.size());
    glBindBuffer(GL_ARRAY_BUFFER, graphicsBackend.guiVBO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);
    GraphicsBackend::updateVBO(graphicsBackend.guicolorVBO,
                               graphicsBackend.guicolorVBOdata.data(),
                               sizeof(GLfloat) * graphicsBackend.guicolorVBOdata.size());
    glBindBuffer(GL_ARRAY_BUFFER, graphicsBackend.guicolorVBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, graphicsBackend.guiVBOdata.size());

    // cleanup drawing
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // render things again
    m_gameStateStack.back()->render(this);

    // Swap buffers
    glfwSwapBuffers(graphicsBackend.window);

    // set prev frame's inputs
    updatePrevInput();

    clock_t endFrame = clock();

    m_deltaTime = clockToMilliseconds(endFrame - beginFrame);
//    double rfps = (1000.0 / m_deltaTime);
    // display rFPS (rendering FPS)
    // std::cout << "rFPS: " << rfps << std::endl;
    fflush(stdout);
    if (m_deltaTime < (1000.0 / K_FPS)) {
      usleep(1000 * ((1000.0 / K_FPS) - m_deltaTime));
//      m_deltaTime = 1000 / K_FPS;
    }

    if (glfwWindowShouldClose(graphicsBackend.window)) {
      m_quit = true;
    }
  }
}

// TODO: Assuming that order of processing doesn't matter??
// TODO: will these happen in-between processing entity updates?

// There's a bug where older key presses sometimes ends up jumbled and gets processed at the wrong time.
void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    LOG_INF("PRESS %.3f", glfwGetTime());
    m_keysDown.insert(key);
  } else if (action == GLFW_RELEASE) {
    LOG_INF("RELEASE %.3f", glfwGetTime());
    m_keysDown.erase(key);
  }
}

void Game::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
  Game::m_mouseX = xpos;
  // TODO: some Y coordinates seem flipped?
  // example case: this vs GUI components
  Game::m_mouseY = K_DISPLAY_SIZE_Y - ypos;
}

void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  if (action == GLFW_PRESS) {
    m_buttonsDown.insert(button);
  } else if (action == GLFW_RELEASE) {
    m_buttonsDown.erase(button);
  }
}

void Game::updatePrevInput() {
  Game::m_keysDownPrev.empty();
  Game::m_buttonsDownPrev.empty();
  Game::m_keysDownPrev = m_keysDown;
  Game::m_buttonsDownPrev = m_buttonsDown;
}
