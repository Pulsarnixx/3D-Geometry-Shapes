#include "Texture.h"

#include "stb_image/stb_image.h"

Texture::Texture(const std::string& filepath)
    :_RendererID(0),_FilePath(filepath), _LocalBufferForImageData(nullptr), 
    _Width(0),_Height(0),_BPP(0)
{
    //Optional - depands on image format
    stbi_set_flip_vertically_on_load(1);
    _LocalBufferForImageData = stbi_load(filepath.c_str(),&_Width,&_Height,&_BPP,4);

    GLCall(glGenTextures(1,&_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D,_RendererID));

    //Texture Filtering
    GLCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST));
    //Texture Wrapping
    GLCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE));  //x
    GLCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE));  //y
  
    //Copy data to GL texture object
    GLCall(glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,_Width,_Height,0,GL_RGBA,GL_UNSIGNED_BYTE,_LocalBufferForImageData));

    GLCall(glBindTexture(GL_TEXTURE_2D,0));

    //Optional
    if(_LocalBufferForImageData)
        stbi_image_free(_LocalBufferForImageData);

}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1,&_RendererID));
}

void Texture::Bind(unsigned int slot) const{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D,_RendererID));
}

void Texture::UnBind() const{
    GLCall(glBindTexture(GL_TEXTURE_2D,0)); 
}

