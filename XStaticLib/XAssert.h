#pragma once

#include <cassert>

#include "XLog.h"

namespace xsl
{
	inline void Assert(bool condition, const char* message)
	{
		if (!condition)
			XLog::Log(message, LogLevel::LOG_ERROR);
		assert(condition);
	}
}