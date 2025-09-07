#pragma once

#include <iostream>
#include <chrono>

namespace xsl
{
    class XTimeCounter
    {
    private:
        std::chrono::time_point<std::chrono::steady_clock> m_startTime;
        std::chrono::time_point<std::chrono::steady_clock> m_endTime;
        std::chrono::duration<float> m_duration;

    public:
        XTimeCounter() :
            m_startTime(std::chrono::steady_clock::now()),
            m_endTime(std::chrono::steady_clock::now()),
            m_duration(0.0f)
        {
        }

        XTimeCounter(const XTimeCounter& other) = default;
        XTimeCounter(XTimeCounter&& other) noexcept = default;
        XTimeCounter& operator=(const XTimeCounter& other) = default;
        XTimeCounter& operator=(XTimeCounter&& other) noexcept = default;
        ~XTimeCounter() = default;

        void start()
        {
            m_startTime = std::chrono::steady_clock::now();
        }

        void end()
        {
            m_endTime = std::chrono::steady_clock::now();
            m_duration = m_endTime - m_startTime;
        }

        float duration() const
        {
            return m_duration.count();
        }

        void coutDuration() const
        {
            XLog::Log(duration(), LogLevel::LOG_INFO);
        }

        void coutDuration(const char* message) const
        {
            XLog::Log(message, duration(), LogLevel::LOG_INFO);
        }
    };
}