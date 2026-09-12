#include <iostream>
#include "game.h"

using namespace std;

game::game()
{
   for(int i = 0; i < 9; i++){state[i] = ' ';}
   turn = 0;
   
   boardstate.disp();
}

char game::getState(int indx)
{
   return state[indx];
}
int game::play(int indx)
{  
   if (indx < 0 || indx >= 9)
   {
      cout << "\nErr: index out of range\n";
      return 1;
   }
   else if (state[indx] != ' ')
   {
      cout << "\nErr: square already filled\n";
      return 2;
   }
   
   state[indx] = (turn%2==0)? 'x' : 'o';
   turn++;
   
   return 0;
}

void game::disp()
{
   cout << "-------------\n";
   for(int row = 0; row < 3; row++)
   {
      cout << "| " << state[row*3] << " | " << state[row*3 + 1] << " | " << state[row*3 + 2] << " |\n-------------\n";
   }
}

bool game::isWin()
{  
   //check for a row win
   for(int row = 0; row < 3; row++)
   {
      bool xWin = true;
      bool oWin = true;
      
      for(int col = 0; col < 3 && (xWin || oWin); col++)
      {
         if(state[row*3 + col] != 'x')
         {
            xWin = false;
         }
         if(state[row*3 + col] != 'o')
         {
            oWin = false;
         }
      }
      
      if(xWin || oWin)
      {
         cout << ((xWin)? 'x' : 'o') << " wins!\n\n";
         return true;
      }
   }
   
   //check for a column win
   for(int col = 0; col < 3; col++)
   {
      bool xWin = true;
      bool oWin = true;
      
      for(int row = 0; row < 3 && (xWin || oWin); row++)
      {
         if(state[row*3 + col] != 'x')
         {
            xWin = false;
         }
         if(state[row*3 + col] != 'o')
         {
            oWin = false;
         }
      }
      
      if(xWin || oWin)
      {
         cout << ((xWin)? 'x' : 'o') << " wins!\n\n";
         return true;
      }
   }
   
   //check for a \ diagonal win
   bool xWin = true;
   bool oWin = true;
   for (int i = 0; i < 3; i++)
   {
      if(state[i*4] != 'x')
      {
         xWin = false;
      }
      if(state[i*4] != 'o')
      {
         oWin = false;
      }
   }
   if(xWin || oWin)
   {
      cout << ((xWin)? 'x' : 'o') << " wins!\n\n";
      return true;
   }
   
   //check for a / diagonal win
   xWin = true;
   oWin = true;
   for (int i = 0; i < 3; i++)
   {
      if(state[(i + 1)*2] != 'x')
      {
         xWin = false;
      }
      if(state[(i + 1)*2] != 'o')
      {
         oWin = false;
      }
   }
   if(xWin || oWin)
   {
      cout << ((xWin)? 'x' : 'o') << " wins!\n\n";
      return true;
   }
   return false;
}
