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

Entity::Entity(System *system)
    : m_id(system->m_openSlots[system->m_head])
    , m_system(system) {
  system->m_openSlots[system->m_head] = 0; // clear mem
  system->m_head += 1;
  if (system->m_head >= k_MAX_ENTS) {
    system->m_head = 0;
  }

  if (system->m_head == system->m_tail) {
    LOG_FAT("overflow of ents???, exiting.");
    exit(1);
  }

//  m_components = std::map<int, Component *>();
  for (auto& c : m_components) {
    c = nullptr;
  }
}

void Entity::die() {
  for (auto cp : m_components) {
//    cp.second->m_alive = false;
    if (cp)
      cp->m_alive = false;
  }
  m_alive = false;
  m_system->m_tail += 1;
  if (m_system->m_tail >= k_MAX_ENTS) {
    m_system->m_tail = 0;
  }
  if (m_system->m_head == m_system->m_tail) {
    LOG_FAT("overflow of ents???, exiting.");
    exit(1);
  }
  if (m_system->m_openSlots[m_system->m_tail] != 0) {

    LOG_FAT("... what? not enroaching onto 0 id for a new open slot... %d\n", m_system->m_openSlots[m_system->m_tail]);
    exit(1);
  }

  m_system->m_openSlots[m_system->m_tail] = m_id;
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

template<>
void Entity::addEntity<EntityType::BASE>(Game* game, System* system) {
  auto entity = Entity(system);

  auto graphicsComp = Graphics(convertColorType(EntityColor<EntityType::BASE>::c));
  auto shapeComp = Shape(EntityShape<EntityType::BASE>::w, EntityShape<EntityType::BASE>::h);
  auto tilePosComp = TilePosition(0, 0);
  auto healthComp = Health(3000000, 2);
  auto attackComp = Attack(Attack::ALLIED, 10, 0.3, Attack::SHOOTER);
  auto laserComp = LaserShooter();

  entity.addComponent(graphicsComp);
  entity.addComponent(shapeComp);
  entity.addComponent(tilePosComp);
  entity.addComponent(healthComp);
  entity.addComponent(attackComp);
  entity.addComponent(laserComp);

  auto pt = entity;
  system->addEntity(game, entity);
}

template<>
void Entity::addEntity<EntityType::TOWER>(Game* game, System* system, int tileX, int tileY) {
  auto entity = Entity(system);

  auto graphicsComp = Graphics(convertColorType(EntityColor<EntityType::TOWER>::c));
  auto shapeComp = Shape(EntityShape<EntityType::TOWER>::w, EntityShape<EntityType::TOWER>::h);
  auto tilePosComp = TilePosition(tileX, tileY);
  auto healthComp = Health(100, 0);
  auto attackComp = Attack(Attack::ALLIED, 5, 1.5, Attack::SHOOTER);
  auto laserComp = LaserShooter();

  entity.addComponent(graphicsComp);
  entity.addComponent(shapeComp);
  entity.addComponent(tilePosComp);
  entity.addComponent(healthComp);
  entity.addComponent(attackComp);
  entity.addComponent(laserComp);

  auto pt = entity;
  system->addEntity(game, entity);
}

template<>
void Entity::addEntity<EntityType::WALL>(Game *game, System *system, int tileX,
                     int tileY) {
  auto entity = Entity(system);

  auto graphicsComp = Graphics(convertColorType(EntityColor<EntityType::WALL>::c));
  auto shapeComp = Shape(EntityShape<EntityType::WALL>::w, EntityShape<EntityType::WALL>::h);
  auto tilePosComp = TilePosition(tileX, tileY);
  auto healthComp = Health(500, 2);

  entity.addComponent(graphicsComp);
  entity.addComponent(shapeComp);
  entity.addComponent(tilePosComp);
  entity.addComponent(healthComp);

  auto pt = entity;
  system->addEntity(game, entity);
}

template<>
void Entity::addEntity<EntityType::ENEMY>(Game *game, System *system, double x,
                      double y) {
  auto entity = Entity(system);

  auto graphicsComp = Graphics(convertColorType(EntityColor<EntityType::ENEMY>::c));
  auto shapeComp = Shape(EntityShape<EntityType::ENEMY>::w, EntityShape<EntityType::ENEMY>::h);
  auto positionComp = Position(x, y);
  auto physicsComp = Physics();
  auto healthComp = Health(10, 0);
  auto attackComp = Attack(Attack::ENEMY, 3, 0.5, Attack::FIGHTER);
  auto laserComp = LaserShooter();
  auto pathingComp = Pathing();

  entity.addComponent(graphicsComp);
  entity.addComponent(shapeComp);
  entity.addComponent(positionComp);
  entity.addComponent(physicsComp);
  entity.addComponent(healthComp);
  entity.addComponent(attackComp);
  entity.addComponent(laserComp);
  entity.addComponent(pathingComp);

  auto pt = entity;
  system->addEntity(game, entity);
}

template<>
void Entity::addEntity(Game *game, System *system, EntityType type) {
  switch (type) {
    case EntityType::BASE:
      Entity::addEntity<EntityType::BASE>(game, system);
      break;
  }
}

template<>
void Entity::addEntity(Game *game, System *system, EntityType type, int x, int y) {
  switch (type) {
    case EntityType::TOWER:
      Entity::addEntity<EntityType::TOWER>(game, system, x, y);
      break;
    case EntityType::WALL:
      Entity::addEntity<EntityType::WALL>(game, system, x, y);
      break;
  }
}

template<>
void Entity::addEntity(Game *game, System *system, EntityType type, double x, double y) {
  switch (type) {
    case EntityType::ENEMY:
      Entity::addEntity<EntityType::ENEMY>(game, system, x, y);
      break;
  }
}
