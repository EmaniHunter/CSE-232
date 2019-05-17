/* Sect. 06; 03/11/19; proj06 */

#include <iostream>
using std::endl; using std::cout;
#include <ostream>
using std::ostream;
#include<sstream>
using std::ostringstream;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<cstdlib>
#include "proj06_functions.h"

/* Prints input vector into given ostream, separates
each element with a comma */
ostream& print_vector(const vector<long>& v, ostream& out){
    ostringstream vect_str;
    for (int i = 0; i < v.size(); ++i){ //iterate through input vector
        vect_str << v[i] << ","; //comma separated elements
    }
    string vect = vect_str.str(); //turns comma separated elements into string
    string  print_vec = vect.substr(0, vect.length()-1); //create substring include first element to the last element (disregarding last comma)
    out << print_vec;
    return out;

}
/* Returns the sum of each of the four
corners in a 2D matrix visualized as
a 1D vector */
long four_corner_sum(const vector<long>& v, int rows, int cols){
    int top_left = 0;
    int top_right = 0;
    int bot_left = 0;
    int bot_right = 0;
    int total_sum = 0;

    if (rows < 2 || cols < 2){ // number of rows/columns must not be less than 2
        return 0;
    }
    //Find each corner
    top_left = v[0];
  
    bot_right = v[v.size()-1];

    bot_left = v[(rows - 1) * cols + 0];
   
    top_right = v[0 * cols + (cols - 1)];
   
    total_sum = top_left + top_right + bot_left + bot_right; //sum of all corners
    return total_sum;

}
/* Reorders input vector in respect to the columns
instead of the rows, creates new vector with
this characteristic */
 vector<long> column_order(const vector<long>& v, int rows, int cols){
    vector<long> new_vect;

    for (int i = 0; i < cols; i++){
        for (int j = i; j < v.size(); j += cols){ 
            new_vect.push_back(v[j]);
        }
    }
    return new_vect;
}
/* Shifts/Rotates each row up 1, creates new 
vector with this characteristic */
vector<long> rotate_rows_up(const vector<long>& v, int rows, int cols){
    vector<long> new_vect = v;

    if (rows < 2){ //if number of rows is less than two must give an empty vector
        return {};
    }

    std::rotate(new_vect.begin(), new_vect.begin() + (cols), new_vect.end());
    return new_vect;
}
/* Rotates 2D matrix inputted as a 1D vector , 90 
degrees counter-clockwise, creates new vector with
this characteristic */
vector<long> matrix_ccw_rotate(const vector<long>& v, int rows, int cols){
    vector<long> new_vect;

    for (int j = cols - 1; j >= 0 ; j--){ 
        for (int i = 0; i < rows; i++){ 
            int new_index = ( i * cols ) + j; //creates index to iterate through each element in vector
            new_vect.push_back(v[new_index]);

        }
    }
    return new_vect;
 
}
/* Takes sum of each column, compares each
column's sum to every other column's sum, finds the
maximum difference of column sums, returns max difference  */
long max_column_diff(const vector<long>& v, int rows, int cols){
    int sum_index = 0;
    int max_num = 0;
    int sum_difference = 0;
    vector<long> col_sums;

    for (int i = 0; i < cols; i++){
        int sums = 0;
        for (int j = i; j < v.size(); j+=cols){ //Add up columns
            sums += v[j];
        }
        col_sums.push_back(sums); //Gives each column sum for each corresponding column
    }

    for (int sum_of_cols = 0; sum_of_cols < col_sums.size(); sum_of_cols++){ //iterate through col_sums vector  
        for (sum_index = sum_of_cols + 1; sum_index < cols; sum_index++){
            sum_difference = abs(col_sums[sum_index] - col_sums[sum_of_cols]); //max diff
            if (sum_difference > max_num){
                max_num = sum_difference; //turns previously assigned max_num from zero to the maximum sum difference

            }
        }       
    } 
    return max_num;

}
/* Checks the 4 neighbors of each individual matrix
element. Each neighbor = up ,down, left, right,
checks if each neighbor is greater than the particular element
that is surrounded, if so, counts the element
as trapped value */
long trapped_vals (const vector<long>& v, int rows, int cols){
    int trapped_val = 0;

    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            int up = 0;
            int left = 0;
            int down = 0;
            int right = 0;
            int index = ( i * cols ) + j;
          
            if (i - 1 < 0){ //in bounds check for upward neighbor
                up = ((i + (rows - 1)) * cols) + j; //grab upwards neighbor
  
            }
     
            if (j - 1 < 0){ //in bounds check for leftwards neighbor
                left = i + (cols - 1) + j; //grab leftwards neighbor

            }
     
            if (i + 1 < rows - 1){ //in bounds check for downwards neighbor
                down = (i + (rows + 1)+ j); //grab downwards neighbor
        
            }
           
            if (j + 1 > cols - 1){ //in bounds check for rightwards neighbor
                right = (i + (cols + 1) + j); //grabs rightwards neighbor

            }
            right = (i + (cols + 1) + j);
           //Finds number of trapped values that satisfy,
           //each neighbor being greater than pointer number
            if (v.at(up) > v.at(index)){
                if (v.at(down) > v.at(index)){
                    if (v.at(left) > v.at(index)){
                        if (v.at(right) > v.at(index)){
                            trapped_val++;
                        }
                    }
                }
            }

        }
    }
    return trapped_val;

} 









