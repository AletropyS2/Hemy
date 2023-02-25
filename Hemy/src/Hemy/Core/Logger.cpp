#include "hemypch.h"
#include "Logger.h"

#include <cstdarg>

#ifdef HEMY_LOG_ENABLED

namespace Hemy
{

	const char* levelColor[5] = { "\033[1;31m", "\033[1;31m", "\033[1;33m", "\033[1;32m", "\033[1;34m" };
	const char* levelStr[5] = { "FATAL", "ERROR", "WARN", "INFO", "TRACE" };

	void Log(LogLevel level, const char* message, ...)
	{
		std::stringstream ss;

		ss << levelColor[(int)level];

		ss << "[HEMY | " << levelStr[(int)level] << "]: ";

		char buffer[4096];

		va_list args;
		va_start(args, message);
		vsnprintf(buffer, sizeof buffer, message, args);
		va_end(args);

		ss << buffer;

		ss << "\033[0m";

		std::cout << ss.str() << std::endl;
	}
}

#endif