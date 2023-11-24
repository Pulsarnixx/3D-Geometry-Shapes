#pragma once

#include <glad.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define DEBUG

#ifdef DEBUG
    #define ASSERT(x) if(!(x)) __builtin_trap()
    #define GLCall(x) GLClearError();\
        x;\
        ASSERT(GLLogError(#x,__FILE__,__LINE__));

#else
    #define GLCall(x) x;
#endif

void GLClearError();

bool GLLogError(const char* function, const char* file, unsigned int line);

class Renderer
{
    private:

    public:
        void UpdateClearColor(float r, float g, float b, float a) const;
        void Clear() const;
        void Draw(const VertexArray& vao, const IndexBuffer& ebo, const Shader& shader) const;
};
