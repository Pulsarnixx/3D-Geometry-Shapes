#pragma once

#include "Entity.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define CUBE_VERTICES_SIZE 80
#define CUBE_INDICES_SIZE 36

typedef glm::vec3 vec3;

//TODO: Add mvp matrix?

class Cube: public Entity
{
   private:
      static float _vertices[CUBE_VERTICES_SIZE];
      static unsigned int _indices[CUBE_INDICES_SIZE];

   public:
    Cube();
    Cube(vec3 position, float size);
    ~Cube() override{}

    const void* GetVerticesArrayData() const {return _vertices;}
    const unsigned int GetVerticesArraySize() const {return 4 * 4 * 5 * sizeof(float);}
    const unsigned int* GetIndicatesArrayData() const {return _indices;}
    const unsigned int GetIndicatesArraySize() const {return 6 * 2 * 3 * sizeof(unsigned int);}

    const vec3 GetPosition() const {return _pos;}
    void SetPosition(float x, float y, float z){_pos = vec3(x,y,z);}
    
    const float GetSize() const {return _size;}
    void SetSize(float size){_size = size;}

    private:
        vec3 _pos;
        float _size;
};
