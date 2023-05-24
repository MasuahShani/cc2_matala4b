#pragma once

#include "Team.hpp"

namespace ariel{
    class SmartTeam : public Team
    {
    private:
            
        int* wich;
        int index_leader;

       
    public:
        SmartTeam(Character* leader);
        ~SmartTeam()override;
        SmartTeam();
        SmartTeam (const SmartTeam& team);
        SmartTeam (SmartTeam &&team) noexcept;
        
        SmartTeam& operator=(const SmartTeam& team);
      
        SmartTeam & operator=(SmartTeam&& team) noexcept;

        void add(Character* warrior)override;
        void attack(Team* other)override;
        int stillAlive()override;
        void print()override;
        int choose_vic2(Team*, int);
        

    };
    
    
    
}