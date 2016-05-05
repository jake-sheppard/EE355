#include <fstream>
#include <iostream>
//#include "caesarlib.h"

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
				ch += (char)steps;
			}
		}
		else if (ch >=97 && ch <= 122){
			if ((ch + steps) > 122){
				ch = 96 + (char)((ch+steps)-122);
			}
			else{
				ch += (char)steps;
			}
		}
	} 
	return ch;
}


int print_file_image(const char filename[], int steps) {
   ifstream ifile(filename);
   if (ifile.fail()){
   	return 1;
   }
   char c[100];
   ifile.getline(c,100);
   int size = ifile.tellg();
   for (int i = 0; i < size; i++){
   		image(c[i],steps);
   		cout << c[i];
   }
   cout << endl;
   ifile.close();
   return 0;
}

int main(){
	print_file_image("msg.txt",3);
}