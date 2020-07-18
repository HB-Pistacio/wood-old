#pragma once

#include "Wood/Window.h"
#include "Wood/Events/ApplicationEvent.h"

namespace Wood {

class Application {
 public:
  Application();
  virtual ~Application();

  void Run();

  void OnEvent(Event& e);

 private:
  bool OnWindowClose(WindowCloseEvent e);
  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
};

Application* CreateApplication();

};  // namespace Wood
