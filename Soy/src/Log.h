#pragma once
#include "spdlog/spdlog.h"
#include <memory>

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;};
	inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; };

private:
	static std::shared_ptr<spdlog::logger> s_CoreLogger;
	static std::shared_ptr<spdlog::logger> s_ClientLogger;

};

// Core log macros
#define CORE_TRACE(...)    Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)     Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)     Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)    Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define TRACE(...)         Log::GetClientLogger()->trace(__VA_ARGS__)
#define INFO(...)          Log::GetClientLogger()->info(__VA_ARGS__)
#define WARN(...)          Log::GetClientLogger()->warn(__VA_ARGS__)
#define ERROR(...)         Log::GetClientLogger()->error(__VA_ARGS__)
#define CRITICAL(...)      Log::GetClientLogger()->critical(__VA_ARGS__)