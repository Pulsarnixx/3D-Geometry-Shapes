#pragma once

#include "Renderer.h"

class Texture
{
    private:
        unsigned int _RendererID;
        std::string _FilePath;
        unsigned char* _LocalBufferForImageData;
        int _Width, _Height, _BPP; //Bytes per pixel
    public:
        Texture(const std::string& filepath);
        ~Texture();

        void Bind(unsigned int slot = 0) const;
        void UnBind() const;

        inline int GetWidth() const { return _Width; }
        inline int GetHeight() const { return _Height; }

};