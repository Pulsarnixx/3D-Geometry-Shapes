#pragma once

#include <vector>
#include "Renderer.h" 

struct VertexBufferElements
{
    unsigned int type;
    unsigned int count;
    int normalized; 

    static unsigned int GetTypeSize(unsigned int type)
    {
        switch(type)
        {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }

        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout
{
    private:
        std::vector<VertexBufferElements> _Elements;
        unsigned int _Stride;
    public:
        VertexBufferLayout()
            :_Stride(0){};

        template<typename T>
        void Push(unsigned int count);
        
        inline const std::vector<VertexBufferElements>& GetElements() const { return _Elements; }
        inline unsigned int GetStride() const { return _Stride; }


};
template<>
inline void VertexBufferLayout::Push<float>(unsigned int count)
{   
            _Elements.push_back({GL_FLOAT,count,GL_FALSE});
            _Stride += count * VertexBufferElements::GetTypeSize(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{   
            _Elements.push_back({GL_UNSIGNED_INT,count,GL_FALSE});
            _Stride += count * VertexBufferElements::GetTypeSize(GL_UNSIGNED_INT);
}

template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{   
            _Elements.push_back({GL_UNSIGNED_BYTE,count,GL_TRUE});
            _Stride += count * VertexBufferElements::GetTypeSize(GL_UNSIGNED_BYTE);
}