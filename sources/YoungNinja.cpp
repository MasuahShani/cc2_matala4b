#include "YoungNinja.hpp"
using namespace ariel;

static const int DEFAULT_SPEED = 14;
static const int DEFAULT_NUM_HIT = 100;

YoungNinja:: YoungNinja(string const& name, Point point):
Ninja(std::move(point),DEFAULT_NUM_HIT,name, DEFAULT_SPEED){}
YoungNinja:: ~YoungNinja () {}
YoungNinja::YoungNinja()
{
    setSpeed(DEFAULT_SPEED);
}

YoungNinja::YoungNinja (const YoungNinja& ninja):Ninja(ninja)
{
    
}
YoungNinja& YoungNinja::operator=(const YoungNinja& ninja)
{
    Ninja::operator=(ninja);
    return *this;
}
YoungNinja::YoungNinja(YoungNinja &&ninja) noexcept: Ninja(std::move(ninja))
{
}
YoungNinja & YoungNinja::operator=(YoungNinja&& ninja) noexcept
{
    Ninja::operator=(ninja);
    return *this;
}