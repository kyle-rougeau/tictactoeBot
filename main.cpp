#include <iostream>
#include "game.h"

using namespace std;

int player2(game ultg)
{
   int rowScore[3] = {2,2,2};
   int colScore[3] = {2,2,2};
   int fDiagScore = 2;
   int bDiagScore = 2;
   
   //in order: 2 against, 1 against, empty or mixed, mixed, 1 for, mixed
   int sum2score[] = {100,1,0,0,2,0};
   int spaceScore[9];
   int maxScore = 0;
   int maxIndx = 8;
   
   int turn = ultg.getTurn();
   
   bool amiKnots = turn%2 != 0;
   
   //first turn play
   if(turn == 0)
   {
      return 4;
   }
   else if(turn == 1)
   {
      if(ultg.getState(4) == 'x')
      {
         return 0;
      }
      else
      {
         return 4;
      }
   }
   else if(turn == 8)
   {
      for(int i = 0; i < 9; i++)
      {
         if(ultg.getState(i) == ' ')
         {
            return i;
         }
      }
   }
   else
   {
      //sum the scores for each row, column, and diagonal
      for(int row = 0; row < 3; row++)
      {
         for(int col = 0; col < 3; col++)
         {
            //cout << row*3 + col << ": " << (((row*3 + col)%2 == 0) && !((row*3 + col)%8 == 0)) << " | " << ((row*3 + col)%4 == 0) << "\n";
            //if space is occupied by bot
            if(ultg.getState(row*3 + col) == ((amiKnots)? 'o' : 'x'))
            {
               /*if(((row*3 + col)%2 == 0) && !((row*3 + col)%8 == 0))
               {
                  cout << row*3 + col << ": fdiag += 2\n";
               }
               if((row*3 + col)%4 == 0)
               {
                  cout << row*3 + col << ": bdiag += 2\n";
               }*/
               rowScore[row] += 2;
               colScore[col] += 2;
               fDiagScore += 2 * (((row*3 + col)%2 == 0) && !((row*3 + col)%8 == 0));
               bDiagScore += 2 * ((row*3 + col)%4 == 0);
            }
            //if space is occupied by player
            else if(ultg.getState(row*3 + col) == ((!amiKnots)? 'o' : 'x'))
            {
               /*if(((row*3 + col)%2 == 0) && !((row*3 + col)%8 == 0))
               {
                  cout << row*3 + col << ": fdiag -= 1\n";
               }
               if((row*3 + col)%4 == 0)
               {
                  cout << row*3 + col << ": bdiag -= 1\n";
               }*/
               rowScore[row] -= 1;
               colScore[col] -= 1;
               fDiagScore -= 1 * (((row*3 + col)%2 == 0) && !((row*3 + col)%8 == 0));
               bDiagScore -= 1 * ((row*3 + col)%4 == 0);
            }
         }
      }
      //assign a score to each square
      for(int row = 0; row < 3; row++)
      {
         for(int col = 0; col < 3; col++)
         {
            //if empty
            if(ultg.getState(row*3 + col) == ' ')
            {
               //if can win, win
               if(rowScore[row] == 6 || colScore[col] == 6 || ((((row*3 + col)%2 == 0) && !((row*3 + col)%8 == 0)) && (fDiagScore == 6)) || (((row*3 + col)%4 == 0) && (bDiagScore == 6)))
               {
                  //cout << row*3 + col << ": I can win\n";
                  return (row*3 + col);
               }
               //else assign score to space
               else
               {
                  spaceScore[row*3 + col] = sum2score[rowScore[row]] + sum2score[colScore[col]] + 2*sum2score[fDiagScore]*(((row*3 + col)%2 == 0) && !((row*3 + col)%8 == 0)) + 2*sum2score[bDiagScore]*((row*3 + col)%4 == 0);
               }
            }
         }
      }
      //pick best play
      for(int id = 0; id < 9; id++)
      {
         if(ultg.getState(id) == ' ')
         {
            //if can block, block
            if(spaceScore[id] >= 100)
            {
               //cout << id << ": I can block\n";
               return id;
            }
            //else, evaluate max
            else if(spaceScore[id] > maxScore)
            {
               maxScore = spaceScore[id];
               maxIndx = id;
            }
         }
      }	
      
      /*
      for(int i = 0; i < 9; i++)
      {
         cout << spaceScore[i] << " | ";
      }
      cout << "\n" << maxScore << " | " << maxIndx << "\n";
      */ 
   }
   
   /*cout << rowScore[0] << " | " << rowScore[1] << " | " << rowScore[2] << " | ";
   cout << colScore[0] << " | " << colScore[1] << " | " << colScore[2] << " | ";
   cout << fDiagScore << " | " << bDiagScore << "\n";*/
   return maxIndx;
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
