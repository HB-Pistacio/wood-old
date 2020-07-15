#include <Wood.h>

class Sandbox : public Wood::Application {
 public:
  Sandbox() {}
  ~Sandbox() {}
};

Wood::Application* Wood::CreateApplication() {
  return new Sandbox();
}