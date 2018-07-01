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

#include <TdGUI/TdGUIComponents/TdGUIComponent.hpp>
#include <TdGUI/TdGUIComponents/TdGUIContainerComponent.hpp>
#include <TdGUI/TdGUIComponents/TdGUIGraphicsComponent.hpp>
#include <TdGUI/TdGUIComponents/TdGUITextComponent.hpp>
#include <TdGUI/TdGUISystems/TdGUISystem.hpp>
#include <exception>
#include <map>
#include <stdexcept>

class TdGUIMissingComponentException : public std::runtime_error {
public:
  TdGUIMissingComponentException(const string &__arg) : runtime_error(__arg) {}
};

class TdGUIEntity {
public:
  // add component pointers to this tuple later
  // TODO: restrict m_components access
  std::map<string, TdGUIComponent *> m_components;
  TdGUISystem *m_GUISystem;

  TdGUIEntity() = delete;
  TdGUIEntity(TdGUISystem *GUISystem) { m_GUISystem = GUISystem; }
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
      throw TdGUIMissingComponentException(msg);
    }
    return static_cast<T *>(m_components[typeid(T).name()]);
  }

  static TdGUIEntity *addButton(TdGame *game, TdGUISystem *system,
                                SDL_Rect rect, std::string &&label) {
    SDL_Rect textRect = rect;

    auto entity = std::make_unique<TdGUIEntity>(system);

    auto graphicsComp = std::make_unique<TdGUIGraphicsComponent>(rect);
    auto textComp =
        std::make_unique<TdGUITextComponent>(game, std::move(label), textRect);
    auto mouseComp = std::make_unique<TdGUIMouseComponent>();
    auto highlightComp = std::make_unique<TdGUIHighlightComponent>();
    auto clickComp = std::make_unique<TdGUIClickableComponent>();

    entity->addComponent(std::move(graphicsComp));
    entity->addComponent(std::move(textComp));
    entity->addComponent(std::move(mouseComp));
    entity->addComponent(std::move(highlightComp));
    entity->addComponent(std::move(clickComp));

    auto pt = entity.get();
    system->m_entities.push_back(std::move(entity));
    return pt;
  }

  static TdGUIEntity *addVerticalMenu(TdGame *game, TdGUISystem *system,
                                      SDL_Rect rect,
                                      std::vector<std::string> &&labels) {
    SDL_Rect textRect = rect;

    auto entity = std::make_unique<TdGUIEntity>(system);

    auto containerComp = std::make_unique<TdGUIContainerComponent>();

    double height =
        static_cast<double>(rect.h -
                            containerComp->m_spacing * (labels.size() - 1)) /
        static_cast<double>(labels.size());
    for (int i = 0; i < labels.size(); i++) {
      SDL_Rect buttonRect = {
          rect.x, static_cast<int>(
                      round(rect.y + i * (height + containerComp->m_spacing))),
          rect.w, static_cast<int>(round(height))};
      containerComp->m_buttons.push_back(
          addButton(game, system, buttonRect, std::move(labels[i])));
    }

    entity->addComponent(std::move(containerComp));

    auto pt = entity.get();
    system->m_entities.push_back(std::move(entity));
    return pt;
  }

  static TdGUIEntity *addHorizontalMenu(TdGame *game, TdGUISystem *system,
                                        SDL_Rect rect,
                                        std::vector<std::string> &&labels) {
    SDL_Rect textRect = rect;

    auto entity = std::make_unique<TdGUIEntity>(system);

    auto containerComp = std::make_unique<TdGUIContainerComponent>();

    double width =
        static_cast<double>(rect.w -
                            containerComp->m_spacing * (labels.size() - 1)) /
        static_cast<double>(labels.size());
    for (int i = 0; i < labels.size(); i++) {
      SDL_Rect buttonRect = {
          static_cast<int>(
              round(rect.x + i * (width + containerComp->m_spacing))),
          rect.y, static_cast<int>(round(width)), rect.h};
      containerComp->m_buttons.push_back(
          addButton(game, system, buttonRect, std::move(labels[i])));
    }

    entity->addComponent(std::move(containerComp));

    auto pt = entity.get();
    system->m_entities.push_back(std::move(entity));
    return pt;
  }
};
