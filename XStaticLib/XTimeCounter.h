#pragma once

#include <iostream>
#include <chrono>

namespace XSL
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

        void Start()
        {
            m_startTime = std::chrono::steady_clock::now();
        }

        void End()
        {
            m_endTime = std::chrono::steady_clock::now();
            m_duration = m_endTime - m_startTime;
        }

        float Duration()
        {
            return m_duration.count();
        }

        void CoutDuration()
        {
            std::cout << "Duration: " << Duration() << "s" << std::endl;
        }

        void CoutDuration(const char* str)
        {
            std::cout << str << " Duration: " << Duration() << "s" << std::endl;
        }

        ~XTimeCounter() = default;
    };
}