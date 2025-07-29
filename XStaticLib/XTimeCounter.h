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

        void Start()
        {
            m_startTime = std::chrono::steady_clock::now();
        }

        void End()
        {
            m_endTime = std::chrono::steady_clock::now();
            m_duration = m_endTime - m_startTime;
        }

        float Duration() const
        {
            return m_duration.count();
        }

        void CoutDuration() const
        {
            std::cout << "Duration: " << Duration() << "s\n";
        }

        void CoutDuration(const char* str) const
        {
            std::cout << str << " Duration: " << Duration() << "s\n";
        }
    };
}