#include "SmartTeam.hpp"
using namespace ariel;


SmartTeam::SmartTeam(Character* leader): Team(leader),wich(new int[10])
{
    if(this->wich==nullptr)
    {
        throw runtime_error("null ptr");
    } 
    wich[0]=get_leader();
    index_leader=0;
}
SmartTeam::~SmartTeam()
{
    delete[] wich;

}
SmartTeam::SmartTeam():wich(new int[10])
{
    if(this->wich==nullptr)
    {
        throw runtime_error("null ptr");
    }
    wich[0]=get_leader();
    index_leader=0;


}
SmartTeam::SmartTeam (const SmartTeam& team):Team(team),wich(new int[10]),index_leader(team.index_leader)
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
SmartTeam::SmartTeam (SmartTeam &&team) noexcept:Team(move(team)),index_leader(team.index_leader)
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

SmartTeam& SmartTeam::operator=(const SmartTeam& team)
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

SmartTeam & SmartTeam::operator=(SmartTeam&& team) noexcept
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

void SmartTeam::add(Character* warrior)
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
int SmartTeam::stillAlive()
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
 
void SmartTeam::attack(Team* other)
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

int k1=0;
int k2=0;
int dis1=0;
int dis2=0;
int q=0;

while (q++<stillAlive()&&stillAlive()&&other->stillAlive())
{
  

    int index= choose_vic(other);
    int wich1=0;
    if(get_leader()==1)
    {
                

        if(other->get_amount_cowboy()<=index)
        {
            wich1=2;
        }
        else if(other->get_amount_ninja()<=index)
        {
            wich1=1;
        }
        else
        {
            int dis1=get_c_warriors()[0]->getLocation().distance(other->get_c_warriors()[index]->getLocation());
            int dis2=get_c_warriors()[0]->getLocation().distance(other->get_n_warriors()[index]->getLocation());
            if(dis1<dis2)
            {
                wich1=1;
            }
            else
            {
                wich1=2;
            }
        }
        

    }
    else if(get_leader()==2)
    {
               

        if(other->get_amount_cowboy()<=index)
        {
            wich1=2;
        }
        else if(other->get_amount_ninja()<=index)
        {
            wich1=1;
        }
        else
        {
            dis1=get_n_warriors()[0]->getLocation().distance(other->get_c_warriors()[index]->getLocation());
            dis2=get_n_warriors()[0]->getLocation().distance(other->get_n_warriors()[index]->getLocation());
            if(dis1<dis2)
            {
                wich1=1;
            }
            else
            {
                wich1=2;
            }
        }
        

    }
    int count=0;
    int sec=choose_vic2(other,index);
    if(get_amount_ninja()>0 && sec!=-1)
    {
        
        int wich2=0;
        

        if(get_leader()==1)
        {
            
            if(other->get_amount_cowboy()<=sec)
            {
                wich2=2;
            }
            else if(other->get_amount_ninja()<=sec)
            {
                wich2=1;
            }
            else
            {
                int dis1=get_c_warriors()[0]->getLocation().distance(other->get_c_warriors()[sec]->getLocation());
                int dis2=get_c_warriors()[0]->getLocation().distance(other->get_n_warriors()[sec]->getLocation());
                if(dis1<dis2)
                {
                    wich2=1;
                }
                else
                {
                    wich2=2;
                }
            }
            
            

        }
        else if(get_leader()==2)
        {
           

            if(other->get_amount_cowboy()<=sec)
            {
                wich2=2;
            }
            else if(other->get_amount_ninja()<=sec)
            {
                wich2=1;
            }
            else
            {
                int dis1=get_n_warriors()[0]->getLocation().distance(other->get_c_warriors()[sec]->getLocation());
                         

                int dis2=get_n_warriors()[0]->getLocation().distance(other->get_n_warriors()[sec]->getLocation());
                if(dis1<dis2)
                {
                    wich2=1;
                }
                else
                {
                    wich2=2;
                }
            }
            
                

        }
        
    
        for (int i = 0; i < get_amount_ninja(); i++)//check if most ninjas closer to the sec vic, we prefer to start with shooting
        {

            if(wich1==1)
            {
            int dis2=get_n_warriors()[i]->getLocation().distance(other->get_c_warriors()[index]->getLocation());
            }
            else
            {
                int dis2=get_n_warriors()[i]->getLocation().distance(other->get_n_warriors()[index]->getLocation());

            }
            if(wich2==1)
            {
                int dis1=get_n_warriors()[i]->getLocation().distance(other->get_c_warriors()[sec]->getLocation());
            }
            else
            {
                int dis1=get_n_warriors()[i]->getLocation().distance(other->get_n_warriors()[sec]->getLocation());
            }
            
                
            if(dis1>dis2)
            {
                count++;
            }
            
        }
    }

    if(count>(get_amount_ninja()-count) && k1<get_amount_cowboy())// most closer to the sec start with the cowboys
    {
      
        if(wich1==1)
        {
            if(get_c_warriors()[k1]->hasboolets()>0)
            {
                get_c_warriors()[k1++]->shoot(other->get_c_warriors()[index]);
            }
            else
            {
               get_c_warriors()[k1++]->reload();
            }
            
        }
        else
        {
            if(get_c_warriors()[k1]->hasboolets()>0)
            {
                get_c_warriors()[k1++]->shoot(other->get_n_warriors()[index]);
            }
            else
            {
               get_c_warriors()[k1++]->reload();
            }

        }
        
    }
    else if (count<=(get_amount_ninja()-count) && k2<get_amount_ninja() )
    {
                

        if(wich1==1)
        {
            if(get_n_warriors()[k2]->distance(other->get_c_warriors()[index])<1)
            {
                get_n_warriors()[k2++]->slash(other->get_c_warriors()[index]);
            }
            else
            {
               get_n_warriors()[k2++]->move(other->get_c_warriors()[index]);
            }
            
        }
        else
        {
             if(get_n_warriors()[k2]->distance(other->get_n_warriors()[index])<1)
            {
                get_n_warriors()[k2++]->slash(other->get_n_warriors()[index]);
            }
            else
            {
               get_n_warriors()[k2++]->move(other->get_n_warriors()[index]);
            }

        }
    }
    else if(count<(get_amount_ninja()-count) && k1<get_amount_cowboy())
    {
            

        if(wich1==1)
        {
            if(get_c_warriors()[k1]->hasboolets()>0)
            {
                get_c_warriors()[k1++]->shoot(other->get_c_warriors()[index]);
            }
            else
            {
               get_c_warriors()[k1++]->reload();
            }
            
        }
        else
        {
            if(get_c_warriors()[k1]->hasboolets()>0)
            {
                get_c_warriors()[k1++]->shoot(other->get_n_warriors()[index]);
            }
            else
            {
               get_c_warriors()[k1++]->reload();
            }

        }
        
    }
    else if (count>(get_amount_ninja()-count) && k2<get_amount_ninja() )
    {
                

        if(wich1==1)
        {
            if(get_n_warriors()[k2]->distance(other->get_c_warriors()[index])<1)
            {
                get_n_warriors()[k2++]->slash(other->get_c_warriors()[index]);
            }
            else
            {
               get_n_warriors()[k2++]->move(other->get_c_warriors()[index]);
            }
            
        }
        else
        {
             if(get_n_warriors()[k2]->distance(other->get_n_warriors()[index])<1)
            {
                get_n_warriors()[k2++]->slash(other->get_n_warriors()[index]);
            }
            else
            {
               get_n_warriors()[k2++]->move(other->get_n_warriors()[index]);
            }

        }
    }
    
    
}


}



void SmartTeam::print()
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

int SmartTeam:: choose_vic2(Team* other, int ind1)
{
    if(!stillAlive() || !other->stillAlive())
    {
        return -1;
    }
    if(other->stillAlive()==1)
    {
        return ind1;
    }
    double min=std::numeric_limits<double>::infinity();
    int index=-1;
    if(get_leader()==1)
    {  
 
        for (int i = 0; i < other->get_amount_cowboy(); i++)
        {
            if(i!=ind1)
            {
                double dis=get_c_warriors()[0]->getLocation().distance(other->get_c_warriors()[i]->getLocation());
                if(min>dis)
                {
                    if(other->get_c_warriors()[i]->isAlive())
                    {
                        index=i;
                        min=dis;
                    
                    }
                }
            }
            
        }
        for (int i = 0; i < other->get_amount_ninja(); i++)
        {
            if(i!=ind1)
            {
                double dis=get_c_warriors()[0]->getLocation().distance(other->get_n_warriors()[i]->getLocation());
                if(min>dis)
                {
                    if(other->get_n_warriors()[i]->isAlive())
                    {
                        index=i;
                        min=dis;
                    
                    }
                }
            }
            
        }

    }
    else if(get_leader()==2)
    {

       for (int i = 0; i < other->get_amount_cowboy(); i++)
        {
            if(i!=ind1)
            {
                double dis=get_n_warriors()[0]->getLocation().distance(other->get_c_warriors()[i]->getLocation());
                if(min>dis)
                {
                    if(other->get_c_warriors()[i]->isAlive())
                    {
                        index=i;
                        min=dis;
                    
                    }
                }                
            
            }
        }
        for (int i = 0; i < other->get_amount_ninja(); i++)
        {
            if(i!=ind1)
            {
                double dis=get_n_warriors()[0]->getLocation().distance(other->get_n_warriors()[i]->getLocation());
                if(min>dis)
                {
                    if(other->get_n_warriors()[i]->isAlive())
                    {
                        index=i;
                        min=dis;
                    
                    }
                }
            }
            
        }
    }
    
    



    
    return index;
}
