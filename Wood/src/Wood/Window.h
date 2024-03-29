#pragma once

#include "pchwd.h"
#include "Wood/Events/Event.h"

namespace Wood {

struct WindowProps {
  std::string Title;
  unsigned int Width;
  unsigned int Height;

  WindowProps(const std::string& title = "Wood Engine",
              unsigned int width = 1280,
              unsigned int height = 720)
      : Title(title), Width(width), Height(height) {}
};

class Window {
 public:
  using EventCallBackFn = std::function<void(Event&)>;
  virtual ~Window() {}

  virtual void OnUpdate() = 0;

  virtual unsigned int GetWidth() const = 0;
  virtual unsigned int GetHeight() const = 0;

  virtual void SetEventCallback(const EventCallBackFn& callback) = 0;
  virtual void SetVSync(bool enabled) = 0;
  virtual bool IsVSync() const = 0;

  static Window* Create(const WindowProps& props = WindowProps());
};

}  // namespace Wood
