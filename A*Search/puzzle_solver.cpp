#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "puzzle_solver.h"

using namespace std;

PuzzleSolver::PuzzleSolver(const Board& b, PuzzleHeuristic *ph) : _b(b), _ph(ph){
	_expansions = 0;
}

PuzzleSolver::~PuzzleSolver(){
	delete _ph;
}

void PuzzleSolver::run(){
	PuzzleMoveHeap openlist;
	PuzzleMoveSet closedlist;
	Board* start = new Board(_b);
	PuzzleMove* p = new PuzzleMove(start);
	openlist.push(p);
	closedlist.insert(p);
	map<int,Board*>m;


	
	
	bool stop = false;
	while ( (!openlist.empty()) && !stop) /*&& (!_b.solved()))*/{
		//_b = *(openlist.top()->b); 
		PuzzleMove* minstate = openlist.top();
		openlist.pop();		    // remove PuzzleMove from heap
		if (minstate->b->solved()){
			// trace solution path backwards & stop
			while (minstate->prev != NULL){
				_solution.push_front(minstate->tileMove);
				minstate = minstate->prev;
			}
			stop = true;
		}
		// generate next potential boards
		else{
			//map<int,Board*>m;
			//m = _b.potentialMoves();
			m = minstate->b->potentialMoves();
			map<int,Board*>::iterator it;
			for (it = m.begin(); it != m.end(); ++it){
				PuzzleMove* s = new PuzzleMove(it->first,it->second,minstate);
				// if move, s, is not in closed list
				if (closedlist.find(s) == closedlist.end()){
					s->score(_ph);
					openlist.push(s); // adding s to open list
					closedlist.insert(s); // adding s to closed list
					_expansions++; // increment # of expansions
				}
				else{
					delete s;

				}
			}
		}
	}

	PuzzleMoveSet::iterator it;
	for (it = closedlist.begin(); it != closedlist.end(); ++it){
		delete *it;
	}

}




int PuzzleSolver::getNumExpansions(){
  return _expansions;
}


std::deque<int> PuzzleSolver::getSolution(){
	return _solution;
}



