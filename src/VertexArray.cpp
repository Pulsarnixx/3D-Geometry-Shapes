#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "Renderer.h"

#include <iostream>

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1,&_RendererID));
}
VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1,&_RendererID));
}


void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(_RendererID));
}
void VertexArray::UnBind() const
{
    GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout)
{
    //Bind VAO
    Bind();
    //Bind VBO
    buffer.Bind();
    //Bind all Vertex Attributes coresponding to current VBO
    int offset = 0;
    const auto elements = layout.GetElements();
    for(unsigned int i = 0 ; i < elements.size(); i++)
    {
        const auto element = elements[i];
        GLCall(glVertexAttribPointer(i, element.count, element.type, 
            element.normalized, layout.GetStride(), (const void*)offset));
        GLCall(glEnableVertexAttribArray(i));
        
       offset += element.count * VertexBufferElements::GetTypeSize(element.type); 
    }



}


