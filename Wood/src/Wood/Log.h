#pragma once

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace Wood {

class Log {
 public:
  static void Init();

  inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
    return s_CoreLogger;
  }

  inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {
    return s_ClientLogger;
  }

 private:
  static std::shared_ptr<spdlog::logger> s_CoreLogger;
  static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

}  // namespace Wood

// CORE LOG MACROS
#define WD_CORE_FATAL(...) ::Wood::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define WD_CORE_ERROR(...) ::Wood::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WD_CORE_WARN(...) ::Wood::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WD_CORE_INFO(...) ::Wood::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WD_CORE_TRACE(...) ::Wood::Log::GetCoreLogger()->trace(__VA_ARGS__)

// CLIENT LOG MACROS
#define WD_FATAL(...) ::Wood::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define WD_ERROR(...) ::Wood::Log::GetClientLogger()->error(__VA_ARGS__)
#define WD_WARN(...) ::Wood::Log::GetClientLogger()->warn(__VA_ARGS__)
#define WD_INFO(...) ::Wood::Log::GetClientLogger()->info(__VA_ARGS__)
#define WD_TRACE(...) ::Wood::Log::GetClientLogger()->trace(__VA_ARGS__)