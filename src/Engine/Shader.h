#pragma once

namespace Nova
{
    class Shader
    {
    public:
        Shader(const char* vertexSource, const char* fragmentSource);
        ~Shader();

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        void Bind() const;
        void UnBind() const;

        unsigned int GetRendererID() const;
        
    private:
        unsigned int m_RendererID = 0;
    };
}