#pragma once
/**
 * TdECSSystemUtils.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <memory>
#include <vector>

class TdGame;

template <class T>
inline void updateComponents(TdGame* game,
                             std::vector<std::unique_ptr<T>>& vec) {
  for (auto c = vec.begin(); c != vec.end();) {
    if ((*c)->m_dead) {
      c = vec.erase(c);
    } else {
      (*c)->update(game);
      c++;
    }
  }
}
//
//std::list<typename std::vector<std::unique_ptr<T>>::iterator> to_remove;
//
//for (auto c = vec.begin(); c != vec.end(); c++) {
//if ((*c)->m_dead) {
//to_remove.push_back(c);
//} else {
//(*c)->update(game);
//}
//}
//
//for (auto c : to_remove) {
//vec.erase(*c);
//}