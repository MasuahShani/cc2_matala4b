#pragma once
#include "Point.hpp"
#include "Character.hpp"
#include "Ninja.hpp"

namespace ariel{
    class YoungNinja : public Ninja
    {
    private:
      
    public:
        static const int DEFAULT_SPEED = 14;
        static const int DEFAULT_NUM_HIT = 100;

        YoungNinja(string const& name, Point point);
       ~YoungNinja ()override;
        YoungNinja();
        
        YoungNinja (const YoungNinja& ninja);
        YoungNinja& operator=(const YoungNinja& ninja);
        YoungNinja (YoungNinja &&ninja) noexcept;
        YoungNinja & operator=(YoungNinja&& ninga) noexcept;
    };

}