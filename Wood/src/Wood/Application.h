#pragma once

namespace Wood {

class Application {
 public:
  Application();
  virtual ~Application();

  void Run();
};

Application* CreateApplication();

};  // namespace Wood
