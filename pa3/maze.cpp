/* 
maze.cpp

Author: Jake Sheppard

Short description of this file: Finds and displays shortest path on a maze.
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main() {
   int rows, cols, result;
   char** mymaze;
   
   mymaze = read_maze(&rows,&cols);
   
   if (mymaze == NULL) {
      cout << "Error, input format incorrect" << endl;
      return 1;
   }

   result = maze_search(mymaze,rows,cols); 

   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

   // Deallocate memory
   
   for (int i=0; i < rows; i++){
      delete [] mymaze[i];
   }
   delete [] mymaze;

   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char** maze, int rows, int cols) {
   int sCount = 0;
   int fCount = 0;
   Location start, finish;
   for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
         if (maze[i][j] == 'S'){
            sCount++;
            start.row = i;
            start.col = j;
         }
         else if(maze[i][j] == 'F'){
            fCount++;
            finish.row = i;
            finish.col = j;
         }
      }
   }  
   if (fCount != 1 | sCount != 1){
      return -1; // INVALID MAZE
   }

   Queue q(rows*cols); // Initialize Queue
   // 2-D Array for visited locations
   int** visits = new int*[rows]; 
   for (int i = 0; i < rows; i++){
      visits[i] = new int[cols];
   }
   // 2-D Array for predecessors
   Location** pred = new Location*[rows];
   for (int i = 0; i < rows; i++) {
      pred[i] = new Location[cols];
   }
   q.add_to_back(start); // Adding start location to queue
   visits[start.row][start.col] = 1; // Added start location to visited list
   // Initializing visits array
   for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
        visits[i][j] = -1;
      }
   }  
   Location curr, loc;
   bool foundF = false;
   while(1){
      curr = q.remove_from_front();
      // North
      if (curr.row - 1 >= 0){ 
         loc.col = curr.col;
         loc.row = curr.row-1;
         if (maze[loc.row][loc.col] == 'F'){
            pred[loc.row][loc.col] = curr;
            foundF = true;
            break;
         }
         else if (visits[loc.row][loc.col] != 1 && maze[loc.row][loc.col] != '#'){
            q.add_to_back(loc); // Add location to queue
            visits[loc.row][loc.col] = 1; // Location has now been visited
            pred[loc.row][loc.col] = curr;
         }
      }
       // WEST
      if (curr.col - 1 >= 0){ 
         loc.col = curr.col -1;
         loc.row = curr.row;
         if (maze[loc.row][loc.col] == 'F'){
            pred[loc.row][loc.col] = curr;
            foundF = true;
            break;
         }
         else if (visits[loc.row][loc.col] != 1 && maze[loc.row][loc.col] != '#'){
            q.add_to_back(loc); // Add location to queue
            visits[loc.row][loc.col] = 1; // Location has now been visited
            pred[loc.row][loc.col] = curr;
         }
      }
       // SOUTH
      if (curr.row + 1 < rows){ 
         loc.col = curr.col;
         loc.row = curr.row+1;
         if (maze[loc.row][loc.col] == 'F'){
            pred[loc.row][loc.col] = curr;
            foundF = true;
            break;
         }
         else if (visits[loc.row][loc.col] != 1 && maze[loc.row][loc.col] != '#'){
            q.add_to_back(loc); // Add location to queue
            visits[loc.row][loc.col] = 1; // Location has now been visited
            pred[loc.row][loc.col] = curr;
         }
      }
      // EAST
      if (curr.col + 1 < cols){ 
         loc.col = curr.col+1;
         loc.row = curr.row;
         if (maze[loc.row][loc.col] == 'F'){
            pred[loc.row][loc.col] = curr;
            foundF = true;
            break;
         }
         else if (visits[loc.row][loc.col] != 1 && maze[loc.row][loc.col] != '#'){
            q.add_to_back(loc); // Add location to queue
            visits[loc.row][loc.col] = 1; // Location has now been visited
            pred[loc.row][loc.col] = curr;
         }
      }
      if (q.is_empty()){
         // Deallocate Memory
         for (int i=0; i < rows; i++){
            delete [] visits[i];
         }
         delete [] visits;
         
         for (int i=0; i < rows; i++){
         delete [] pred[i];
         }
         delete [] pred;

         return 0;
      }
      
   }
   if (foundF){
      while(maze[curr.row][curr.col] != 'S'){
         maze[curr.row][curr.col] = '*';
         curr = pred[curr.row][curr.col];
      }
      // Deallocate Memory
      for (int i=0; i < rows; i++){
         delete [] visits[i];
      }
      delete [] visits;

      for (int i=0; i < rows; i++){
         delete [] pred[i];
      }
      delete [] pred;


      return 1;
   }

   return 0;
}
