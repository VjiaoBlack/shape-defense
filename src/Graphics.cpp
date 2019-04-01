#include "Graphics.hpp"

#include <TdECS/TdECSSystems/SystemUtils.hpp>
#include <Utils.hpp>
#include <cstring>

GraphicsBackend graphicsBackend;

// TODO: refactor into a .obj file, or similar
void addEnt(std::vector<GLfloat> &buf, int pos,
            glm::vec2 xy, float width, float thickness) {
  glm::vec2 off_vec = glm::vec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2);

  // left
  addTriangle(buf, pos + 9 * 0,
              xy - off_vec,
              xy - off_vec + glm::vec2(thickness, 0),
              xy - off_vec + glm::vec2(0, width));

  addTriangle(buf, pos + 9 * 1,
              xy - off_vec + glm::vec2(thickness, 0),
              xy - off_vec + glm::vec2(thickness, width),
              xy - off_vec + glm::vec2(0, width));

  // right
  addTriangle(buf, pos + 9 * 2,
              xy - off_vec + glm::vec2(width, 0),
              xy - off_vec + glm::vec2(width - thickness, 0),
              xy - off_vec + glm::vec2(width - thickness, width));

  addTriangle(buf, pos + 9 * 3,
              xy - off_vec + glm::vec2(width, 0),
              xy - off_vec + glm::vec2(width, width),
              xy - off_vec + glm::vec2(width - thickness, width));

  // bottom
  addTriangle(buf, pos + 9 * 4,
              xy - off_vec + glm::vec2(thickness, 0),
              xy - off_vec + glm::vec2(width - thickness, 0),
              xy - off_vec + glm::vec2(width - thickness, thickness));

  addTriangle(buf, pos + 9 * 5,
              xy - off_vec + glm::vec2(thickness, 0),
              xy - off_vec + glm::vec2(thickness, thickness),
              xy - off_vec + glm::vec2(width - thickness, thickness));

  // top
  addTriangle(buf, pos + 9 * 6,
              xy - off_vec + glm::vec2(thickness, width),
              xy - off_vec + glm::vec2(width - thickness, width),
              xy - off_vec + glm::vec2(width - thickness, width - thickness));

  addTriangle(buf, pos + 9 * 7,
              xy - off_vec + glm::vec2(thickness, width),
              xy - off_vec + glm::vec2(thickness, width - thickness),
              xy - off_vec + glm::vec2(width - thickness, width - thickness));
}

Triangle::Triangle(CircularBuffer *buffer, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3)
    : m_buffer(buffer), m_hasColor(false) {
  m_indices[0] = m_buffer->add(p1.x - K_DISPLAY_SIZE_X / 2.0);
  m_indices[1] = m_buffer->add(p1.y - K_DISPLAY_SIZE_Y / 2.0);

  m_indices[2] = m_buffer->add(p2.x - K_DISPLAY_SIZE_X / 2.0);
  m_indices[3] = m_buffer->add(p2.y - K_DISPLAY_SIZE_Y / 2.0);

  m_indices[4] = m_buffer->add(p3.x - K_DISPLAY_SIZE_X / 2.0);
  m_indices[5] = m_buffer->add(p3.y - K_DISPLAY_SIZE_Y / 2.0);

}

Triangle::Triangle(CircularBuffer *buffer, CircularBuffer *colorBuffer,
                   glm::vec2 p1, glm::vec2 p2, glm::vec2 p3,
                   glm::vec3 color)
    : m_buffer(buffer), m_colorBuffer(colorBuffer), m_hasColor(true) {
  m_indices[0] = m_buffer->add(p1.x - K_DISPLAY_SIZE_X / 2.0);
  m_indices[1] = m_buffer->add(p1.y - K_DISPLAY_SIZE_Y / 2.0);
  m_indices[2] = m_buffer->add(p2.x - K_DISPLAY_SIZE_X / 2.0);
  m_indices[3] = m_buffer->add(p2.y - K_DISPLAY_SIZE_Y / 2.0);
  m_indices[4] = m_buffer->add(p3.x - K_DISPLAY_SIZE_X / 2.0);
  m_indices[5] = m_buffer->add(p3.y - K_DISPLAY_SIZE_Y / 2.0);

  m_colors[0] = m_colorBuffer->add(color.r);
  m_colors[1] = m_colorBuffer->add(color.g);
  m_colors[2] = m_colorBuffer->add(color.b);
  m_colors[3] = m_colorBuffer->add(color.r);
  m_colors[4] = m_colorBuffer->add(color.g);
  m_colors[5] = m_colorBuffer->add(color.b);
  m_colors[6] = m_colorBuffer->add(color.r);
  m_colors[7] = m_colorBuffer->add(color.g);
  m_colors[8] = m_colorBuffer->add(color.b);
}

void Triangle::update(glm::vec3 color) {
  if (m_buffer && m_hasColor) {
    m_colorBuffer->m_arr[m_colors[0]] = color.r;
    m_colorBuffer->m_arr[m_colors[1]] = color.g;
    m_colorBuffer->m_arr[m_colors[2]] = color.b;
    m_colorBuffer->m_arr[m_colors[3]] = color.r;
    m_colorBuffer->m_arr[m_colors[4]] = color.g;
    m_colorBuffer->m_arr[m_colors[5]] = color.b;
    m_colorBuffer->m_arr[m_colors[6]] = color.r;
    m_colorBuffer->m_arr[m_colors[7]] = color.g;
    m_colorBuffer->m_arr[m_colors[8]] = color.b;
  }
}

void Triangle::update(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec3 color) {
  if (m_buffer) {
    m_buffer->m_arr[m_indices[0]] = p1.x - K_DISPLAY_SIZE_X / 2.0;
    m_buffer->m_arr[m_indices[1]] = p1.y - K_DISPLAY_SIZE_Y / 2.0;
    m_buffer->m_arr[m_indices[2]] = p2.x - K_DISPLAY_SIZE_X / 2.0;
    m_buffer->m_arr[m_indices[3]] = p2.y - K_DISPLAY_SIZE_Y / 2.0;
    m_buffer->m_arr[m_indices[4]] = p3.x - K_DISPLAY_SIZE_X / 2.0;
    m_buffer->m_arr[m_indices[5]] = p3.y - K_DISPLAY_SIZE_Y / 2.0;

    if (m_hasColor) {
      this->update(color);
    }
  }
}

void Triangle::destroy() {
  if (m_buffer) {
    m_buffer->remove(m_indices[0]);
    m_buffer->remove(m_indices[1]);
    m_buffer->remove(m_indices[2]);
    m_buffer->remove(m_indices[3]);
    m_buffer->remove(m_indices[4]);
    m_buffer->remove(m_indices[5]);
    m_buffer = nullptr;

    if (m_hasColor) {
      m_colorBuffer->remove(m_colors[0]);
      m_colorBuffer->remove(m_colors[1]);
      m_colorBuffer->remove(m_colors[2]);
      m_colorBuffer->remove(m_colors[3]);
      m_colorBuffer->remove(m_colors[4]);
      m_colorBuffer->remove(m_colors[5]);
      m_colorBuffer->remove(m_colors[6]);
      m_colorBuffer->remove(m_colors[7]);
      m_colorBuffer->remove(m_colors[8]);
    }
  }
}