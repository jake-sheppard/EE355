#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }

  int size, initMoves, seed, heur;

  size = atoi(argv[1]);
  initMoves = atoi(argv[2]);
  seed = atoi(argv[3]);
  heur = atoi(argv[4]);

  Board b(size,initMoves,seed);
  

  PuzzleHeuristic* ph;
  if(heur == 0){
    ph = new PuzzleBFSHeuristic;
  }
  else if(heur == 1){
    ph = new PuzzleOutOfPlaceHeuristic;
  }
  else {
    ph = new PuzzleManhattanHeuristic;
  }
  

  //*********** Implement the gameplay here
  int userInput = 1;
  while (userInput != 0){
    cout << b;
    cout << endl;
    if (b.solved()){
      cout << "Puzzled Solved!" << endl;
      break; // get out of loop
    }
    cout << "Enter tile number to move or -1 for a cheat: ";
    cin >> userInput;
    if (userInput == -1){
      PuzzleSolver solver(b,ph);
      solver.run();
      cout << "Try this sequence: " << endl;
      deque<int> deq = solver.getSolution();
      while (!deq.empty()){
        cout << deq.front() << " ";
        deq.pop_front();
      }
      cout << endl;
      cout << "(Expansions = "<<solver.getNumExpansions()<<")"<<endl;     
    }
    else if (userInput == 0){
      break;
    }
    else {
          b.move(userInput); 
    }
  }

  return 0;
}
