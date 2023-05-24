#pragma once
#include "Point.hpp"
#include "Character.hpp"
#include "Ninja.hpp"

namespace ariel{
    class TrainedNinja : public Ninja
    {
    private:

    public:
        static const int DEFAULT_SPEED = 12;
        static const int DEFAULT_NUM_HIT = 120;

        TrainedNinja(string const& name, Point point);
        ~TrainedNinja ()override;
        TrainedNinja();
        
        TrainedNinja (const TrainedNinja& ninja);
        TrainedNinja& operator=(const TrainedNinja& ninja);
        TrainedNinja (TrainedNinja &&ninja) noexcept;
        TrainedNinja & operator=(TrainedNinja&& ninga) noexcept;


    };

}