#pragma once

#include "Team.hpp"

namespace ariel{
    class Team2 : public Team
    {
    private:
        
        int* wich;
        int index_leader;
       

       
    public:
        Team2(Character* leader);
        ~Team2()override;
        Team2();
        Team2 (const Team2& team);
        Team2 (Team2 &&team) noexcept;
        
        Team2& operator=(const Team2& team);
      
        Team2 & operator=(Team2&& team) noexcept;

        void add(Character* warrior)override;
        void attack(Team* other)override;
        int stillAlive()override;
        void print()override;
        

    };
    
    
    
}