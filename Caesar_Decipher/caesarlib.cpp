/* 
caesarlib.cpp

Author: Jake Sheppard

Short description of this file: .cpp for caesarlib header file, functions for shifting 
 								and identifying if char is english letter.
*/

#include <fstream>
#include <iostream>
#include "caesarlib.h"

using namespace std;

// is this char an English letter?
bool is_letter(char ch) {
	if ((ch >= 65 && ch <=90) || (ch >= 97 && ch <= 122)){
		return true;
	}  
	else{
		return false;
	}
}

// return shifted image of ch (if ch not letter, don't shift)
// assumes 0 <= steps < 26
char image(char ch, int steps) {
	if (is_letter(ch)){
		if (ch >= 65 && ch <= 90){
			if ((ch + steps > 90) && (ch + steps <= 116)){
				ch = 64 + (char)((ch+steps)-90);
			}
			else{
				ch = ch + (char)steps;
			}
		}
		else if (ch >=97 && ch <= 122){
			if ((ch + steps) > 122){
				ch = 96 + (char)((ch+steps)-122);
			}
			else{
				ch = ch + (char)steps;
			}
		}
	} 
	return ch;
}

// shift all characters in this file and print it to cout
// return 1 if error (file couldn't be opened), 0 if no error
int print_file_image(const char filename[], int steps) {
	ifstream ifile;
	ifile.open(filename);
	if (ifile.fail()){
		return 1;
	}
	char c;
	while (ifile.get(c)){
		cout << image(c,steps);
	}
	ifile.close();
	return 0;
}





