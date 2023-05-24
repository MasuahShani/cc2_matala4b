#pragma once
#include "Point.hpp"
#include "Character.hpp"

namespace ariel{
    class Ninja : public Character
    {
    private:
        
        int speed;

    public:
        Ninja(Point point,int num_hit, string const& name, int speed);
        ~Ninja ()override ;
        Ninja();
        Ninja (const Ninja& ninja);
        Ninja& operator=(const Ninja& ninja);
        Ninja (Ninja &&ninja) noexcept;
        Ninja & operator=(Ninja&& ninga) noexcept;

        void move(Character* enemy);
        void slash(Character* enemy);
        string print()override;
        void setSpeed(int speed);
        int getSpeed();



    };

}