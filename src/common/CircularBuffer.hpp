#pragma once
/**
 * CircularBuffer.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <vector>

class CircularBuffer {
 public:
  int m_length;
  int m_head = 0; // most recently added
  int m_tail = 0; // least recently added

  std::vector<float> m_arr;
  std::vector<bool>  m_alive;

  CircularBuffer(int length)
      : m_length(length) {
    m_arr.resize(length);
    m_alive.resize(length);
  };

  // TODO: optimize these for bulk add/removes
  int add(float elem);
  bool remove(int pos);

  size_t size() { return m_length; }
  float *data() { return m_arr.data(); }

 private:
};
