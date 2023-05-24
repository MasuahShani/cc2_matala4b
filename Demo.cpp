/**
 * Demo file for the exercise on binary tree
 *
 * @author Evgeny Hershkovitch Neiterman
 * @since 2023-03
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
using namespace std;

#include "sources/Team.hpp" //no need for other includes

#include "sources/Team2.hpp"///////////////////////////////
#include "sources/SmartTeam.hpp"///////////////////////////////
using namespace ariel;


int main() {
   //  Point a(32.3,44),b(1.3,3.5);
   //  assert(a.distance(b) == b.distance(a));
   //  Cowboy *tom = new Cowboy("Tom", a);
   //  OldNinja *sushi = new OldNinja("sushi", b);
   //   /////////////////
   //   cout << tom->print() <<endl;
   // cout << sushi->print() <<endl;
   // /////////////

   //  tom->shoot(sushi);
   //  cout << tom->print() <<endl;
   //  /////////////////
   // cout << sushi->print() <<endl;
   // cout << "dis:"<<sushi->getLocation().distance(tom->getLocation())<<endl;
   // /////////////


   //  sushi->move(tom);
   //  sushi->slash(tom);
   // /////////////////
   //  cout << tom->print() <<endl;
   // cout << sushi->print() <<endl;
   // cout << "dis:"<<sushi->getLocation().distance(tom->getLocation())<<endl;
   // /////////////


   //  Team team_A(tom); 
   //  team_A.add(new YoungNinja("Yogi", Point(64,57)));

   //  //Team f(tom);// should throw tom is already in team a
   //  //team_A.add(tom);// should throw tom is already in team a
   //   Team team_B(sushi);
   //   team_B.add(new TrainedNinja("Hikari", Point(12,81)));
   //  /////////////////////////////////////////////////////////////
   //  team_A.print();
   //  team_B.print();
   //  // cout << team_A.stillAlive() <<endl;
   //  // cout << team_B.stillAlive() <<endl;
   //  // team_A.attack(&team_B);
   //  //////////////////////////////

   //   while(team_A.stillAlive() > 0 && team_B.stillAlive() > 0){
   //      team_A.attack(&team_B);
   //      //////
   //      team_A.print();
   //      team_B.print();
   //      /////////
   //      if(team_A.stillAlive() > 0 && team_B.stillAlive() > 0)
   //      {
   //          team_B.attack(&team_A);
   //          team_A.print();
   //          team_B.print();
   //      }
        
   //   }
    

   //   if (team_A.stillAlive() > 0) cout << "winner is team_A" << endl;
   //   else cout << "winner is team_B" << endl;

   //   ////////////////////////////////
   // Point p1(10,20);
   // Point p2(20,10);
   // cout<<p2.distance(p1)<<endl;
   // Point p3= Point::moveTowards(p2,p1,10);
   // cout<<p3.print()<<endl;
   //  cout<<p3.distance(p1)<<endl;
   //  p3= Point::moveTowards(p1,p2,10);

    


   // Point c(100,100);
   // Point d(200,150);
   // TrainedNinja* tn =new TrainedNinja("tn",c);
   // YoungNinja* yn =new YoungNinja("yn",d);
   // cout << tn->print() <<endl;
   // cout << yn->print() <<endl;
   // cout << "dis:"<<tn->getLocation().distance(yn->getLocation())<<endl;
   // tn->slash(yn);
   // cout << tn->print() <<endl;
   // cout << yn->print() <<endl;
   // tn->move(yn);
   // cout << "dis:"<<tn->getLocation().distance(yn->getLocation())<<endl;
   // tn->slash(yn);
   // cout << tn->print() <<endl;
   // cout << yn->print() <<endl;

   // cout << "team2:" <<endl;
   // Point e(10,100);
   // Point f(20,150);
   // Cowboy* c1 =new Cowboy("c1",e );
   // Cowboy* c2 =new Cowboy("c2",f );
  

   // Team2 team_c(c1);
   // Team2 team_d(yn);

   // team_c.add(tn);
   // team_d.add(c2);

   // while(team_c.stillAlive() > 0 && team_d.stillAlive() > 0){
   //      team_d.attack(&team_c);
   //      //////
   //      team_c.print();
   //      team_d.print();
   //      /////////
   //      if(team_c.stillAlive() > 0 && team_d.stillAlive() > 0)
   //      {
   //          team_c.attack(&team_d);
   //          team_c.print();
   //          team_d.print();
   //      }
        
   //   }
   //   if (team_c.stillAlive() > 0) cout << "winner is team_c" << endl;
   //   else cout << "winner is team_d" << endl;


 Point a(32.3,44),b(1.3,3.5);
    assert(a.distance(b) == b.distance(a));
    Cowboy *tom = new Cowboy("Tom", a);
    OldNinja *sushi = new OldNinja("sushi", b);
    tom->shoot(sushi);
    cout << tom->print() <<endl;

    sushi->move(tom);
    sushi->slash(tom);

    Team team_A(tom); 
    team_A.add(new YoungNinja("Yogi", Point(64,57)));

    // Team b(tom); should throw tom is already in team a

     Team team_B(sushi);
     team_B.add(new TrainedNinja("Hikari", Point(12,81)));


     while(team_A.stillAlive() > 0 && team_B.stillAlive() > 0){
        team_A.attack(&team_B);
        team_B.attack(&team_A);
        team_A.print();
        team_B.print();
     }

     if (team_A.stillAlive() > 0) cout << "winner is team_A" << endl;
     else cout << "winner is team_B" << endl;



     /////////////////////////////////////////////
     Point p8(0,0);
     Point p9(1,1);
     YoungNinja* nnn=new YoungNinja("nnn",p8);
      YoungNinja* mmm=new YoungNinja("mmm",p9);

      //nnn.move(mmm);

      cout<< nnn->getLocation().print()<<endl;

      Team2 team2(nnn);
      Team team(mmm);
      int i = 0;
    while (team.stillAlive() && team2.stillAlive()) {
        if (i % 2 == 0) {
            team.attack(&team2);
        } else {
            team2.attack(&team);
        }
        team2.print();
        team.print();
        i++;
    }

    ////////////////////////////////////////////////

    YoungNinja* n1=new YoungNinja("nn1n",p8);
    YoungNinja* n2=new YoungNinja("m1",p9);
    YoungNinja* n3=new YoungNinja("n2nn",p8);
    YoungNinja* n4=new YoungNinja("mm1m",p9);
    SmartTeam st1(n1);
    st1.add(n2);
    SmartTeam st2(n3);
    st2.add(n4);
    // Cowboy* cc1=new Cowboy("cc1",a);
    // Cowboy* cc2=new Cowboy("cc2",b);
    // st1.add(cc1);
    // st2.add(cc2);

    // cout<<st1.choose_vic(&st2)<<endl;
    //     cout<<st1.choose_vic2(&st2,st1.choose_vic(&st2))<<endl;
    //             cout<<st1.choose_vic2(&st2,st1.choose_vic2(&st2,st1.choose_vic(&st2)))<<endl;


    while (st1.stillAlive() && st2.stillAlive()) {
        if (i % 2 == 0) {
            st1.attack(&st2);
        } else {
            st2.attack(&st1);
        }
        st1.print();
        st2.print();
        i++;
    }


      


     return 0; // no memory issues. Team should free the memory of its members. both a and b teams are on the stack. 

}
