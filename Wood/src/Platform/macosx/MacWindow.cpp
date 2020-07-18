#include "pchwd.h"

#include "MacWindow.h"

#include "Wood/Core.h"
#include "Wood/Events/KeyEvent.h"
#include "Wood/Events/ApplicationEvent.h"
#include "Wood/Events/MouseEvent.h"

#include <glad/glad.h>

namespace Wood {

static bool s_GLFWInitialized = false;
static void GLFWErrorCallback(int error, const char* description) {
  WD_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

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

    glfwSetErrorCallback(GLFWErrorCallback);
    s_GLFWInitialized = true;
  }

  m_Window = glfwCreateWindow((int)props.Width, (int)props.Height,
                              m_Data.Title.c_str(), nullptr, nullptr);
  glfwMakeContextCurrent(m_Window);

  int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  WD_CORE_ASSERT(gladStatus, "Could not initialize glad!");
  glfwSetWindowUserPointer(m_Window, &m_Data);
  SetVSync(true);

  // Set callbacks
  glfwSetWindowSizeCallback(
      m_Window, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
      });

  glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
    WindowCloseEvent event;
    data.EventCallback(event);
  });

  glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode,
                                  int action, int mods) {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
    switch (action) {
      case GLFW_PRESS: {
        KeyPressedEvent pressEvent(key, false);
        data.EventCallback(pressEvent);
        break;
      }

      case GLFW_REPEAT: {
        KeyPressedEvent repeatEvent(key, true);
        data.EventCallback(repeatEvent);
        break;
      }

      case GLFW_RELEASE: {
        KeyReleasedEvent releaseEvent(key);
        data.EventCallback(releaseEvent);
        break;
      }
    }
  });

  glfwSetMouseButtonCallback(
      m_Window, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch (action) {
          case GLFW_PRESS: {
            MouseButtonPressedEvent pressEvent(button);
            data.EventCallback(pressEvent);
            break;
          }

          case GLFW_RELEASE: {
            MouseButtonReleasedEvent releaseEvent(button);
            data.EventCallback(releaseEvent);
            break;
          }
        }
      });

  glfwSetScrollCallback(
      m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
      });

  glfwSetCursorPosCallback(
      m_Window, [](GLFWwindow* window, double xPos, double yPos) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseMovedEvent event((float)xPos, (float)yPos);
        data.EventCallback(event);
      });
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