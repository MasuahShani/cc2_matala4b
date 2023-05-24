#pragma once

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>



#include "Point.hpp"

using namespace std;

namespace ariel{
    class Character
    {
    private:
        Point point;
        int num_hit;
        string name;
        bool in_team;

    public:
        Character(Point& point,int num_hit, string const& name);
        virtual~Character();

        Character();
        Character (const Character& chara);
        Character& operator=(const Character& chara);
        
        Character(Character&& chara) noexcept;
        Character & operator=(Character&& chara) noexcept;
        
        bool isAlive ()const;
        double distance(const Character* other);
        void hit(int num);
        string getName();
        Point getLocation();
        virtual string print();
        bool operator==(const Character& chara) const;
        
        void setIn_team(bool bol);
        bool getIn_team() const;
        void setPoint(Point);




    };

}