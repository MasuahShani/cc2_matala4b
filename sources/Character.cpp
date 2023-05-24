#include "Character.hpp"
using namespace ariel;
    
Character::Character(Point& point,int num_hit, string const& name):
point(point),num_hit(num_hit), name(name),in_team(false)
{ 
    
    if(num_hit<0)
    {
        throw invalid_argument("negative num hit");

    } 
   
}
Character:: ~Character(){}
 
Character::Character():num_hit(0),in_team(false)
{
    name="name";
    Point point1;
    point=point1;
}
Character::Character (const Character& chara):
point(chara.point),num_hit(chara.num_hit),
name(chara.name),in_team(chara.in_team)
{
    
 }
Character& Character::operator=(const Character& chara)
{
    if(!(this==&chara))
    {
          name=chara.name;
        num_hit=chara.num_hit;
        point=chara.point;
        in_team=chara.in_team;
    }

    return *this;
}

Character::Character(Character&& chara) noexcept
: point(move(chara.point)), num_hit(chara.num_hit),in_team(chara.in_team),name(move(chara.name))
{
   
    
}
Character & Character::operator=(Character&& chara) noexcept
{
    name=chara.name;
    num_hit=chara.num_hit;
    point=chara.point;
    in_team=chara.in_team;

    
    return *this;
    
}

bool Character:: isAlive ()const 
{
    return num_hit!=0;
}
double Character::distance(const Character* other)
{
    return point.distance(other->point);
}
void Character::hit(int num)
{
    if(num<0)
    {
        throw invalid_argument("neg hit");
    }
    num_hit-=num;
    if(num_hit<0)
    {
        num_hit=0;
    }
}
string Character::getName(){return name;}
Point Character::getLocation(){return point;}
string Character::print()
{
    string ret="name:"+string(name)+", point:"+point.print()+", num hit:"+ to_string(num_hit);
    return ret;
}
bool Character::operator==(const Character& chara) const
{
    if(point.getX()==chara.point.getX() && point.getY()==chara.point.getY())
    {
        return (name==chara.name)&&(num_hit==chara.num_hit);
    }
    return false;
}

void Character::setIn_team(bool bol)
{
    in_team=bol;
}
bool Character::getIn_team() const
{
    return in_team;
}
void Character::setPoint(Point p)
{
    point=p;
}
