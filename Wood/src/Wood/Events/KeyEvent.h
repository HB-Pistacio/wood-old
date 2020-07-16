#pragma once
#include "Event.h"

namespace Wood {

// General KeyEvent class to be reused be pressed and released events
class KeyEvent : public Event {
 public:
  EVENT_TYPE_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
  inline int GetKeyCode() const { return m_KeyCode; }

 protected:
  KeyEvent(int keycode) : m_KeyCode(keycode) {}
  int m_KeyCode;
};

class KeyPressedEvent : public KeyEvent {
 public:
  KeyPressedEvent(int keycode, bool repeated)
      : KeyEvent(keycode), m_Repeated(repeated) {}
  inline int GetRepeated() const { return m_Repeated; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << m_KeyCode << m_Repeated ? "(repeated)" : "";
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyPressed)

 private:
  bool m_Repeated;
};

class KeyReleasedEvent : public KeyEvent {
 public:
  KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << m_KeyCode;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyReleased)
};

}  // namespace Wood