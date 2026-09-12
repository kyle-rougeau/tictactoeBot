.RECIPEPREFIX = >
objects = game.o main.o

tictactoe : $(objects)
> g++ -o tictactoe $(objects)
   
clean :
> rm $(objects)
