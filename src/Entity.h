#pragma once

#include <vector>
#include <iostream>

typename std::vector<float> vector;

class Entity
{
    private:
        static unsigned int _entitiesNumber; //static variable dec.
        const unsigned int _ID;


    public:
        Entity():_ID(_entitiesNumber++){};
        virtual ~Entity(){_entitiesNumber--;}

        unsigned int HowMany() const {return _entitiesNumber;}
        unsigned int GetId() const {return _ID;}


};

//static variable def.
unsigned int Entity::_entitiesNumber = 0;