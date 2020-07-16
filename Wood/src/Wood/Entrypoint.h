#pragma once

#include "Wood.h"

extern Wood::Application* Wood::CreateApplication();

int main(int argc, char** argv) {
  Wood::Log::Init();

  WD_CORE_WARN("Welcome to Wood enginge!");
  int a = 5;
  WD_INFO("App started a={0}", a);

  auto app = Wood::CreateApplication();
  app->Run();
  delete app;
}