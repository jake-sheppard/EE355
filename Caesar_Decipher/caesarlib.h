/* 
caesarlib.cpp

Author: Jake Sheppard

Description: Library of functions that are used for identifying if a char is an English letter 
			 and also for shifting a char.
Header file for the caesarlib library.
Provide useful functionality for both parts of the assignment.
*/

#ifndef _H_CAESARLIB
#define _H_CAESARLIB

// is this char an English letter?
bool is_letter(char ch);

// return shifted image of ch (if ch not letter, don't shift)
// assumes 0 <= steps < 26
char image(char ch, int steps);

// shift all characters in this file and print it to cout
// return 1 if error (file couldn't be opened), 0 if no error
int print_file_image(const char filename[], int steps);


#endif
