#include "puzzle_move.h"

PuzzleMove::PuzzleMove(Board* board){
	b = board;
	prev = NULL;
	g = 0;
}

PuzzleMove::PuzzleMove(int tile, Board *board, PuzzleMove *parent){
	tileMove = tile;
	b = board;
	prev = parent;
	g = (parent->g) + 1;
}

PuzzleMove::~PuzzleMove(){
	delete b;
}

bool PuzzleMove::operator<(const PuzzleMove& p) const{
	if (( (g+h) == (p.g+p.h))){
		{
			if (h < p.h){
				return 1;
			}
			else{
				return 0;
			}
		}
	}
	else if (( (g+h) < (p.g+p.h))){
		return 1;
	}
	else{
		return 0;
	}
}

void PuzzleMove::score(PuzzleHeuristic* ph){
	h = ph->compute(*b);
}


