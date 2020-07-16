#include "Wood/Application.h"

#include "Wood/Events/Event.h"
#include "Wood/Events/ApplicationEvent.h"
#include "Wood/Log.h"

namespace Wood {
Application::Application() {}
Application::~Application() {}

void Application::Run() {
  WindowResizeEvent e(1200, 720);
  WD_TRACE(e);

  while (true)
    ;
}

}  // namespace Wood