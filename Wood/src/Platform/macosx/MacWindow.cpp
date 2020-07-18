#include "pchwd.h"
#include "Wood/Core.h"
#include "MacWindow.h"

namespace Wood {

static bool s_GLFWInitialized = false;

Window* Window::Create(const WindowProps& props) {
  return new MacWindow(props);
}

MacWindow::MacWindow(const WindowProps& props) {
  Init(props);
}

MacWindow::~MacWindow() {
  ShutDown();
}

void MacWindow::Init(const WindowProps& props) {
  m_Data.Title = props.Title;
  m_Data.Width = props.Width;
  m_Data.Height = props.Height;

  WD_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width,
               props.Height);
  if (!s_GLFWInitialized) {
    int success = glfwInit();
    WD_CORE_ASSERT(success, "Could not initialize GLFW!");

    s_GLFWInitialized = true;
  }

  m_Window = glfwCreateWindow((int)props.Width, (int)props.Height,
                              m_Data.Title.c_str(), nullptr, nullptr);
  glfwMakeContextCurrent(m_Window);
  glfwSetWindowUserPointer(m_Window, &m_Data);
  SetVSync(true);
}

void MacWindow::ShutDown() {
  glfwDestroyWindow(m_Window);
}

void MacWindow::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(m_Window);
}

void MacWindow::SetVSync(bool enabled) {
  if (enabled) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }

  m_Data.VSync = enabled;
}

bool MacWindow::IsVSync() const {
  return m_Data.VSync;
}

}  // namespace Wood