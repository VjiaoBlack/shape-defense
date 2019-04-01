/**
 * CircularBuffer.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "CircularBuffer.hpp"

int CircularBuffer::add(float elem) {
  if (m_head == m_tail - 1 || (m_head == m_length - 1 && m_tail == 0)) {
    return false; // full
  }

  // if we're simply already on a valid element,
  // move until we get to an empty space
  while (m_alive[m_head]) {
    m_head++;

    if (m_head >= m_length) {
      m_head -= m_length;
    }
    if (m_head == m_tail - 1 || (m_head == m_length - 1 && m_tail == 0)) {
      return false; // full
    }
  }
  m_arr[m_head]   = elem;
  m_alive[m_head] = true;
  int past = m_head;
  m_head++;

  if (m_head >= m_length) {
    m_head -= m_length;
  }

  return past;
}

bool CircularBuffer::remove(int pos) {
  if (!m_alive[pos]) {
    return false;
  }

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