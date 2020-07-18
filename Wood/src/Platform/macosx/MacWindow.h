#pragma once

#include <GLFW/glfw3.h>
#include "Wood/Window.h"

namespace Wood {

class MacWindow : public Window {
 public:
  MacWindow(const WindowProps& props);
  virtual ~MacWindow();
  void OnUpdate() override;

  inline unsigned int GetWidth() const override { return m_Data.Width; }
  inline unsigned int GetHeight() const override { return m_Data.Height; }

  inline void SetEventCallback(const EventCallBackFn& callback) override {
    m_Data.EventCallback = callback;
  }
  void SetVSync(bool enabled) override;
  bool IsVSync() const override;

 private:
  virtual void Init(const WindowProps& props);
  virtual void ShutDown();

  GLFWwindow* m_Window;

  struct WindowData {
    std::string Title;
    unsigned int Width, Height;
    bool VSync;

    EventCallBackFn EventCallback;
  };

  WindowData m_Data;
};

}  // namespace Wood