#include "pchwd.h"

#include "Wood/Application.h"
#include "Wood/Log.h"
#include "Wood/Events/Event.h"

#include <glad/glad.h>

namespace Wood {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

Application::Application() {
  m_Window = std::unique_ptr<Window>(Window::Create());
  m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

  unsigned int id;
  glGenVertexArrays(1, &id);
}

Application::~Application() {}

void Application::OnEvent(Event& e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(
      BIND_EVENT_FN(Application::OnWindowClose));

  for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
    (*--it)->OnEvent(e);
    if (e.Handled) {
      break;
    }
  }
}

void Application::Run() {
  while (m_Running) {
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for (Layer* layer : m_LayerStack) {
      layer->OnUpdate();
    }

    m_Window->OnUpdate();
  }
}

bool Application::OnWindowClose(WindowCloseEvent e) {
  m_Running = false;
  return true;
}

void Application::PushLayer(Layer* layer) {
  m_LayerStack.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverlay(Layer* overlay) {
  m_LayerStack.PushOverlay(overlay);
  overlay->OnAttach();
}

}  // namespace Wood