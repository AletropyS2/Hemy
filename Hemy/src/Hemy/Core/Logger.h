#pragma once


#define HEMY_API __declspec(dllexport)

#ifndef HEMY_LOG_ENABLED
#define HEMY_LOG_ENABLED
#endif

namespace Hemy
{
	enum class HEMY_API LogLevel
	{
		Fatal,
		Error,
		Warn,
		Info,
		Trace
	};

	void HEMY_API Log(LogLevel level, const char* message, ...);
}

#define HFATAL(message, ...) Hemy::Log(Hemy::LogLevel::Fatal, message, ##__VA_ARGS__)
#define HERROR(message, ...) Hemy::Log(Hemy::LogLevel::Error, message, ##__VA_ARGS__)

#ifdef HEMY_DEBUG
#define HEMY_ASSERT_ENABLED
#define HWARN(message, ...) Hemy::Log(Hemy::LogLevel::Warn, message, ##__VA_ARGS__)
#define HINFO(message, ...) Hemy::Log(Hemy::LogLevel::Info, message, ##__VA_ARGS__)
#define HTRACE(message, ...) Hemy::Log(Hemy::LogLevel::Trace, message, ##__VA_ARGS__)
#else
#define HWARN(message, ...)
#define HINFO(message, ...)
#define HTRACE(message, ...)
#endif

#ifdef HEMY_ASSERT_ENABLED
#define LOG_FAILURE(message) Hemy::Log(Hemy::LogLevel::Fatal, "%s. File: %s | Line: %d", message, __FILE__, __LINE__)
#define HASSERT(expr, message) if(expr){} else { LOG_FAILURE(message); __debugbreak(); }
#else
#define HASSERT(expr, message)
#endif