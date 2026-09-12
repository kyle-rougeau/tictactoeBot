#ifndef GAME_H
#define GAME_H

using namespace std;

class game
{
   private:
      char state[9];
      bool turnOrder;
      int turn;
   
   public:
      game();
      
      char getState(int indx);
      int getTurn();
      
      int play(int indx);
      void disp();
      bool isOver();
};

#endif
