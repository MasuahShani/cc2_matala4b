#include "Ninja.hpp"
using namespace ariel;

Ninja::Ninja(Point point,int num_hit, string const& name, int speed):
Character(point,num_hit,name), speed(speed){}
Ninja::~Ninja () {}
Ninja::Ninja():speed(0){}
Ninja::Ninja (const Ninja& ninja):Character(ninja),speed(ninja.speed){}
Ninja& Ninja::operator=(const Ninja& ninja)
{
    if(!(this==&ninja))
    {
        speed=ninja.speed;
        Character::operator=(ninja);
    }
    return *this;
}
Ninja::Ninja (Ninja &&ninja) noexcept: Character(std::move(ninja)), speed(ninja.speed){}
Ninja & Ninja::operator=(Ninja&& ninja) noexcept
{
    speed=ninja.speed;
    Character::operator=(ninja);
    return *this;
}

void Ninja::move(Character* enemy)
{
    if(this->isAlive() && enemy!=this)
    {
        Point p=Point::moveTowards( (this->getLocation()),enemy->getLocation(),speed);
        this->setPoint(p);
    }
}
void Ninja::slash(Character* enemy)
{
    if(!isAlive()||!enemy->isAlive())
    {
        throw runtime_error("ded");
    }
    Ninja* n = dynamic_cast<Ninja*>(enemy);
    if(n && (this==n))
    {
        throw runtime_error("shoot myself");
    }
    if(this->getLocation().distance(enemy->getLocation())<1)
    {
        enemy->hit(40);
    }

}
string Ninja:: print()
{
    return Character::print()+", speed:"+to_string(speed);
}
void Ninja::setSpeed(int speed)
{
    if(speed>=0)
    {
        this->speed=speed;
    }
}
int Ninja:: getSpeed()
{
    return speed;
}
