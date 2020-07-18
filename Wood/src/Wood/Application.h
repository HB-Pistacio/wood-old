#pragma once

#include "Wood/Window.h"
#include "Wood/LayerStack.h"
#include "Wood/Events/ApplicationEvent.h"

namespace Wood {

class Application {
 public:
  Application();
  virtual ~Application();

  void Run();

  void OnEvent(Event& e);

  void PushLayer(Layer* layer);
  void PushOverlay(Layer* overlay);

 private:
  bool OnWindowClose(WindowCloseEvent e);
  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
  LayerStack m_LayerStack;
};

Application* CreateApplication();

};  // namespace Wood
