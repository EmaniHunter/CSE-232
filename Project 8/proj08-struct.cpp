/* proj08; Sect. 06; 3/25/2019 */

#include<fstream>
using std::ifstream;
#include<sstream>
using std::istringstream;
#include<iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
#include<algorithm>
using std::copy;
#include<iterator>
#include "proj08-struct.h"

/* Constructor, takes in pgm file for input,
 grabs max_val, height and width and pixel data members for
 corresponding image*/
Image::Image(string f_name) {

    ifstream inFile(f_name);
    string line;
    istringstream iss;

    getline(inFile, line); //skip magic number of file
 
    do{
   
        getline(inFile, line);

    }while (line.front() == '#'); //skip any comments in file
    
    iss.str(line);
    iss >> width_ >> height_; //grab width and height

    getline(inFile,line);
    iss.str(line);
    iss.seekg(0);
    iss >> max_val_ ; //find max_val

    for (auto i = 0; i < height_ ; i++){ //rows
        vector<long> row_vec ;
        getline(inFile, line);
        istringstream new_iss(line);
        
        for (auto j = 0; j < width_ ; j++){
           
            if (line.empty()){
                continue;
            }
            
            long num;
            new_iss >> num; //new stream created to grab each pixel in each line of file
            row_vec.push_back(num);
   
        }
        pixels_.push_back(row_vec);
    }

}
/* Method, writes out a pgm file for image */
void Image::write_image(string f_name) const{
    ofstream ofs (f_name);

    ofs << "P2" << endl; //grabs magic number of given file displays "P2"
    ofs << width_ << " " << height_ << endl; //grabs width and height of given file, displays with space
    ofs << max_val_ << endl; //grabs max_val,

    for (auto row:pixels_){ //iterate through each row of the pixel 2d vector
        std::copy(row.begin(), row.end(), std::ostream_iterator<long> (ofs, " ")); //creates copy of rows and displays plixels with space in between
        ofs << endl;
    }

}
/* Method, creates new image with given convolution mask
and divisor/ whiten parameters, sets pixels in new_image to old
pixels in old image */
Image Image::convolve(vector<vector<long>> mask, long div, long whiten) const{
    Image new_image(*this); //copy, create new_image
    new_image.pixels_ = pixels_;

    for (int row = 0; row < height_; row++){
        for (int col = 0; col < width_; col++){
             long sum = 0;

            sum += pixels_[row][col] * mask[1][1]; //middle of mask summation

            if (row - 1 >= 0 ){ //top left corner/edge bound checks
  
                if (col - 1 >= 0 ){
                    sum += (pixels_[row -1][col -1] * mask[0][0]); //adds corresponding top left corner pixel times corresponding mask to summation
                }
            }
            if (row - 1 >= 0){ //top middle bound check
                sum += (pixels_[row - 1][col] * mask[0][1]);
            }
     
            if (row - 1 >= 0){ //top right corner checks
  
                if (col + 1 <= width_ - 1){
                    sum += (pixels_[row-1][col + 1] * mask[0][2]);
                }
            }

            if (row + 1 <= height_ - 1){ //bottom left corner/edge checks
                if (col - 1 >= 0){
                    sum += (pixels_[row + 1][col - 1] * mask[2][0]);
                }
            }
  
            if (row + 1 <= height_ - 1){ //bottom middle bound check
                sum += (pixels_[row + 1][col] * mask[2][1]);
            }

            if (row + 1 <= height_ - 1 ){//bottom right corner/edge checks
            
                if (col + 1 <= width_-1){
                    sum += (pixels_[row + 1][col + 1] * mask[2][2]);
                }
            }
 
            if (col + 1 <= width_ - 1 ){ //far right middle bound check
                sum += (pixels_[row][col + 1] * mask [1][2]);
            }
      
            if (col - 1 >= 0){ //far left middle bound check
                sum += (pixels_[row][col - 1] * mask[1][0]);
        
            }

            sum = (sum/div); //divide accumlated sum by divisor
            sum = sum + whiten; //add whiten to whiten image
            sum = static_cast<int>(sum);
            
            if (sum > max_val_){ //if sum is bigger than max val set the sum to the max val
                sum = max_val_;
            }
            
            if (sum < 0){ //if sum is negative, must be set to zero
                sum = 0;
            }

            new_image.pixels_[row][col] = sum;
        }
    }
    return new_image;
}
/* Methods calling convolve*/
Image Image::sharpen() const{
    return convolve({{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}, 1 ,0);
}
/* Methods calling convolve*/
Image Image::edge_detect() const{
    return convolve({{0, 1, 0}, {1, -4, 1}, {0, 1, 0}}, 1 , 50);
}
/* Methods calling convolve*/
Image Image::blur() const{
    return convolve ({{1,1,1}, {1,1,1},{1,1,1}}, 9, 0);
}
/* Methods calling convolve*/
Image Image::emboss() const{
    return convolve({{-2, -1, 0}, {-1, 1, 1}, {0 , 1, 2}}, 1, 0);
}
/*Embeds secret image inside of original/ plain image */
void Image::embed(const Image &secret){

    for (int i = 0; i < secret.height_ ; i++){
        for ( int j = 0; j < secret.width_; j++){
            
            if (secret.pixels_[i][j] == 0){ //check if pixel in secret image is zero
                if (pixels_[i][j] % 2 == 1){ //find if plain pixel is odd subtract one to turn it even
                    pixels_[i][j] = pixels_[i][j] - 1;
                }
            }
            else { //non zero numbers in secret image pixels
                if (pixels_[i][j] % 2 == 0){ //if even
                    pixels_[i][j] = pixels_[i][j] + 1; //set to odd
                }
                
                if (pixels_[i][j] == max_val_){ //if plain pixel already at max value, check if even, set to odd if even
                    if (pixels_[i][j] % 2 == 0){
                        pixels_[i][j] = pixels_[i][j] - 1;
                    }
                }
            }
        }
    }
}
/* Creates new image with extracted pixel
values, extracted values ranging from zero or
given max val input */
Image Image::extract(long max_val) const{
    Image new_image(*this); //copy, creates new_image pointing to the old_image & its data members
    new_image.pixels_ = pixels_;
    new_image.max_val_ = max_val; //set data member max value to given max val
    
    for (int i = 0; i < height_; i++){
        for (int j = 0; j < width_; j++){
            
            if (pixels_[i][j] % 2 == 1){ //if corresponding pixel is odd, set pixel to the max val
                new_image.pixels_[i][j] = max_val;
            }
            
            else{ //if corresponding pixel is even, set pixel to zero
                new_image.pixels_[i][j] = 0;
            }
        }

    }
    return new_image;
}
