#include "Cowboy.hpp"
using namespace ariel;

static const int DEFAULT_NUM_BALLS = 6;
static const int DEFAULT_NUM_HIT = 110;

        // Cowboy::Cowboy(string const& name, Point& point):
        // Character(point,DEFAULT_NUM_HIT,name) ,num_balls(DEFAULT_NUM_BALLS){}
        Cowboy::Cowboy(string const& name, Point point):
        Character(point,DEFAULT_NUM_HIT,name) ,num_balls(DEFAULT_NUM_BALLS){}
        Cowboy:: ~Cowboy(){}
        Cowboy::Cowboy():num_balls(DEFAULT_NUM_BALLS){}
        Cowboy::Cowboy (const Cowboy& cow):
        Character(cow), num_balls(cow.num_balls){}
        Cowboy &  Cowboy:: operator=(const Cowboy& cow)
        {
            if(this!=&cow)
            {
                Character::operator=(cow);
                num_balls=cow.num_balls;
            }
            return *this;
        }
         Cowboy::Cowboy (Cowboy &&cow) noexcept: Character(move(cow)), num_balls(cow.num_balls){}
        Cowboy &  Cowboy::operator=(Cowboy&& cow) noexcept
        {
            Character::operator=(cow);
            num_balls=cow.num_balls;
            return *this;
        }

        void  Cowboy::shoot(Character* enemy)
        {
            if(!isAlive()||!enemy->isAlive())
            {
                throw runtime_error("ded");
            }
            Cowboy* c_le = dynamic_cast<Cowboy*>(enemy);
            if(c_le && (this==c_le))
            {
                throw runtime_error("shoot myself");
            }
            if( hasboolets() && enemy!=this)
            {
                enemy->hit(10);
                num_balls--;
            }
        }
        bool  Cowboy::hasboolets() const
        {
            return num_balls!=0;
        }
        void  Cowboy::reload()
        {
            if(!isAlive())
            {
                throw runtime_error("ded cant reload");
            }
            num_balls=6;
        }
        string  Cowboy::print()
        {
            return Character::print()+", num balls:"+to_string(num_balls);
        }