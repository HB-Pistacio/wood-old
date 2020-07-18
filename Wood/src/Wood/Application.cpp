#include "pchwd.h"
#include "Wood/Application.h"
#include "Wood/Log.h"
#include "Wood/Events/Event.h"
#include "Wood/Events/ApplicationEvent.h"

namespace Wood {
Application::Application() {
  m_Window = std::unique_ptr<Window>(Window::Create());
}

Application::~Application() {}

void Application::Run() {
  while (m_Running) {
    m_Window->OnUpdate();
  }
}

}  // namespace Wood