#include "Renderer.h"
#include <iostream>

class VertexArray;

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogError(const char* function, const char* file, unsigned int line)
{
    while(GLenum error = glGetError())
    {
        std::cout << "[OpenGL] ("<< error << ") "<< function <<" "<< file <<":"<< line << std::endl;

        return false;
    }

    return true;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ebo, const Shader& shader) const
{
    
    shader.Bind(); 
    vao.Bind();
    ebo.Bind();

    //GLCall(glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL));
    GLCall(glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0));

}