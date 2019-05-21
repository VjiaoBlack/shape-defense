#pragma once
/**
 * TdGUIEntity.hpp
 *
 * Victor Jiao
 *
 * Each GUI object with be a TdGUIEntity with various Components.
 *
 * I rely on virtual functions because GUI objects are usually not
 * computationally
 * the limiting factor of the game (there's not usually many GUI objects on
 * screen).
 */

#include <GUI/Components/GUIComponent.hpp>
#include <GUI/Components/GUIContainerComponent.hpp>
#include <GUI/Components/GUIGraphicsComponent.hpp>
#include <GUI/Components/GUITextComponent.hpp>
#include <GUI/Systems/GUISystem.hpp>
#include <exception>
#include <map>
#include <stdexcept>

class MissingGUIComponentException : public std::runtime_error {
public:
  MissingGUIComponentException(const string &__arg) : runtime_error(__arg) {}
};

class GUIEntity {
public:
  // add component pointers to this tuple later
  // TODO: restrict m_components access
  std::map<string, GUIComponent *> m_components;
  GUISystem *m_GUISystem;

  GUIEntity() = delete;
  GUIEntity(GUISystem *GUISystem) { m_GUISystem = GUISystem; }
  template <class T> void addComponent(unique_ptr<T> &&component) {
    component->m_ent = this;
    m_components[typeid(T).name()] = component.get();
    if (m_GUISystem) {
      m_GUISystem->addComponent(std::move(component));
    }
  }

  template <class T> T *get() {
    if (!m_components.count(typeid(T).name())) {
      string msg = "missing component: ";
      msg += typeid(T).name();
      throw MissingGUIComponentException(msg);
    }
    return static_cast<T *>(m_components[typeid(T).name()]);
  }


  static GUIEntity *addButton(Game *game, GUISystem *system,
                                MY_Rect rect, std::string label) {
    MY_Rect textRect = rect;

    auto entity = std::make_unique<GUIEntity>(system);

    auto graphicsComp = std::make_unique<GUIGraphicsComponent>(rect);
    auto textComp =
        std::make_unique<GUITextComponent>(game, label, textRect);
    auto mouseComp = std::make_unique<GUIMouseComponent>();
    auto highlightComp = std::make_unique<GUIHighlightComponent>();
    auto clickComp = std::make_unique<GUIClickableComponent>();

    entity->addComponent(std::move(graphicsComp));
    entity->addComponent(std::move(textComp));
    entity->addComponent(std::move(mouseComp));
    entity->addComponent(std::move(highlightComp));
    entity->addComponent(std::move(clickComp));

    auto pt = entity.get();
    system->m_entities.push_back(std::move(entity));
    return pt;
  }

  static GUIEntity *addVerticalMenu(Game *game, GUISystem *system,
                                      MY_Rect rect,
                                      std::vector<std::string> labels) {
    MY_Rect textRect = rect;

    auto entity = std::make_unique<GUIEntity>(system);

    auto containerComp = std::make_unique<GUIContainerComponent>();

    double height =
        static_cast<double>(rect.h -
                            containerComp->m_spacing * (labels.size() - 1)) /
        static_cast<double>(labels.size());
    for (int i = 0; i < labels.size(); i++) {
      MY_Rect buttonRect = {
          rect.x, static_cast<int>(
                      round(K_DISPLAY_SIZE_Y / 2 - (-rect.y + i * (height +
          containerComp->m_spacing)))),
          rect.w, static_cast<int>(round(height))};
      containerComp->m_buttons.push_back(
          addButton(game, system, buttonRect, labels[i]));
    }

    entity->addComponent(std::move(containerComp));

    auto pt = entity.get();
    system->m_entities.push_back(std::move(entity));
    return pt;
  }

  static GUIEntity *addHorizontalMenu(Game *game, GUISystem *system,
                                        MY_Rect rect,
                                        std::vector<std::string> labels) {
    MY_Rect textRect = rect;

    auto entity = std::make_unique<GUIEntity>(system);

    auto containerComp = std::make_unique<GUIContainerComponent>();

    double width =
        static_cast<double>(rect.w -
                            containerComp->m_spacing * (labels.size() - 1)) /
        static_cast<double>(labels.size());
    for (int i = 0; i < labels.size(); i++) {
      MY_Rect buttonRect = {
          static_cast<int>(
              round(rect.x + i * (width + containerComp->m_spacing))),
          rect.y, static_cast<int>(round(width)), rect.h};
      containerComp->m_buttons.push_back(
          addButton(game, system, buttonRect, labels[i]));
    }

    entity->addComponent(std::move(containerComp));

    auto pt = entity.get();
    system->m_entities.push_back(std::move(entity));
    return pt;
  }
};
