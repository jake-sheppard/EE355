/* 
libtest.cpp

Author: CS 103 Course staff

Description:
Runs a few basic tests of caesarlib.
See assignment page for expected output.
*/

#include "caesarlib.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
   cout << boolalpha;
   cout << is_letter('g') << " ";
   cout << is_letter('G') << " ";
   cout << is_letter('?') << endl;
   cout << image('S', 3) << " ";
   cout << image('w', 23) << " ";
   cout << image('?', 10) << endl;
   return 0;
}
