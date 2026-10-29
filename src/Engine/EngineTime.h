#pragma once
#include<chrono>

namespace Nova{
    class EngineTime{
        public:
        using Clock = std::chrono::steady_clock;
        
        void Reset(){
            m_StartTime = Clock::now();
            m_LastFrameTime = m_StartTime;

            m_DeltaTime = 0.0f;
            m_ElapsedTime = 0.0f;
        }

        void Tick(){
            const auto currentTime = Clock::now();
            m_DeltaTime = std::chrono::duration<float>(currentTime - m_LastFrameTime).count();
            m_ElapsedTime = std::chrono::duration<float>(currentTime - m_StartTime).count();
            m_LastFrameTime = currentTime;
        }

        float GetDeltaTime() const{
            return m_DeltaTime;
        }

        float GetElapsedTime() const{
            return m_ElapsedTime;
        }

        private:
        Clock::time_point m_StartTime;
        Clock::time_point m_LastFrameTime;

        float m_DeltaTime = 0.0f;
        float m_ElapsedTime = 0.0f;
    };
}