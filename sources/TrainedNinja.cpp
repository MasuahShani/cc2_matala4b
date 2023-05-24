#include "TrainedNinja.hpp"
using namespace ariel;

static const int DEFAULT_SPEED = 12;
static const int DEFAULT_NUM_HIT = 120;

TrainedNinja:: TrainedNinja(string const& name, Point point):
Ninja(std::move(point),DEFAULT_NUM_HIT,name, DEFAULT_SPEED){}
TrainedNinja:: ~TrainedNinja () {}
TrainedNinja::TrainedNinja()
{
    setSpeed(DEFAULT_SPEED);
}

TrainedNinja::TrainedNinja (const TrainedNinja& ninja):Ninja(ninja)
{
    
}
TrainedNinja& TrainedNinja::operator=(const TrainedNinja& ninja)
{
    Ninja::operator=(ninja);
    return *this;
}
TrainedNinja::TrainedNinja(TrainedNinja &&ninja) noexcept: Ninja(std::move(ninja))
{
}
TrainedNinja & TrainedNinja::operator=(TrainedNinja&& ninja) noexcept
{
    Ninja::operator=(ninja);
    return *this;
}