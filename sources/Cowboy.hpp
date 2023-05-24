#pragma once
#include "Point.hpp"
#include "Character.hpp"

using namespace std;
namespace ariel{
    class Cowboy: public Character
    {
    private:
        int num_balls;

    public:
       // Cowboy(string const& name, Point& point);
       Cowboy(string const& name, Point point); 
        ~Cowboy()override;
        Cowboy();
        Cowboy (const Cowboy& cow);
        Cowboy& operator=(const Cowboy& cow);
        Cowboy (Cowboy &&cow) noexcept ;
        Cowboy & operator=(Cowboy&& cow) noexcept;

        void shoot(Character* enemy);
        bool hasboolets() const;
        void reload();
        string print()override;
        


    };

 

}