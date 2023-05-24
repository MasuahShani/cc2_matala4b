#include "Team2.hpp"
using namespace ariel;


Team2::Team2(Character* leader): Team(leader),wich(new int[10])
{
    if(this->wich==nullptr)
    {
        throw runtime_error("null ptr");
    } 
    wich[0]=get_leader();
    index_leader=0;
}
Team2::~Team2()
{
    delete[] wich;

}
Team2::Team2():wich(new int[10])
{
    if(this->wich==nullptr)
    {
        throw runtime_error("null ptr");
    }
    wich[0]=get_leader();
    index_leader=0;


}
Team2::Team2 (const Team2& team):Team(team),wich(new int[10]),index_leader(team.index_leader)
{
    if(this->wich==nullptr)
    {
        throw runtime_error("null ptr");
    }
    for (int i = 0; i < team.get_amount_cowboy()+team.get_amount_ninja(); i++)
    {
        wich[i]=team.wich[i];
    }
    

}
Team2::Team2 (Team2 &&team) noexcept:Team(move(team)),index_leader(team.index_leader)
{
    try {
       wich=new int[10];
    } catch (const std::bad_alloc&) {
        std::cerr << "Error: memory allocation failed." << std::endl;
        exit(1);
    }
    for (int i = 0; i < team.get_amount_cowboy()+team.get_amount_ninja(); i++)
    {
        wich[i]=team.wich[i];
    }
    team.wich=nullptr;
    
}

Team2& Team2::operator=(const Team2& team)
{
    if(this!=&team)
    {
        Team::operator=(team);
        delete[]wich;
        wich=new int[10];
        if(this->wich==nullptr)
        {
            throw runtime_error("null ptr");
        }
        for (int i = 0; i < team.get_amount_cowboy()+team.get_amount_ninja(); i++)
        {
            wich[i]=team.wich[i];
        }
        index_leader=team.index_leader;

    }
    return *this;
}

Team2 & Team2::operator=(Team2&& team) noexcept
{
    Team::operator=(team);
    delete[]wich;
    try {
        wich=new int[10];
    } catch (const std::bad_alloc&) {
        std::cerr << "Error: memory allocation failed." << std::endl;
        exit(1);
    }
    for (int i = 0; i < team.get_amount_cowboy()+team.get_amount_ninja(); i++)
    {
        wich[i]=team.wich[i];
    }
    team.wich=nullptr;
    index_leader=team.index_leader;
    return *this;
}

void Team2::add(Character* warrior)
{
    if(get_amount_cowboy()+get_amount_ninja()==10)
    {
        throw std::runtime_error("full team");
    }
    if(Cowboy* c_w = dynamic_cast<Cowboy*>(warrior))
    {
        if(c_w->getIn_team())
        {
            throw std::runtime_error("already in a team");
        }
        
        get_c_warriors()[get_amount_cowboy()]=c_w;
        wich[get_amount_cowboy()+get_amount_ninja()]=1;
        set_amount_cowboy(get_amount_cowboy()+1);
        c_w->setIn_team(true);


    }
    else if (Ninja* n_w = dynamic_cast<Ninja*>(warrior))
    {
        if(n_w->getIn_team())
        {
            throw std::runtime_error("already in a team");
        }
        get_n_warriors()[get_amount_ninja()]=n_w;
        wich[get_amount_cowboy()+get_amount_ninja()]=2;
        set_amount_ninja(get_amount_ninja()+1);
        n_w->setIn_team(true);

    }
    else
    {
        throw std::invalid_argument("invalid_argument");
    }

}
int Team2::stillAlive()
{

    if(get_amount_cowboy()==0&&get_amount_ninja()==0)
    {
        return 0;
    }
    double dis;
    if(get_leader()==1 && !get_c_warriors()[0]->isAlive() )
    {
        //the leader is ded, need to replace
        if(get_amount_cowboy()>1 || get_amount_ninja()>0)
        {
            double min=std::numeric_limits<double>::infinity();
            int index=0;
            int count1=1;
            int count2=0;
            for (int i = 1; i <get_amount_cowboy()+get_amount_ninja() ; i++)
            {
                if(wich[i]==1)
                {
                    dis=get_c_warriors()[0]->getLocation().distance(get_c_warriors()[count1]->getLocation());
                    if(min>dis)
                    {
                        if(get_c_warriors()[count1]->isAlive())
                        {
                            index=i;
                            setLeader(1);
                            min=dis;
                        }
                    }
                    count1++;
                }
                else
                {
                    dis=get_c_warriors()[0]->getLocation().distance(get_n_warriors()[count2]->getLocation());
                    if(min>dis)
                    {
                        if(get_n_warriors()[count2]->isAlive())
                        {
                            index=i;
                            setLeader(2);
                            min=dis;
                        }
                    }
                    count2++;

                }
            }

            if(get_leader()==1)
            {


                get_c_warriors()[0]=get_c_warriors()[index];
                for (int i = index; i < get_amount_cowboy()-1; i++)
                {
                    get_c_warriors()[i]=get_c_warriors()[i+1];
                }
                int index2=-1;
                int a=0;
                while (a<=index)
                {
                    index2++;
                    if(wich[index2]==1)
                    {
                        a++;
                    }
                    
                }
                
                
                for (int i = index_leader; i < get_amount_cowboy()+get_amount_ninja()-1; i++)
                {
                    wich[i]=wich[i+1];
                }
                if (index2>index_leader)
                {
                    index2--;
                }
                
                
                index_leader=index2;
                set_amount_cowboy(get_amount_cowboy()-1);
                
            }
            else if (get_leader()==2)
            {   
           
                Ninja* temp=get_n_warriors()[0];
                get_n_warriors()[0]=get_n_warriors()[index];
                get_n_warriors()[index]=temp;
                int index2=-1;
                int a=0;
                while (a<=index)
                {
                    index2++;
                    if(wich[index2]==2)
                    {
                        a++;
                    }
                    
                }
                
                index_leader=index2;
                
                
            }
            else
            {
                set_amount_cowboy(0);
                set_amount_ninja(0);
                return 0;
            }

      
            

            
        }
        else
        {
            set_amount_cowboy(0);
            set_amount_ninja(0);
            return 0;
        }
        
   }
   else if (get_leader()==2 && !get_n_warriors()[0]->isAlive())
   {
    
    //the leader is ded, need to replace
        if(get_amount_cowboy()>0 || get_amount_ninja()>1)
        {
           
            double min=std::numeric_limits<double>::infinity();
            int index=0;
            int count1=0;
            int count2=1;
            for (int i = 1; i <get_amount_cowboy()+get_amount_ninja() ; i++)
            {
                if(wich[i]==1)
                {
                    dis=get_n_warriors()[0]->getLocation().distance(get_c_warriors()[count1]->getLocation());
                    if(min>dis)
                    {
                        if(get_c_warriors()[count1]->isAlive())
                        {
                            index=i;
                            setLeader(1);
                            min=dis;
                        }
                    }
                    count1++;
                }
                else
                {
                    dis=get_n_warriors()[0]->getLocation().distance(get_n_warriors()[count2]->getLocation());
                    if(min>dis)
                    {
                        if(get_n_warriors()[count2]->isAlive())
                        {
                            index=i;
                            setLeader(2);
                            min=dis;
                        }
                    }
                    count2++;

                }
            }
       
            if(get_leader()==2)
            {
  
                get_n_warriors()[0]=get_n_warriors()[index];
                for (int i = index; i < get_amount_ninja()-1; i++)
                {
                    get_n_warriors()[i]=get_n_warriors()[i+1];
                }

                int index2=-1;
                int a=0;
                while (a<=index)
                {
                    index2++;
                    if(wich[index2]==2)
                    {
                        a++;
                    }
                    
                }
             


                for (int i = index_leader; i < get_amount_cowboy()+get_amount_ninja()-1; i++)
                {
                    wich[i]=wich[i+1];
                }
            
                if(index2>index_leader)
                {
                    index2--;
                }
                index_leader=index2;
                set_amount_ninja(get_amount_ninja()-1);
                
            }
            else if (get_leader()==1)
            {
     

                
                Cowboy* temp=get_c_warriors()[0];
                get_c_warriors()[0]=get_c_warriors()[index];
                get_c_warriors()[index]=temp;
                int index2=-1;
                int a=0;
                while (a<=index)
                {
                    index2++;
                    if(wich[index2]==2)
                    {
                        a++;
                    }
                    
                }
                
                index_leader=index2;
                
                
                
            }
            else
            {
                set_amount_cowboy(0);
                set_amount_ninja(0);
                return 0;
            }
        

        }
        else
        {
            set_amount_cowboy(0);
            set_amount_ninja(0);
            return 0;
        }
    }
         
    
    for (int i = 0; i < get_amount_cowboy(); i++)
    {
        
        if(!get_c_warriors()[i]->isAlive())
        {
            
            for (int j = i; j < get_amount_cowboy()-1; j++)
            {
                get_c_warriors()[j]=get_c_warriors()[j+1];
                
            }
            int index2=-1;
            int a=0;
            while (a<=i)
            {
                index2++;
               
                if(wich[index2]==1)
                {
                    a++;
                }
                
            }
            for (int x = index2; x < get_amount_cowboy()+get_amount_ninja()-1; x++)
            {
                wich[x]=wich[x+1];
            }
            
            set_amount_cowboy(get_amount_cowboy()-1);
        }
    }
    for (int i = 0; i < get_amount_ninja(); i++)
    {
       
        if(!get_n_warriors()[i]->isAlive())
        {
            for (int j = i; j < get_amount_ninja()-1; j++)
            {
                get_n_warriors()[j]=get_n_warriors()[j+1];
            }
            int index2=-1;
            int a=0;
            while (a<=i)
            { 
                index2++;
                if(wich[index2]==2)
                {
                    a++;
                }
                
            }
            
            for (int x = index2; x < get_amount_cowboy()+get_amount_ninja()-1; x++)
            {
                wich[x]=wich[x+1];
            }
            set_amount_ninja(get_amount_ninja()-1);
        }
    }
        
   

    return get_amount_cowboy()+get_amount_ninja();

}
void Team2::attack(Team* other)
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

    int wichone=0;
    if(index==-1)
    {
        other->set_amount_cowboy(0);
        other->set_amount_ninja(0);
        return;
    }
    //find if the index is ninja or cowboy
   
    if(index>=other->get_amount_cowboy())
    {
        wichone=2;
    } 
    else if (index>=other->get_amount_ninja())
    {
        wichone=1;
    }
    else if(get_leader()==1)//leader is cowboy
    {       
        int dis1=get_c_warriors()[0]->getLocation().distance(other->get_c_warriors()[index]->getLocation());
        int dis2=get_c_warriors()[0]->getLocation().distance(other->get_n_warriors()[index]->getLocation());
        if(dis1<dis2)
        {
            wichone=1;
        }
        else
        {
            wichone=2;
        }
    }
    else if (get_leader()==2)//leader is ninja
    {
        int dis1=get_n_warriors()[0]->getLocation().distance(other->get_c_warriors()[index]->getLocation());
        int dis2=get_n_warriors()[0]->getLocation().distance(other->get_n_warriors()[index]->getLocation());
        if(dis1<dis2)
        {
            wichone=1;
        }
        else
        {
            wichone=2;
        }
    }
    
    
    int count1=0;
    int count2=0;
    int count=-1;
    while (++count<get_amount_cowboy()+get_amount_ninja())         
    {
        if(wichone==1 && !other->get_c_warriors()[index]->isAlive())//the vic is cowboy and he is ded
        {
            index= choose_vic(other);
            wichone=0;
            if(index==-1)
            {
                other->set_amount_cowboy(0);
                other->set_amount_ninja(0);
                return;
            }
            //find if the index is ninja or cowboy
            if(index>=other->get_amount_cowboy())
            {
                wichone=2;
            } 
            else if (index>=other->get_amount_ninja())
            {
                wichone=1;
            }
             else if(get_leader()==1)//leader is cowboy
            {   
                int dis1=get_c_warriors()[0]->getLocation().distance(other->get_c_warriors()[index]->getLocation());
                int dis2=get_c_warriors()[0]->getLocation().distance(other->get_n_warriors()[index]->getLocation());
                if(dis1<dis2)
                {
                    wichone=1;
                }
                else
                {
                    wichone=2;
                }
            }
            else if (get_leader()==2)//leader is ninja
            {
                int dis1=get_n_warriors()[0]->getLocation().distance(other->get_c_warriors()[index]->getLocation());
                int dis2=get_n_warriors()[0]->getLocation().distance(other->get_n_warriors()[index]->getLocation());
                if(dis1<dis2)
                {
                    wichone=1;
                }
                else
                {
                    wichone=2;
                }
            }

        }
        else if (wichone==2 && !other->get_n_warriors()[index]->isAlive())//the vic is ninja and he is ded
        {
            index= choose_vic(other);
            wichone=0;
            if(index==-1)
            {
                other->set_amount_cowboy(0);
                other->set_amount_ninja(0);
                return;
            }
            //find if the index is ninja or cowboy
            if(index>=other->get_amount_cowboy())
            {
                wichone=2;
            } 
            else if (index>=other->get_amount_ninja())
            {
                wichone=1;
            }
            else if(get_leader()==1)//leader is cowboy
            {       
                int dis1=get_c_warriors()[0]->getLocation().distance(other->get_c_warriors()[index]->getLocation());
                int dis2=get_c_warriors()[0]->getLocation().distance(other->get_n_warriors()[index]->getLocation());
                if(dis1<dis2)
                {
                    wichone=1;
                }
                else
                {
                    wichone=2;
                }
            }
            else if (get_leader()==2)//leader is ninja
            {
                int dis1=get_n_warriors()[0]->getLocation().distance(other->get_c_warriors()[index]->getLocation());
                int dis2=get_n_warriors()[0]->getLocation().distance(other->get_n_warriors()[index]->getLocation());
                if(dis1<dis2)
                {
                    wichone=1;
                }
                else
                {
                    wichone=2;
                }
            }
        }
        
        

        if(wichone==1 && wich[count]==1&& get_c_warriors()[count1]->hasboolets())//hit the cowboy
        {
            get_c_warriors()[count1]->shoot(other->get_c_warriors()[index]);
        }
        else if(wich[count]==1 && !get_c_warriors()[count1]->hasboolets())//reload
        {
            get_c_warriors()[count1]->reload();
        }
        else if (wichone==2 && wich[count]==1&& get_c_warriors()[count1]->hasboolets())//hit the ninja
        {
            get_c_warriors()[count1]->shoot(other->get_n_warriors()[index]);
        }
        
        else if(wichone==1 && wich[count]==2&& get_n_warriors()[count2]->getLocation().distance(other->get_c_warriors()[index]->getLocation())<1)//hit the cowboy
        {
            get_n_warriors()[count2]->slash(other->get_c_warriors()[index]);
        }
        else if(wichone==1 && wich[count]==2&& get_n_warriors()[count2]->getLocation().distance(other->get_c_warriors()[index]->getLocation())>=1)//move to cowboy
        {
            get_n_warriors()[count2]->move(other->get_c_warriors()[index]);
        }
        else if (wichone==2 && wich[count]==2&& get_n_warriors()[count2]->getLocation().distance(other->get_n_warriors()[index]->getLocation())<1)//hit the ninja
        {
            get_n_warriors()[count2]->slash(other->get_n_warriors()[index]);
        }
        else if (wichone==2 && wich[count]==2&& get_n_warriors()[count2]->getLocation().distance(other->get_n_warriors()[index]->getLocation())>=1)//move to ninja
        {
            get_n_warriors()[count2]->move(other->get_n_warriors()[index]);
        }
        if (wich[count]==1)
        {
           count1++;
        }
        else
        {
            count2++;
        }
        
    }
    
    
}



void Team2::print()
{
    if(stillAlive())
    {
        printf("Team, amount cowboy:%d, amount ninja:%d",get_amount_cowboy(),get_amount_ninja());
        if(get_leader()==1)
        {
            printf(", the leader is cowboy\n");
        }
        else if (get_leader()==2)
        {
            printf(", the leader is ninja\n");
        }
        int j1=0,j2=0;
        for (int i = 0; i < get_amount_cowboy()+get_amount_ninja(); i++)
        {
           if(wich[i]==1)
           {
                cout << get_c_warriors()[j1++]->print()<<endl;
           }
           else 
           {
                cout << get_n_warriors()[j2++]->print()<<endl;
           }
           
        }
        
        
    }
    else
    {
        printf("the team is ded\n");;
    }
    

}