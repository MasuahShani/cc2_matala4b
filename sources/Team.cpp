#include "Team.hpp"
using namespace ariel;

static const int SIZE = 10;
Team::Team(Character* leader):c_warriors(new Cowboy*[SIZE]),
n_warriors(new Ninja*[SIZE]),amount_cowboy(0),
amount_ninja(0),leader(0)
{
    if(n_warriors==nullptr || c_warriors==nullptr)
    {
        throw runtime_error("null ptr");
    }
    if(Cowboy* c_le = dynamic_cast<Cowboy*>(leader))
    {
        if(c_le->getIn_team())
        {
            throw std::runtime_error("is already in team");
        }
        this->leader=1;
        c_warriors[amount_cowboy++]=c_le;
        c_le->setIn_team(true);


    }
    else if (Ninja* n_le = dynamic_cast<Ninja*>(leader))
    {
        if(n_le->getIn_team())
        {
            throw std::runtime_error("is already in team");
        }
        this->leader=2;
        n_warriors[amount_ninja++]=n_le;
        n_le->setIn_team(true);


    }
    else
    {
        throw std::invalid_argument("invalid_argument");
    }
    
}
Team::~Team()
{
    for(int i=0; i<amount_cowboy;i++)
    {
        delete c_warriors[i];
    }
    delete[] c_warriors;
    for(int i=0; i<amount_ninja;i++)
    {
        delete n_warriors[i];
    }
    delete[] n_warriors;

}
Team::Team():c_warriors(new Cowboy*[SIZE]),
n_warriors(new Ninja*[SIZE]),amount_cowboy(0),
amount_ninja(0),leader(0)
{
    if(n_warriors==nullptr || c_warriors==nullptr)
    {
        throw runtime_error("null ptr");
    }
}
Team::Team (const Team& team):c_warriors(new Cowboy*[SIZE]),
n_warriors(new Ninja*[SIZE]),amount_cowboy(team.amount_cowboy),
amount_ninja(team.amount_ninja),leader(team.leader)
{
    if(n_warriors==nullptr || c_warriors==nullptr)
    {
        throw runtime_error("null ptr");
    }
    for (int i = 0; i < amount_cowboy; i++)
    {
        *c_warriors[i]=*team.c_warriors[i];
    }
    for (int i = 0; i < amount_ninja; i++)
    {
        *n_warriors[i]=*team.n_warriors[i];
    }
    
    
}
Team& Team::operator=(const Team& team)
{
    if(!(this==&team))
    {
        for(int i=0; i<amount_cowboy;i++)
        {
            delete c_warriors[i];
        }
        delete[] c_warriors;
        for(int i=0; i<amount_ninja;i++)
        {
            delete n_warriors[i];
        }
        delete[] n_warriors;

        c_warriors=new Cowboy*[SIZE];
        n_warriors=new Ninja*[SIZE];
        if(n_warriors==nullptr || c_warriors==nullptr)
        {
            throw runtime_error("null ptr");
        }
        amount_cowboy=team.amount_cowboy;
        amount_ninja=team.amount_ninja;
        leader=team.leader;
        for (int i = 0; i < amount_cowboy; i++)
        {
            *c_warriors[i]=*team.c_warriors[i];
        }
        for (int i = 0; i < amount_ninja; i++)
        {
            *n_warriors[i]=*team.n_warriors[i];
        }

    }
    return *this;
}

Team::Team (Team &&team) noexcept: c_warriors(nullptr),n_warriors(nullptr), amount_cowboy(0),amount_ninja(0),leader(0) {
    try {
        c_warriors = new Cowboy*[SIZE];
        n_warriors = new Ninja*[SIZE];
    } catch (const std::bad_alloc&) {
        std::cerr << "Error: memory allocation failed." << std::endl;
        exit(1);
    }

}
    

Team & Team::operator=(Team&& team) noexcept
{
     try {
        c_warriors = new Cowboy*[SIZE];
        n_warriors = new Ninja*[SIZE];
    } catch (const std::bad_alloc&) {
        std::cerr << "Error: memory allocation failed." << std::endl;
        exit(1);
    }
    amount_cowboy=team.amount_cowboy;
    amount_ninja=team.amount_ninja;
    leader=team.leader;
    for (int i = 0; i < amount_cowboy; i++)
    {
        *c_warriors[i]=*team.c_warriors[i];
    }
    for (int i = 0; i < amount_ninja; i++)
    {
        *n_warriors[i]=*team.n_warriors[i];
    }
    return *this;
}

void Team::add(Character* warrior)
{
    if(amount_cowboy+amount_ninja==10)
    {
        throw std::runtime_error("full team");
    }
    if(Cowboy* c_w = dynamic_cast<Cowboy*>(warrior))
    {
        if(c_w->getIn_team())
        {
            throw std::runtime_error("already in a team");
        }
        
        c_warriors[amount_cowboy++]=c_w;
        c_w->setIn_team(true);


    }
    else if (Ninja* n_w = dynamic_cast<Ninja*>(warrior))
    {
        if(n_w->getIn_team())
        {
            throw std::runtime_error("already in a team");
        }
        n_warriors[amount_ninja++]=n_w;
        n_w->setIn_team(true);

    }
    else
    {
        throw std::runtime_error("invalid_argument");
    }

}
int Team::stillAlive()
{

    if(amount_cowboy==0&&amount_ninja==0)
    {
        return 0;
    }
    double dis;
    if(leader==1 && !c_warriors[0]->isAlive() )
    {
        //the leader is ded, need to replace
        if(amount_cowboy>1 || amount_ninja>0)
        {
            double min=std::numeric_limits<double>::infinity();
            int index=0;
            for (int i = 1; i < amount_cowboy; i++)
            {
                dis=c_warriors[0]->getLocation().distance(c_warriors[i]->getLocation());
                if(min>dis)
                {
                    if(c_warriors[i]->isAlive())
                    {
                        index=i;
                        leader=1;
                        min=dis;
                    }
                }
            }
            for (int i = 0; i < amount_ninja; i++)
            {
                dis=c_warriors[0]->getLocation().distance(n_warriors[i]->getLocation());
                if(min>dis)
                {
                    if(n_warriors[i]->isAlive())
                    {
                        index=i;
                        leader=2;
                        min=dis;
                    }
                }
            }

            if(leader==1)
            {
                
                c_warriors[0]=c_warriors[index];
                for (int i = index; i < amount_cowboy-1; i++)
                {
                    c_warriors[i]=c_warriors[i+1];
                }
                amount_cowboy--;
                
            }
            else if (leader==2)
            {   
                Ninja* temp=n_warriors[0];
                n_warriors[0]=n_warriors[index];
                n_warriors[index]=temp;
                
            }
            else
            {
                amount_cowboy=0;
                amount_ninja=0;
                return amount_cowboy+amount_ninja;
            }

            

            
        }
        else
        {
            amount_cowboy=0;
            amount_ninja=0;
            return amount_cowboy+amount_ninja;
        }
        
   }
   else if (leader==2 && !n_warriors[0]->isAlive())
   {
    //the leader is ded, need to replace
        if(amount_cowboy>0 || amount_ninja>1)
        {
            double min=std::numeric_limits<double>::infinity();
            int index=0;
            for (int i = 0; i < amount_cowboy; i++)
            {
                dis=n_warriors[0]->getLocation().distance(c_warriors[i]->getLocation());
                if(min>dis)
                {
                    if(c_warriors[i]->isAlive())
                    {
                        index=i;
                        leader=1;
                        min=dis;
                    }
                }
            }
            for (int i = 1; i < amount_ninja; i++)
            {
                dis=n_warriors[0]->getLocation().distance(n_warriors[i]->getLocation());
                if(min>dis)
                {
                    if(n_warriors[i]->isAlive())
                    {
                        index=i;
                        leader=2;
                        min=dis;
                    }
                }
            }

            if(leader==2)
            {
                
                n_warriors[0]=n_warriors[index];
                for (int i = index; i < amount_ninja-1; i++)
                {
                    n_warriors[i]=n_warriors[i+1];
                }
                amount_ninja--;
                
            }
            else if (leader==1)
            {
                
                Cowboy* temp=c_warriors[0];
                c_warriors[0]=c_warriors[index];
                c_warriors[index]=temp;
                
                
                
            }
            else
            {
                amount_cowboy=0;
                amount_ninja=0;
                return amount_cowboy+amount_ninja;
            }
        
 
        }
        else
        {
            amount_cowboy=0;
            amount_ninja=0;
            return amount_cowboy+amount_ninja;
        }
    }
    
    
    for (int i = 0; i < amount_cowboy; i++)
    {
        if(!c_warriors[i]->isAlive())
        {
            
            for (int j = i; j < amount_cowboy-1; j++)
            {
                   c_warriors[j]=c_warriors[j+1];
            }
            amount_cowboy--;
        }
    }
    for (int i = 0; i < amount_ninja; i++)
    {
        if(!n_warriors[i]->isAlive())
        {
            
            for (int j = i; j < amount_ninja-1; j++)
            {
                n_warriors[j]=n_warriors[j+1];
            }
            amount_ninja--;
        }
    }
        
   

    return amount_cowboy+amount_ninja;

}
void Team::print()
{
    if(stillAlive())
    {
        printf("Team, amount cowboy:%d, amount ninja:%d",amount_cowboy,amount_ninja);
        if(leader==1)
        {
            printf(", the leader is cowboy\n");
        }
        else if (leader==2)
        {
            printf(", the leader is ninja\n");
        }
        for (int i = 0; i < amount_cowboy; i++)
        {
            cout << c_warriors[i]->print()<<endl;
        }
        for (int i = 0; i < amount_ninja; i++)
        {
           cout << n_warriors[i]->print()<<endl;
        }
    }
    else
    {
        printf("the team is ded\n");
    }
    

    
}
void Team::setLeader(int lead)
{
    leader=lead;
}
void Team::attack(Team* other)
{
    if(other==nullptr)
    {
        throw invalid_argument("null");
    }
    
    if(this==other)
    {
        throw std::invalid_argument("the same team");
    }
    if(!stillAlive() || !other->stillAlive())
    {
        throw std::runtime_error("the team is ded");
    }

    int index= choose_vic(other);
    
    int wich=0;
    if(index==-1)
    {
        other->amount_cowboy=0;
        other->amount_ninja=0;
        return;
    }
    //find if the index is ninja or cowboy
        
    if(index>=other->amount_cowboy)
    {
        wich=2;
    } 
    else if (index>=other->amount_ninja)
    {
        wich=1;
    }
    else if(leader==1)//leader is cowboy
    {       
        int dis1=c_warriors[0]->getLocation().distance(other->c_warriors[index]->getLocation());
     
        int dis2=c_warriors[0]->getLocation().distance(other->n_warriors[index]->getLocation());
        if(dis1<dis2)
        {
     
            wich=1;
        }
        else
        {
       
            wich=2;
        }

    }
    else if (leader==2)//leader is ninja
    {
        int dis1=n_warriors[0]->getLocation().distance(other->c_warriors[index]->getLocation());

        int dis2=n_warriors[0]->getLocation().distance(other->n_warriors[index]->getLocation());
        if(dis1<dis2)
        {
            wich=1;
        }
        else
        {
            wich=2;
        }
    }
    
    
    int count1=-1;
    int count2=-1;
    while (++count1<amount_cowboy)         
    {
        
        if(wich==1 && !other->c_warriors[index]->isAlive())//the vic is cowboy and he is ded
        {
            index= choose_vic(other);
            wich=0;
            if(index==-1)
            {
                other->amount_cowboy=0;
                other->amount_ninja=0;
                return;
            }
            //find if the index is ninja or cowboy
            if(index>=other->amount_cowboy)
            {
                wich=2;
            } 
            else if (index>=other->amount_ninja)
            {
                wich=1;
            }
             else if(leader==1)//leader is cowboy
            {       
                int dis1=c_warriors[0]->getLocation().distance(other->c_warriors[index]->getLocation());
                int dis2=c_warriors[0]->getLocation().distance(other->n_warriors[index]->getLocation());
                if(dis1<dis2)
                {
                    wich=1;
                }
                else
                {
                    wich=2;
                }
            }
            else if (leader==2)//leader is ninja
            {
                int dis1=n_warriors[0]->getLocation().distance(other->c_warriors[index]->getLocation());
                int dis2=n_warriors[0]->getLocation().distance(other->n_warriors[index]->getLocation());
                if(dis1<dis2)
                {
                    wich=1;
                }
                else
                {
                    wich=2;
                }
            }

        }
        else if (wich==2 && !other->n_warriors[index]->isAlive())//the vic is ninja and he is ded
        {
            index= choose_vic(other);
            wich=0;
            if(index==-1)
            {
                other->amount_cowboy=0;
                other->amount_ninja=0;
                return;
            }
            //find if the index is ninja or cowboy
            if(index>=other->amount_cowboy)
            {
                wich=2;
            } 
            else if (index>=other->amount_ninja)
            {
                wich=1;
            }
            else if(leader==1)//leader is cowboy
            {       
                int dis1=c_warriors[0]->getLocation().distance(other->c_warriors[index]->getLocation());
                int dis2=c_warriors[0]->getLocation().distance(other->n_warriors[index]->getLocation());
                if(dis1<dis2)
                {
                    wich=1;
                }
                else
                {
                    wich=2;
                }
            }
            else if (leader==2)//leader is ninja
            {
                int dis1=n_warriors[0]->getLocation().distance(other->c_warriors[index]->getLocation());
                int dis2=n_warriors[0]->getLocation().distance(other->n_warriors[index]->getLocation());
                if(dis1<dis2)
                {
                    wich=1;
                }
                else
                {
                    wich=2;
                }
            }
        }
        
        if(wich==1 && c_warriors[count1]->hasboolets())//hit the cowboy
        {
            c_warriors[count1]->shoot(other->c_warriors[index]);
        }
        else if(!c_warriors[count1]->hasboolets())//reload
        {
            c_warriors[count1]->reload();
        }
        else if (wich==2 && c_warriors[count1]->hasboolets())//hit the ninja
        {
            c_warriors[count1]->shoot(other->n_warriors[index]);
        }
        
    }
    while (++count2<amount_ninja)         
    {
        
        if(wich==1 && !other->c_warriors[index]->isAlive())//the vic is cowboy and he is ded
        {
            index= choose_vic(other);
            wich=0;
            if(index==-1)
            {
                other->amount_cowboy=0;
                other->amount_ninja=0;
                return;
            }
            //find if the index is ninja or cowboy
            if(index>=other->amount_cowboy)
            {
                wich=2;
            } 
            else if (index>=other->amount_ninja)
            {
                wich=1;
            }
            else if(leader==1)//leader is cowboy
            {       
                int dis1=c_warriors[0]->getLocation().distance(other->c_warriors[index]->getLocation());
                int dis2=c_warriors[0]->getLocation().distance(other->n_warriors[index]->getLocation());
                if(dis1<dis2)
                {
                    wich=1;
                }
                else
                {
                    wich=2;
                }
            }
            else if (leader==2)//leader is ninja
            {
                int dis1=n_warriors[0]->getLocation().distance(other->c_warriors[index]->getLocation());
                int dis2=n_warriors[0]->getLocation().distance(other->n_warriors[index]->getLocation());
                if(dis1<dis2)
                {
                    wich=1;
                }
                else
                {
                    wich=2;
                }
            }

        }
        else if (wich==2 && !other->n_warriors[index]->isAlive())//the vic is ninja and he is ded
        {
            index= choose_vic(other);
            wich=0;
            if(index==-1)
            {
                other->amount_cowboy=0;
                other->amount_ninja=0;
                return;
            }
            //find if the index is ninja or cowboy
            if(index>=other->amount_cowboy)
            {
                wich=2;
            } 
            else if (index>=other->amount_ninja)
            {
                wich=1;
            }
            else if(leader==1)//leader is cowboy
            {       
                int dis1=c_warriors[0]->getLocation().distance(other->c_warriors[index]->getLocation());
                int dis2=c_warriors[0]->getLocation().distance(other->n_warriors[index]->getLocation());
                if(dis1<dis2)
                {
                    wich=1;
                }
                else
                {
                    wich=2;
                }
            }
            else if (leader==2)//leader is ninja
            {
                int dis1=n_warriors[0]->getLocation().distance(other->c_warriors[index]->getLocation());
                int dis2=n_warriors[0]->getLocation().distance(other->n_warriors[index]->getLocation());
                if(dis1<dis2)
                {
                    
                    wich=1;
                }
                else
                {
                    
                    wich=2;
                }
                
            }
        }
        
        if(wich==1 && n_warriors[count2]->getLocation().distance(other->c_warriors[index]->getLocation())<1)//hit the cowboy
        {
            n_warriors[count2]->slash(other->c_warriors[index]);
        }
        else if(wich==1 && n_warriors[count2]->getLocation().distance(other->c_warriors[index]->getLocation())>=1)//move to cowboy
        {
            n_warriors[count2]->move(other->c_warriors[index]);
        }
        else if (wich==2 && n_warriors[count2]->getLocation().distance(other->n_warriors[index]->getLocation())<1)//hit the ninja
        {
            n_warriors[count2]->slash(other->n_warriors[index]);
        }
        else if (wich==2 && n_warriors[count2]->getLocation().distance(other->n_warriors[index]->getLocation())>=1)//move to ninja
        {
            n_warriors[count2]->move(other->n_warriors[index]);
        }
            
    }  
    
}

int Team:: choose_vic(Team* other)
{
    if(!stillAlive() || !other->stillAlive())
    {
        return -1;
    }
    double min=std::numeric_limits<double>::infinity();
    int index=-1;
    if(leader==1)
    {  

 
        for (int i = 0; i < other->amount_cowboy; i++)
        {
            double dis=c_warriors[0]->getLocation().distance(other->c_warriors[i]->getLocation());
            if(min>dis)
            {
                if(other->c_warriors[i]->isAlive())
                {
                    index=i;
                    min=dis;
                  
                }
            }
        }
        for (int i = 0; i < other->amount_ninja; i++)
        {
            double dis=c_warriors[0]->getLocation().distance(other->n_warriors[i]->getLocation());
            if(min>dis)
            {
                if(other->n_warriors[i]->isAlive())
                {
                    index=i;
                    min=dis;
                  
                }
            }
        }

    }
    else if(leader==2)
    {

       for (int i = 0; i < other->amount_cowboy; i++)
        {
            double dis=n_warriors[0]->getLocation().distance(other->c_warriors[i]->getLocation());
            if(min>dis)
            {
                if(other->c_warriors[i]->isAlive())
                {
                    index=i;
                    min=dis;
                  
                }
            }
        }
        for (int i = 0; i < other->amount_ninja; i++)
        {
            double dis=n_warriors[0]->getLocation().distance(other->n_warriors[i]->getLocation());
            if(min>dis)
            {
                if(other->n_warriors[i]->isAlive())
                {
                    index=i;
                    min=dis;
                  
                }
            }
        }
    }
    
    return index;
}
int Team:: get_amount_cowboy()const
{
    return amount_cowboy;
}
int Team::get_amount_ninja()const
{
    return amount_ninja;
}
void Team::set_amount_ninja(int amo)
{
    amount_ninja=amo;
}
void Team::set_amount_cowboy(int amo)
{
    amount_cowboy=amo;
}
Cowboy** Team:: get_c_warriors()
{
    return c_warriors;
}
Ninja** Team:: get_n_warriors()
{
    return n_warriors;
}
int Team:: get_leader()
{
    return leader;
}  




   

