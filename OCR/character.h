#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
 public:
  Character();
  // the first parameter should just be passed in and saved to 
  //  the 'image' data member as in ( image = myimage; )
  Character(unsigned char (*myimage)[256], int ulr, int ulc, int h, int w );
  ~Character();


  void perform_tests();
  void classify();
  char get_classification();
  // returns upper-left point and lower-right point of bounding box
  //  DOES NOT compute bounding box...it's already in your data members
  //  just returns the bounding box if a user wants the bounds
  void get_bounding_box(int &ulr, int &ulc, int &lrr, int &lrc);
  void print_calculations();

 private:
  //==============
  // Helper Functions
  //==============

  void calc_bit_quads();
  void calc_area();
  void calc_perimeter();
  void calc_euler_number();
  void calc_spatial_moment(); // calcs the horizontal & vertical centroids
  void calc_sym();            // calcs horizontal and vertical symmetry
  void calc_aspect_ratio();

  //==============
  // Data Members
  //==============
 private: 
  int ul_r, ul_c;
  int height, width, area, perimeter;
  int q_0, q_1, q_2, q_3, q_4, q_d;
  int eulerNum;
  double vertCentroid, horCentroid;
  double shftdVertCentroid, shftdHorCentroid;
  double vertSym, horSym;
  double aspRatio;
  
  // feel free to add functions here.
  
  char recognized_char;
  unsigned char (*image)[256];


};

#endif

