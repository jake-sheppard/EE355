#include "puzzle_heur.h"
#include <cmath>



int PuzzleManhattanHeuristic::compute(const Board& b){
	//int dim = static_cast<int>(sqrt(b.getSize()));
	int score = 0;
	int dim = b.getDim();
	for (int i = 0; i < b.getSize(); i++){
		if (b.getTile(i) != i && b.getTile(i) != 0){
			// translate to row and col
			int row = i / dim;
			int col = i % dim;
			int tile = b.getTile(i);
			int rowLoc = tile / dim;
			int colLoc = tile % dim;
			score += abs(row-rowLoc) + abs(col-colLoc);
			
		}
	}

	return score;
}

int PuzzleOutOfPlaceHeuristic::compute(const Board& b){
	int count = 0;
	for (int i = 0; i < b.getSize(); i++){
		if (b.getTile(i) != i && b.getTile(i) != 0){
			count++;
		}
	}
	return count;
}

int PuzzleBFSHeuristic::compute(const Board& b){
	return 0;
}

