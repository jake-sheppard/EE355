/* 
crack.cpp

Author: Jake Sheppard

Short description of this file: Method of cracking a message.
*/

#include "caesarlib.h"
#include <fstream>
#include <iostream>

using namespace std;

// frequencies of letters in a large sample of English
const double enfreq[26] = {0.0793, 0.0191, 0.0392, 0.0351, 0.1093,
   0.0131, 0.0279, 0.0238, 0.0824, 0.0024, 0.0103, 0.0506, 0.0277,
   0.0703, 0.0602, 0.0274, 0.0019, 0.0705, 0.1109, 0.0652, 0.0321,
   0.0098, 0.0093, 0.0026, 0.0156, 0.0040};

// return score when ch is shifted (if ch not letter, return 0)
double char_score(char ch, int shift) {
   if (is_letter(ch)){
      char val = image(ch,shift);
      int index;
      if (val>=65 && val<=90){
         index = (static_cast<int>(val)-65) % 26;
      }
      else{
         index = (static_cast<int>(val)-97) % 26;
      }
      return enfreq[index];
   }
   else{
      return 0;
   }
}

// return score when contents of entire file are shifted
double file_score(const char filename[], int shift) {
   ifstream ifile(filename);
   double total = 0;
   char c;
   while (ifile.get(c)){
      total += char_score(c,shift);
   }
   return total;
}

int main(int argc, char* argv[]) {
   if (argc != 2) {
      cout << "Wrong number of arguments." << endl;
      cout << "Usage: crack ciphertext.txt" << endl;
      return 1;
   }
   
   // FILL this in
   double bestScore = 0;
   int tracker;
   for (int i = 0; i < 26; i++){
      double score = file_score(argv[1],i);
      if (score > bestScore){
         bestScore = score;
         tracker = i;
      }
   }
   print_file_image(argv[1],tracker);

   
   return 0;
}

