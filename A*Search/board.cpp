#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include "board.h"
using namespace std;

/*Board::Board(){
  _size = 0;
  _tiles = NULL;
}*/

Board::Board(int dim){
  _size = dim*dim;
  for (int i = 0; i < _size; i++){
    _tiles[i] = i;
  }
}

Board::Board(int dim, int numInitMoves, int seed )
{
  _size = dim*dim;
  _tiles = new int[_size];
  srand(seed);
  for(int i=0; i < _size; i++){
    _tiles[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < _size){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      _tiles[blankLoc] = _tiles[randNeighbor];
      _tiles[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }

}



void Board::move(int tile)
{
  int dim = static_cast<int>(sqrt(_size));
  int tr, tc, br, bc;

  // find the tile
  int i=-1;
  while(_tiles[++i] != tile);

  tr = i / dim; 
  tc = i % dim;

  // find the blank
  int j=-1;
  while(_tiles[++j] != 0);
  br = j / dim;
  bc = j % dim;

  // if they aren't next to each other just return
  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  _tiles[j] = tile;
  _tiles[i] = 0;
}



// Write the other member functions for this class
Board::Board(const Board &b){
  _size = b._size;
  _tiles = new int[b._size];
  for (int i = 0; i < b._size; i++){
    _tiles[i] = b._tiles[i];
  }
}


Board::~Board(){
  delete [] _tiles;
  
}

map<int, Board*> Board::potentialMoves() const{
    map<int, Board*> m;
    int i = 0;
    int dim = static_cast<int>(sqrt(_size));
    while (_tiles[i] != 0){   // search for blank tile
      i++;
    }

    // check all moves (N,W,S,E)
    int tile;
    // North
    if (i - dim >= 0){
      tile = i - dim;
      Board* b_n = new Board(*this);
      b_n->move(_tiles[tile]);
      m.insert(pair<int,Board*>(_tiles[tile],b_n));
    }
    // West
    if ((i%dim)  != 0){
      tile = i-1;
      Board* b_w = new Board(*this);
      b_w->move(_tiles[tile]);
      m.insert(pair<int,Board*>(_tiles[tile],b_w));
    }
    // South
    if ((i+dim) < _size){
      tile = i+dim;
      Board* b_s = new Board(*this);
      b_s->move(_tiles[tile]);
      m.insert(pair<int,Board*>(_tiles[tile],b_s));
    }
    // East
    if ( ((i+1)%dim)  != 0){
      tile = i+1;
      Board* b_e = new Board(*this);
      b_e->move(_tiles[tile]);
      m.insert(pair<int,Board*>(_tiles[tile],b_e));
    }

    return m;
 }



 ostream& operator<<(ostream &os, const Board &b){
    int dim = static_cast<int>(sqrt(b._size));
    for (int i = 0; i < b._size; i = i+dim){
      for (int j = 0; j < dim; j++){
        if (b._tiles[i+j] == 0){
          os <<setw(3)<<" ";
        }
        else{
          os <<setw(3)<< b._tiles[i+j];
        }
      }
      os << endl;
    }
    return os;
 }

 bool Board::operator<(const Board& rhs) const{
    for (int i = 0; i < _size; i++){
      if(_tiles[i] < rhs._tiles[i]){
        return 1;
      }
      else if (_tiles[i] > rhs._tiles[i]){
        return 0;
      }
    }
    return 0;
 }

bool Board::solved() const{
  for (int i = 0; i < _size; i++){
    if (_tiles[i] != i){
      return false;
    }
  }
  return true;
}

int Board::getTile(int loc) const{
  return _tiles[loc];
}

int Board::getSize() const{
  return _size;
}

int Board::getDim() const{
  int dim = static_cast<int>(sqrt(_size));
  return dim;
}