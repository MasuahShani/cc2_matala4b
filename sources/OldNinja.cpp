#include "OldNinja.hpp"
using namespace ariel;

static const int DEFAULT_SPEED = 8;
static const int DEFAULT_NUM_HIT = 150;

OldNinja:: OldNinja(string const& name, Point point):
Ninja(std::move(point),DEFAULT_NUM_HIT,name, DEFAULT_SPEED){}
OldNinja:: ~OldNinja () {}
OldNinja::OldNinja()
{
    setSpeed(DEFAULT_SPEED);
}

OldNinja::OldNinja (const OldNinja& ninja):Ninja(ninja)
{
    
}
OldNinja& OldNinja::operator=(const OldNinja& ninja)
{
    Ninja::operator=(ninja);
    return *this;
}
OldNinja::OldNinja(OldNinja &&ninja) noexcept: Ninja(std::move(ninja))
{
}
OldNinja & OldNinja::operator=(OldNinja&& ninja) noexcept
{
    Ninja::operator=(ninja);
    return *this;
}