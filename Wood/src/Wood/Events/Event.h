#pragma once

#include "pchwd.h"
#include "spdlog/fmt/ostr.h"

namespace Wood {
// Events in Wood are currently blocking, meaning that as soon as an even fires
// it will block the main thread until the event handler has run.
// An alternative strategy would be to queue events in a buffer when they fire.
// Then as part of the update loop, we could empty the buffer,
// by handling all the queued events in it. Anyway - blocking events are fine
// for now 🤷‍♂️

enum class EventType {
  None = 0,
  WindowClose,
  WindowResize,
  WindowFocus,
  WindowBlur,
  WindowMoved,
  AppTick,
  AppUpdate,
  AppRender,
  KeyPressed,
  KeyReleased,
  MouseButtonPressed,
  MouseButtonReleased,
  MouseMoved,
  MouseScrolled
};

enum EventCategory {
  None = 0,
  EventCategoryApplication = (1 << 0),
  EventCategoryInput = (1 << 1),
  EventCategoryKeyboard = (1 << 2),
  EventCategoryMouse = (1 << 3),
  EventCategoryMouseButton = (1 << 4),
};

#define EVENT_CLASS_TYPE(type)                                                \
  static EventType GetStaticType() { return EventType::type; }                \
  virtual EventType GetEventType() const override { return GetStaticType(); } \
  virtual const char* GetName() const override { return #type; }

#define EVENT_TYPE_CATEGORY(category) \
  virtual int GetCategoryFlags() const override { return category; }

class Event {
  friend class EventDispatcher;

 public:
  virtual EventType GetEventType() const = 0;
  virtual const char* GetName() const = 0;
  virtual int GetCategoryFlags() const = 0;
  virtual std::string ToString() const { return GetName(); }

  inline bool IsInCategory(EventCategory category) {
    return GetCategoryFlags() & category;
  }

  template <typename OStream>
  friend OStream& operator<<(OStream& os, const Event& e) {
    return os << e.ToString();
  }

  bool Handled = false;
};

class EventDispatcher {
  template <typename T>
  using EventFn = std::function<bool(T&)>;

 public:
  EventDispatcher(Event& event) : m_Event(event) {}

  template <typename T>
  bool Dispatch(EventFn<T> func) {
    if (m_Event.GetEventType() == T::GetStaticType()) {
      m_Event.Handled = func(*(T*)&m_Event);
      return true;
    }

    return false;
  }

 private:
  Event& m_Event;
};

}  // namespace Wood
