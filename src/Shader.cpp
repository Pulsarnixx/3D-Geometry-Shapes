#include "Shader.h"

#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& filepath)
    :_FilePath(filepath),_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    _RendererID = GenProgram(source.VertexShader,source.FragmentShader);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(_RendererID));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream file(filepath);
    std::string line;

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0 ,FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;
    std::stringstream ss[2];

    while(std::getline(file,line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
        
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT; 
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
        
    }

    return {ss[0].str(),ss[1].str()};
}  

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);
   
    //Error handling
    int result;
    glGetShaderiv(id,GL_COMPILE_STATUS,&result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id,length,&length,message);

        std::cout << "Failed to compile shader! " << std::endl;
        std::cout << message << std::endl;
        
        glDeleteShader(id);
        return 0;
    }


    return id;
}

unsigned int Shader::GenProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram(); 

    unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}

void Shader::Bind() const
{
    glUseProgram(_RendererID);
}

void Shader::UnBind() const
{
    glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& name)
{
    if(_UniformsLocationCache.find(name) != _UniformsLocationCache.end())
        return _UniformsLocationCache[name];

    GLCall(int location = glGetUniformLocation(_RendererID,name.c_str())); 
    if(location == -1)
        std::cout << "Warning, uniform name: " << name << " doesn't exist!" << std::endl;
    if(location >= 0)   _UniformsLocationCache[name] = location;

    return location; 
}

 void Shader::SetUniform1i(const std::string& name, int v0)
 {
    GLCall(glUniform1i(GetUniformLocation(name),v0));
 }

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3 )
{
    GLCall(glUniform4f(GetUniformLocation(name),v0,v1,v2,v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& m1)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name),1,false,&m1[0][0]));
}
