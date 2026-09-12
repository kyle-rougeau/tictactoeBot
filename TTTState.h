#ifndef TTTSTATE_H
#define TTTSTATE_H

#include <iostream>
using namespace std;

class TTTState
{
   private:
      char state[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
   
   public:
      TTTState();
      
      char getState(int indx);
      int setState(int indx, bool isCross);
      
      void disp();
      bool isWin();
};

#endif
