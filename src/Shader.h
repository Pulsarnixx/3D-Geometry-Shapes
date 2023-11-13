#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"


struct ShaderProgramSource
{
    std::string VertexShader;
    std::string FragmentShader;
};

class Shader
{
    private:
       
        std::string _FilePath; //Debugging purpose
        unsigned int _RendererID; 
        std::unordered_map<std::string, int> _UniformsLocationCache;

    public:
        Shader(const std::string& filepath);
        ~Shader();

        void Bind() const;
        void UnBind() const;

        //Set uniforms - simple for tutorial
        void SetUniform1i(const std::string& name, int v0);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3 );
        void SetUniformMat4f(const std::string& name, const glm::mat4& m1);
    private:
        ShaderProgramSource ParseShader(const std::string& filepath);
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int GenProgram(const std::string& vertexShader, const std::string& fragmentShader);

        int GetUniformLocation(const std::string& name);

};