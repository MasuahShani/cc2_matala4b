#pragma once
#include "Point.hpp"
#include "Character.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"
#include "YoungNinja.hpp"
#include <typeinfo>


namespace ariel{
    class Team
    {
    private:
        
        Cowboy** c_warriors;
        Ninja** n_warriors;
        int amount_cowboy;
        int amount_ninja;
        int leader;

       
    public:

        Team(Character* leader);
        virtual ~Team();
        Team();
        Team (const Team& team);
        Team& operator=(const Team& team);

        Team (Team &&team) noexcept;
            

        Team & operator=(Team&& team) noexcept;

        virtual void add(Character* warrior);
        virtual void attack(Team* other);
        virtual int stillAlive();
        virtual void print();
        void setLeader(int leader);
        int choose_vic(Team* other);
        int get_amount_cowboy()const;
        int get_amount_ninja()const;
        void set_amount_ninja(int amo);
        void set_amount_cowboy(int amo);
        Cowboy** get_c_warriors();
        Ninja** get_n_warriors();
        int get_leader();

    };///////////////////לבדוק את כל האורטואל
    
    
    
}
