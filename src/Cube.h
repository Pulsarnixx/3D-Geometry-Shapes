#pragma once

#include "Entity.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

typedef glm::vec3 vec3;

class Cube: public Entity
{
   private:
     static float _vertices[];
     static unsigned int _indices[];  

   public:
    Cube():Entity(),_pos(0.0f){}
    ~Cube() override{}

    const void* GetVerticesArrayData() const {return _vertices;}
    const unsigned int GetVerticesArraySize() const {return 4 * 4 * 5 * sizeof(float);}
    const unsigned int* GetIndicatesArrayData() const {return _indices;}
    const unsigned int GetIndicatesArraySize() const {return 6 * 2 * 3 * sizeof(unsigned int);}

    const vec3 GetPosition();
    void SetPosition();

    private:
        vec3 _pos;

};

/*
Before: 6 * 6 * 5 vertices = 180 * sizeof(float) = 720
        0 indicies
        Summary -> 720

After: 
      4 * 4 * 5 vertices = 80 * szieof(float) = 320
      2 * 3 * 6 indiceis = 36 * sizeof(uint) = 144
      Summary -> 464


*/
float Cube::_vertices[]{

      //position            //texture
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,//0
       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,//1
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,//2
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,//3
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,//4
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,//5
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,//6
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,//7
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,//8
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,//9
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,//10
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,//11
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,//12
       0.5f, -0.5f,  0.5f,  0.0f, 0.0f,//13       
       0.5f, -0.5f, -0.5f,  1.0f, 1.0f,//14                              
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f//15

};

unsigned int Cube::_indices[]{
    
    0, 1, 2, //1 surface
    2, 3, 0,

    4, 5, 6, //2 ...
    6, 7, 4,

    8, 9, 10,
    10, 4, 8,

    11, 2, 12,
    12, 13, 11,

    10, 14, 5,
    5, 4, 10,

    3, 2, 11,
    11, 15, 3

};