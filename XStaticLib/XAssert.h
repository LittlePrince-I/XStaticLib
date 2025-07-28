#pragma once

#include <cassert>

#include "XLog.h"

namespace XSL
{
	void Assert(bool condition, const char* message)
	{
		if (!condition)
			XLog::Log(message, LogLevel::LOG_ERROR);
		assert(condition);
	}
}