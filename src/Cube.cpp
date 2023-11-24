#include "Cube.h"

//static def.
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

//Constructors
Cube::Cube()
    :Entity(),_pos(0.0f),_size(1.0f){}

Cube::Cube(vec3 position, float size)
    :Entity(),_pos(position),_size(size){}

