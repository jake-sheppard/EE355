#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int main(int argc, char* argv[]){

	ifstream ifile(argv[1]);
	if (ifile.fail()){
		cout << "file not read in" <<endl;
		return 1;
	}
	int num;
	ifile >> num;
	vector<char> vec;
	while (!ifile.EOF){
		ifile >> vec[i];
	}
	for (int i = num-1; i >= 0; i--){
		cout << vec[i] << " ";
	}

	return 0;
}