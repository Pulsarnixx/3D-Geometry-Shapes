#pragma once

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

