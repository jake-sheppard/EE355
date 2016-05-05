#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cstdlib>
#include "character.h"
#include "point.h"
#include "bmplib.h"

using namespace std;

#define THRESH 127

unsigned char image[SIZE][SIZE];		// Input Image Data Array
unsigned char explored[SIZE][SIZE];		// Explored

Character find_bounding_box(int, int);


int main(int argc, char *argv[])
{

	int debug = atoi(argv[2]);

	if (argc != 3){
		cout << "Please enter file name and 1 or 0 indicating debug information" << endl;
		return 1;
	}
	 
	vector<Character> charVec;

	readGSBMP(argv[1],image); // Read in the image
	// Convert grayscale info to only black=0 or white=255 using THRESH
	for (int i=0; i < SIZE; i++){
		for (int j=0; j < SIZE; j++){
			if (image[i][j] < THRESH){
				image[i][j] = 0;

			}
			else{
				image[i][j] = 255;
			}
		}
	}

	// Scanning the image for characters

	for (int i=0; i < SIZE; i++){
		for (int j=0; j < SIZE; j++){
			if (image[i][j] == 0 && explored[i][j] != 1){
				Character newChar = find_bounding_box(i,j);
				charVec.push_back(newChar);
			}

		}
	}

	// Run classification tests on each character object
	int size = charVec.size();

	// debug flag is turned off
	if (debug == 0){
		for (int i=0;  i < size; i ++ ){
			charVec[i].perform_tests();
			cout << charVec[i].get_classification() << " ";
		}
		cout << endl;
	}
	else if ( debug == 1){
		for (int i=0;  i < size; i ++ ){
			charVec[i].perform_tests();
			charVec[i].print_calculations();
			cout << "Character " << i+1 << " is classified as: " << charVec[i].get_classification() << endl;
			cout << endl;
		}

	}
	



  return 0;
}

Character find_bounding_box(int row,int col){
	int ulr = row;
	int ulc = col;
	int rowUpdate = 0;
	int colUpdate = 0;
	deque<Point> pixel_deq;
	Point start = Point(row,col);
	pixel_deq.push_back(start);
	Point curr,loc;
	while (!pixel_deq.empty()){
		curr = pixel_deq[0];
		pixel_deq.pop_front();
		// North
		if (curr.r - 1 >= 0){
			loc.r = curr.r - 1;
			loc.c = curr.c;
			if (image[loc.r][loc.c] == 0 && explored[loc.r][loc.c] != 1){
				pixel_deq.push_back(loc);
				if (loc.r < ulr){
					ulr--;
					rowUpdate++;
				}
			}
			explored[loc.r][loc.c] = 1;
		}
		// NorthWest
		if (curr.r - 1 >= 0 && curr.c - 1 >= 0){
			loc.r = curr.r - 1;
			loc.c = curr.c - 1;
			if (image[loc.r][loc.c] == 0 && explored[loc.r][loc.c] != 1){
				pixel_deq.push_back(loc);
				if (loc.c < ulc){
					ulc--;
					colUpdate++;
				}
				if (loc.r < ulr){
					ulr--;
					rowUpdate++;
				}
			}
			explored[loc.r][loc.c] = 1;
		}
		// West
		if (curr.c - 1 >= 0){
			loc.r = curr.r;
			loc.c = curr.c - 1;
			if (image[loc.r][loc.c] == 0 && explored[loc.r][loc.c] != 1){
				pixel_deq.push_back(loc);
				if (loc.c < ulc){
					ulc--;
					colUpdate++;
				}
			}
			explored[loc.r][loc.c] = 1;
		}
		// SouthWest
		if (curr.r + 1 <= SIZE && curr.c - 1 >= 0){
			loc.r = curr.r + 1;
			loc.c = curr.c - 1;
			if (image[loc.r][loc.c] == 0 && explored[loc.r][loc.c] != 1){
				pixel_deq.push_back(loc);
				if (loc.r > ulr + rowUpdate){
					rowUpdate++;
				}
				if (loc.c < ulc){
					ulc--;
					colUpdate++;
				}
			}
			explored[loc.r][loc.c] = 1;
		}
		// South
		if (curr.r + 1 <= SIZE){
			loc.r = curr.r + 1;;
			loc.c = curr.c;
			if (image[loc.r][loc.c] == 0 && explored[loc.r][loc.c] != 1){
				pixel_deq.push_back(loc);
				if (loc.r > ulr + rowUpdate){
					rowUpdate++;
				}
			}
			explored[loc.r][loc.c] = 1;
		}	
		// SouthEast
		if (curr.r + 1 <= SIZE && curr.c <= SIZE){
			loc.r = curr.r +1;
			loc.c = curr.c + 1;
			if (image[loc.r][loc.c] == 0 && explored[loc.r][loc.c] != 1){
				pixel_deq.push_back(loc);
				if (loc.c > ulc + colUpdate){
					colUpdate++;
				}
				if (loc.r > ulr + rowUpdate){
					rowUpdate++;
				}
			}
			explored[loc.r][loc.c] = 1;
		}
		// East
		if (curr.c + 1 <= SIZE){
			loc.r = curr.r;
			loc.c = curr.c + 1;
			if (image[loc.r][loc.c] == 0 && explored[loc.r][loc.c] != 1){
				pixel_deq.push_back(loc);
				if (loc.c > ulc + colUpdate){
					colUpdate++;
				}
			}
			explored[loc.r][loc.c] = 1;
		}
		// NorthEast
		if (curr.c + 1 <= SIZE && curr.r - 1 >= 0 ){
			loc.r = curr.r -1;
			loc.c = curr.c + 1;
			if (image[loc.r][loc.c] == 0 && explored[loc.r][loc.c] != 1){
				pixel_deq.push_back(loc);
				if (loc.c > ulc+colUpdate){
					colUpdate++;
				}
			}
			explored[loc.r][loc.c] = 1;
		}

	}
	int h = rowUpdate;
	int w = colUpdate;
	Character retChar(image,ulr,ulc,h,w);
	return retChar;

}

