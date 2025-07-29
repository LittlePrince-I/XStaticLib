#pragma once

#include <iostream>

namespace xsl
{
	enum class LogLevel :
	std::uint8_t
	{
		LOG_NONE,
		LOG_INFO,		
		LOG_WARN,
		LOG_ERROR,
		LOG_FATAL
	};

	
	class XLog
	{
	
	public:
		template <typename T>
		static void Log(T& value)
		{
			std::cout << value << std::endl;
		}

		template <typename T>
		static void Log(const T value, LogLevel level)
		{
			if (level == LogLevel::LOG_INFO)
			{
                std::cout << "[INFO] " << value << std::endl;
			}

			else if (level == LogLevel::LOG_WARN)
			{
				std::cout << "[WARN] " << value << std::endl;
			}

			else if (level == LogLevel::LOG_ERROR)
			{
				std::cout << "[ERROR] " << value << std::endl;
			}
		}

		template <typename T>
		static void Log(const char* message, T value, LogLevel level)
		{
			if (level == LogLevel::LOG_INFO)
			{
				std::cout << "[INFO] " << message << value << std::endl;
			}

			else if (level == LogLevel::LOG_WARN)
			{
				std::cout << "[WARN] "<< message << value << std::endl;
			}

			else if (level == LogLevel::LOG_ERROR)
			{
				std::cout << "[ERROR] " << message << value << std::endl;
			}
		}
	};
}
