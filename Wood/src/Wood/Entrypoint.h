#pragma once

#include "Wood.h"

extern Wood::Application* Wood::CreateApplication();

int main(int argc, char** argv) {
  auto app = Wood::CreateApplication();
  app->Run();
  delete app;
}