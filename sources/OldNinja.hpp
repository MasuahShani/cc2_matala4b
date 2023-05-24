#pragma once
#include "Point.hpp"
#include "Character.hpp"
#include "Ninja.hpp"

namespace ariel{
    class OldNinja : public Ninja
    {
    private:
      
    public:
        static const int DEFAULT_SPEED = 8;
        static const int DEFAULT_NUM_HIT = 150;

        OldNinja(string const& name, Point point);
         ~OldNinja ()override;
        OldNinja();
        
        OldNinja (const OldNinja& ninja);
        OldNinja& operator=(const OldNinja& ninja);
        OldNinja (OldNinja &&ninja) noexcept;
        OldNinja & operator=(OldNinja&& ninga) noexcept;


    };

}