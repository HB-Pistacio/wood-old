#include <Wood.h>

class ExampleLayer : public Wood::Layer {
 public:
  ExampleLayer() : Layer("Example") {}
  void OnUpdate() override { WD_INFO("ExampleLayer::Update"); }
  void OnEvent(Wood::Event& event) override { WD_TRACE(event); }
};

class Sandbox : public Wood::Application {
 public:
  Sandbox() { PushLayer(new ExampleLayer()); }
  ~Sandbox() {}
};

Wood::Application* Wood::CreateApplication() {
  return new Sandbox();
}