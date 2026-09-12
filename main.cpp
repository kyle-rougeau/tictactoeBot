#include <iostream>
#include "game.h"

using namespace std;

int player2(game ultg)
{
   int rowCnt[3][2];
   int colCnt[3][2];
   int fDiagCnt[2][2];
   
   int turn = ultg.getTurn();
   
   //TODO: make a "amiknotsorcrosses" variable
   
   //if player two
   if(turn%2 == 1)
   {
      //first play logic
      if(turn == 1)
      {
         //check if center is occupied
         if(ultg.getState(4) == 'o'){return 0;}
         else{return 4;}
      }
      else
      {
      
      }
   }
   //if player one
   else
   {
      //first play logic
      if(turn == 0)
      {
         
      }
      else
      {
         
      }
   }
   
   return 8;
}

int main()
{
   game myGame;
   bool turnOrder;
   char choice;
   
   //welcome player & get turn order
 
   
   //validate turn order choice
   bool valid = false;
   while(!valid)
   {
      cout << "\nWant to play first (y/n)? ";
      
      cin >> choice;
      if(choice == 'y' || choice == 'n'){valid = true;}
      else{cout << "Err: invalid choice\n";}
   }
   
   turnOrder = (choice == 'y');
   cin.ignore(1000,'\n');
   
   //main game loop for player vs cpu
   while(!myGame.isOver())
   {
      int pos;
      bool valid = false;
      
      if(myGame.getTurn()%2!=turnOrder)
      {
         while(!valid)
         {
            cout << "\n" << ((myGame.getTurn()%2 == 0)? 'x' : 'o') << "'s turn. Please select a square (1-9): ";
            if(cin >> pos){valid = (myGame.play(--pos) == 0);}
            else{cout << "You know what you did.\n"; cin.clear();}
            while((getchar())!='\n');
         }
      }
      else
      {
         myGame.play(player2(myGame));
      }
      
      myGame.disp();
   }
   
   return 0;
}
