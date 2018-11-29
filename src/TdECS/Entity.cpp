/** 
 * TdECSEntity.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "Entity.hpp"

#include "TdECS/TdECSSystems/System.hpp"

glm::dvec2 Entity::getPosition() {
  if (this->has<TilePosition>()) {
    return this->get<TilePosition>()->m_xy * 16 +
        glm::ivec2(K_DISPLAY_SIZE_X, K_DISPLAY_SIZE_Y) / 2;
  } else if (this->has<Position>()) {
    return glm::dvec2(this->get<Position>()->m_p);
  } else {
    std::string msg = "missing component: general position";
    throw MissingComponentException(msg);
  }
};

glm::dvec2 Entity::getCenterPosition() {
  if (this->has<TilePosition>()) {
    return this->get<TilePosition>()->m_xy * 16 +
        glm::ivec2(K_DISPLAY_SIZE_X, K_DISPLAY_SIZE_Y) / 2 +
        glm::ivec2(this->get<Shape>()->m_dimensions / 2.0);
  } else if (this->has<Position>()) {
    return this->get<Position>()->m_p +
        this->get<Shape>()->m_dimensions / 2.0;
  } else {
    std::string msg = "missing component: general position";
    throw MissingComponentException(msg);
  }
};

Entity::Entity(System *GUISystem) : m_id(GUISystem->m_nextEntityId), m_system(GUISystem) {
    m_components = std::map<int, Component *>();
}

template <class T>
void Entity::addComponent(T component) {
  component.m_entID = m_id;

  if (m_system) {
    m_components[classToInt<T>::value] = m_system->addComponent(component);
  } else {
    printf("NO SYSTEM\n");
    exit(1);
  }
}

Entity *Entity::addPlayerBase(Game *game, System *system) {
  auto entity = std::make_unique<Entity>(system);

  auto graphicsComp = Graphics(convertColorType(0xFFFFFFFF));
  auto shapeComp = Shape(48, 48);
  auto tilePosComp = TilePosition(0, 0);
  auto healthComp = Health(3000000, 2);
  auto attackComp = Attack(0, 10, 0.3, Attack::SHOOTER);
  auto laserComp = LaserShooter();

  // TODO: currently make a new copy of components for temp
  // but we want to remove this later.
  entity->addComponent(graphicsComp);
  entity->addComponent(shapeComp);
  entity->addComponent(tilePosComp);
  entity->addComponent(healthComp);
  entity->addComponent(attackComp);
  entity->addComponent(laserComp);

  auto pt = entity.get();
  system->addEntity(game, std::move(entity));
  return pt;
}


Entity *Entity::addTower(Game *game, System *system, int tileX,
                        int tileY) {
  auto entity = std::make_unique<Entity>(system);

  auto graphicsComp = Graphics(convertColorType(0xFFFFFFFF));
  auto shapeComp = Shape(32, 32);
  auto tilePosComp = TilePosition(tileX, tileY);
  auto healthComp = Health(100, 0);
  auto attackComp = Attack(0, 5, 1.5, Attack::SHOOTER);
  auto laserComp = LaserShooter();

  entity->addComponent(graphicsComp);
  entity->addComponent(shapeComp);
  entity->addComponent(tilePosComp);
  entity->addComponent(healthComp);
  entity->addComponent(attackComp);
  entity->addComponent(laserComp);

  auto pt = entity.get();
  system->addEntity(game, std::move(entity));

  return pt;
}

Entity *Entity::addWall(Game *game, System *system, int tileX,
                       int tileY) {
  auto entity = std::make_unique<Entity>(system);

  auto graphicsComp = Graphics(convertColorType(0xFFFFFFFF));
  auto shapeComp = Shape(16, 16);
  auto tilePosComp = TilePosition(tileX, tileY);
  auto healthComp = Health(500, 2);

  entity->addComponent(graphicsComp);
  entity->addComponent(shapeComp);
  entity->addComponent(tilePosComp);
  entity->addComponent(healthComp);

  auto pt = entity.get();
  system->addEntity(game, std::move(entity));

  return pt;
}

Entity *Entity::addEnemy(Game *game, System *system, double x,
                        double y) {
  auto entity = std::make_unique<Entity>(system);

  auto graphicsComp = Graphics(convertColorType(0xFFC06060));
  auto shapeComp = Shape(16, 16);
  auto positionComp = Position(x, y);
  auto physicsComp = Physics();
  auto healthComp = Health(10, 0);
  auto attackComp = Attack(1, 3, 0.5, Attack::FIGHTER);
  auto laserComp = LaserShooter();
  auto pathingComp = Pathing();

  entity->addComponent(graphicsComp);
  entity->addComponent(shapeComp);
  entity->addComponent(positionComp);
  entity->addComponent(physicsComp);
  entity->addComponent(healthComp);
  entity->addComponent(attackComp);
  entity->addComponent(laserComp);
  entity->addComponent(pathingComp);

  auto pt = entity.get();
  system->addEntity(game, std::move(entity));

  return pt;
}