#pragma once
/** 
 * LevelManager.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

class Game;

class LevelManager {
 public:
  std::default_random_engine m_rg;
  std::uniform_real_distribution<> m_rd;

  std::string m_titleText = "BLEP";
  MY_Color textColor0 = {0, 255, 0, 255};
  int text_width;
  int text_height;

  int m_enemySpawnTimer = 0;
  int m_nextEnemy = 20;
  int m_lastMarkerDist = 10;
  int m_curMarker = 10;
  int m_curLevel = 1;
  int m_curBossesSpawned = 0;

//  sdl_texture_pt m_titleTexture;

  LevelManager(Game* game);

  void update(Game* game);
  void render(Game* game);
 private:
  void addRandomEnemy(Game* game, double dist);
  void addRandomBoss(Game* game, double dist);

};

