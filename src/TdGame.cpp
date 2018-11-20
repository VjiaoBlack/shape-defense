
#include "TdGame.hpp"
#include "TdRenderLoop/TdGameLoop.hpp"
#include "TdRenderLoop/TdMainMenuLoop.hpp"

#include <deque>
#include <TdECS/TdECSEntity.hpp>

void TdGame::setupSDL() {
  // Initialize
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOG_FAT("SDL could not initialize - SDL Error: %s", SDL_GetError());
    exit(1);
  }

  // nearest neighbor scaling
  SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0");

  // "antialiasing"
  //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

  // Create window
  m_SDLWindow = TrWindow(SDL_CreateWindow("athena", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, sz(K_DISPLAY_SIZE_X),
                                          sz(K_DISPLAY_SIZE_Y), SDL_WINDOW_SHOWN));
  if (m_SDLWindow == nullptr) {
    LOG_FAT("Window could not be created - SDL Error: %s", SDL_GetError());
    exit(1);
  }

  // Create renderer for window
  m_SDLRenderer = TrRenderer(SDL_CreateRenderer(m_SDLWindow, -1, SDL_RENDERER_ACCELERATED));
  if (m_SDLRenderer == nullptr) {
    LOG_FAT("Renderer could not be created - SDL Error: %s", SDL_GetError());
    exit(1);
  }

  SDL_SetRenderDrawBlendMode(m_SDLRenderer, SDL_BLENDMODE_BLEND);

  if (TTF_Init() == -1) {
    LOG_FAT("TTF_Init: %s", TTF_GetError());
    exit(2);
  }

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    LOG_FAT("SDL_image could not initialize! SDL_image Error: %s", IMG_GetError());
    exit(2);
  }


}

TdGame::TdGame()
    : m_quit(false),
      m_gameStateTransition(nullptr),
      m_deltaTime(0),
      m_frames(0),
      m_frameRate(30) {
  this->setupSDL();

  // initialize framerate counter
  m_deltaTime = 0;
  m_frames = 0;
  m_frameRate = 30;

  m_font.reset(TTF_OpenFont("anirb.ttf", 72));
  if (!m_font) {
    LOG_FAT("TTF_OpenFont: %s", TTF_GetError());
    // handle error
    exit(2);
  }

  m_menuFont.reset(TTF_OpenFont("anirb.ttf", 36));
  if (!m_menuFont) {
    LOG_FAT("TTF_OpenFont: %s", TTF_GetError());
    // handle error
    exit(2);
  }

  // setup game loop
  auto tempmenu = make_shared<TrMainMenuLoop>(this);
  m_gameStateStack.push_back(std::move(tempmenu));

  // setup entities
  m_entitySystem = make_unique<TdECSSystem>();

  TdECSEntity::addPlayerBase(this, m_entitySystem.get());
}

TdGame::~TdGame() {
  while (!m_gameStateStack.empty()) {
    m_gameStateStack.pop_back();
  }
}

void TdGame::handleKey(int SDLKey) {
  switch (SDLKey) {
    case SDLK_q:m_quit = true;
    default:break;
  }
}

void TdGame::run() {
  while (!m_quit) {
    clock_t beginFrame = clock();

    // Update keysDown and buttonsDown
    handleInput();

    // Assuming that order of processing doesn't matter.
    for (int it : m_keysDown) {
      handleKey(it);
    }

    // clear screen
    SDL_SetRenderDrawColor(m_SDLRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(m_SDLRenderer);

    if (m_gameStateTransition) {
      m_gameStateTransition->render(this);
      TdRenderLoop *loop = m_gameStateTransition->update(this);
      if (!loop) {
        m_gameStateTransition.reset(nullptr);
      }
    } else {
      m_gameStateStack.back()->render(this);
      TdRenderLoop *loop = m_gameStateStack.back()->update(this);
    }

    // update screen
    SDL_RenderPresent(m_SDLRenderer);

    // do render stuff
    clock_t endFrame = clock();

    m_deltaTime = clockToMilliseconds(endFrame - beginFrame);
    double rfps = (1000.0 / m_deltaTime);
    // display rFPS (rendering FPS)
    std::cout << "rFPS: " << rfps << std::endl;
    fflush(stdout);
    if (m_deltaTime < (1000.0 / 30.0)) {
      usleep(1000 * ((1000.0 / 30.0) - m_deltaTime));
      m_deltaTime = 1000 / 30.0;
    }
  }
}

void TdGame::handleInput() {
  m_keysDownPrev.empty();
  m_buttonsDownPrev.empty();
  m_keysDownPrev = m_keysDown;
  m_buttonsDownPrev = m_buttonsDown;

  while (SDL_PollEvent(&m_SDLEvent) != 0) {
    if (m_SDLEvent.type == SDL_QUIT) {
      m_quit = true;
    } else if (m_SDLEvent.type == SDL_KEYDOWN) {
      m_keysDown.insert(m_SDLEvent.key.keysym.sym);
    } else if (m_SDLEvent.type == SDL_KEYUP) {
      m_keysDown.erase(m_SDLEvent.key.keysym.sym);
    } else if (m_SDLEvent.type == SDL_MOUSEBUTTONDOWN) {
      m_buttonsDown.insert(m_SDLEvent.button.button);
    } else if (m_SDLEvent.type == SDL_MOUSEBUTTONUP) {
      m_buttonsDown.erase(m_SDLEvent.button.button);
    } else if (m_SDLEvent.type == SDL_MOUSEMOTION) {
      m_mouseX = m_SDLEvent.motion.x;
      m_mouseY = m_SDLEvent.motion.y;
    }
  }
}
