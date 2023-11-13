#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
    private:
        unsigned int _RendererID;
    public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void UnBind() const;
    void AddBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout);
};