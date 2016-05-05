/* 
shift.cpp

Author: Jake Sheppard

Short description of this file: printing the shifted output of input file
*/

#include "caesarlib.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
   if (argc != 3) {
      cout << "Wrong number of arguments." << endl;
      cout << "Usage: shift message.txt shift_number" << endl;
      return 1;
   }
   
   // read the arguments and print the shifted output
   char* fileName = argv[1];
   int steps = atoi(argv[2]);

   int result = print_file_image(fileName,steps); // FILL in
   
   // return sensible error if the filename is wrong
   if (result != 0) {
      cout << "Couldn't open the input file." << endl;
      return 1;
   }
   return 0;
}
