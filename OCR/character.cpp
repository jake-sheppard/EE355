# include "character.h"
# include <iostream>

using namespace std;

Character::Character(){
	ul_r = 0;
	ul_c = 0;
	height = 0;
	width = 0;
}
Character::Character(unsigned char (*myimage)[256], int ulr, int ulc, int h, int w ){
	image = myimage;
	ul_r = ulr;
	ul_c = ulc;
	height = h;
	width = w;
	area = 0;
	perimeter = 0;


}
Character::~Character(){

}
void Character::perform_tests(){
	calc_bit_quads();
	calc_area();
	calc_perimeter();
	calc_euler_number();
	calc_spatial_moment();
	calc_sym();
	calc_aspect_ratio();
	classify();
}
void Character::classify(){   
	if (eulerNum == -1){
		recognized_char = '8';
	}
	else if (eulerNum == 0){
		if (vertSym > 0.86){
			recognized_char = '0';
		}
		else if (shftdVertCentroid > 0){
			recognized_char = '6';
		}
		else if (vertSym > horSym){
			recognized_char = '4';
		}
		else{
			recognized_char = '9';
		}

	}
	else if (eulerNum == 1){
		if (aspRatio > 1.7){
			recognized_char = '1';
		}
		else if (shftdHorCentroid > 2){
			recognized_char = '3';
		}
		else if (shftdVertCentroid < -4){
			recognized_char = '7';
		}
		else if (horSym > .84 || shftdHorCentroid < 0){
			recognized_char = '5';
		}
		else {
			recognized_char = '2';
		}
	}
}
char Character::get_classification(){
	return recognized_char;
}
void Character::get_bounding_box(int &ulr, int &ulc, int &lrr, int &lrc){
	ulr = ul_r;
	ulc = ul_c;
	lrr = ul_r + height;
	lrc = ul_c + width;
}
void Character::print_calculations(){ 
	cout << "Character in bounding box: " << ul_r << "," << ul_c << " to " << ul_r + height << "," << ul_c + width << endl;
	cout << "===============================" << endl;
	cout << "BQ0 = " << q_0 << " BQ1 = " << q_1 << " BQ2 = " << q_2 << " BQ3 = " << q_3 << " BQ4 = " << q_4 << " BQD = " << q_d << endl;
	cout << "Euler Number = " << eulerNum << endl;
	cout << "VCentroid = "<< vertCentroid << " / "<< "HCentroid = " << horCentroid << endl;
	cout << "Shifted VCentroid = " << shftdVertCentroid << " / " << "Shifted HCentroid = " << shftdHorCentroid << endl;
	cout << "VSym = " << vertSym << " / " << "HSym = " << horSym << endl;
	cout << "Aspect Ratio = " << aspRatio << endl;
}
void Character::calc_bit_quads(){  
	q_0 = 0;
	q_1 = 0;
	q_2 = 0;   
	q_3 = 0;
	q_4 = 0;
	q_d = 0;
	// start one row & col above & to left
	int ulr = ul_r - 1;
	int ulc = ul_c - 1;
	// continue to one row & col below & to right
	int lrr = ul_r + height + 1;
	int lrc = ul_c + width + 1;
	for (int i = ulr; i < lrr; i++){
		for (int j = ulc; j < lrc; j++){
			int count = 0;
			if (image[i][j] == 0){
				count++;
			}
			if (image[i][j+1] == 0){
				count++;
			}
			if (image[i+1][j+1] == 0){
				count++;
			}
			if (image[i+1][j] == 0){
				count++;
			}


			if (count == 0){
				q_0++;
			}
			else if (count == 1){
				q_1++;
			}
			// diagonal check #1
			else if (count == 2 && (image[i][j] == 0 && image[i+1][j+1] == 0)){
				q_d++;
			}
			// diagonal check #2
			else if (count == 2 && (image[i][j+1] == 0 && image[i+1][j] == 0)){
				q_d++;
			}
			// 2 black pixels, but not diagonal
			else if (count == 2){
				q_2++;
			}
			else if (count == 3){
				q_3++;
			}
			else if (count == 4){
				q_4++;
			}
			
		}
	}
	
}
void Character::calc_area(){
	area =  (q_1 + 2*q_2 + 2*q_d + 3*q_3 + 4*q_4)/4;
}
void Character::calc_perimeter(){
	perimeter =  q_1 + q_2 + 2*q_d;
}
void Character::calc_euler_number(){
	eulerNum =  (q_1 - q_3 - 2*q_d)/4;
}
void Character::calc_spatial_moment(){
	int totalBlack = 0;
	int vertSum = 0;
	int horSum = 0;
	int lrr = ul_r + height;
	int lrc = ul_c + width;

	// Vertical Sum & Total Black Pixels
	for (int i = ul_r; i < lrr; i++){
		for (int j = ul_c; j < lrc; j++){
			if (image[i][j] == 0){
				vertSum += i*1;
				totalBlack++;
			}
		}
	}

	// Horizontal Sum
	for (int j = ul_c; j < lrc; j++){
		for (int i = ul_r; i < lrr; i++){
			if (image[i][j] == 0){
				horSum += j*1;
			}
		}
	}

	// Vertical Centroid
	vertCentroid = ((double)vertSum / totalBlack) - ul_r;
	// Horizontal Centroid
	horCentroid = ((double)horSum / totalBlack) - ul_c;
	// Shifted Vertical Centroid
	shftdVertCentroid =  vertCentroid - ((double)height/2);
	// Shift Horizontal Centroid
	shftdHorCentroid =  horCentroid - ((double)width/2);
}

void Character::calc_sym(){
	int lrr = ul_r + height;
	int lrc = ul_c + width;

	int vertCompare = 0;
	int vertCount = 0;
	int vertMid = (ul_r + lrr)/2;
	int horCompare = 0;
	int horCount = 0;
	int horMid = (ul_c + lrc)/2;
	


	// Vertical Symmetry
	for (int i = 0; i < vertMid; i++){
		for (int j = ul_c; j < lrc; j++){
			if (image[i+ul_r][j] == image[lrr-i][j]){
				vertCount++;
			}
			vertCompare++;
		}
	}
	/*if (vertCompare == 0){
		vertSym = 0;
	}*/
	//else{
		vertSym = (double)vertCount/vertCompare;
	//}

	// Horizontal Symmetry
	for (int j = 0; j < horMid; j++){
		for (int i = ul_r; i < lrr; i++){
			if (image[i][j+ul_c] == image[i][lrc-j]){
				horCount++;
			}
			horCompare++;
		}
	}
	/*if (horCompare == 0){
		horSym = 0;
	}*/
	//else{
		horSym = (double)horCount/horCompare;
	//}
	

}

void Character::calc_aspect_ratio(){
	aspRatio = (double)height/width;
}
