#include <iostream>
using std:: endl; using std:: cout;
#include <ostream>
using std::ostream;
#include<sstream>
using std::ostringstream;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include "proj06_functions.h" 
 
int main() {
 

    vector<long> v {11,12,13,14,15,21,22,23,24,25,31,32,33,34,35,41,42,43,44,45};
    long rows = 4;
    long cols = 5;

    //long ans = 112;
    //vector<long> result = column_order(v,rows,cols);

    // vector<long> v {11,12,13,14,15,21,22,23,24,25,31,32,33,34,35,41,42,43,44,45};
    // long rows = 4;
    // long cols = 5;

    //vector<long> ans = {15,25,35,45,14,24,34,44,13,23,33,43,12,22,32,42,11,21,31,41};
    // vector<long> result = matrix_ccw_rotate(v,rows,cols);
    // x = ostream print_vector(v, result);
    //return result;
    long result = trapped_vals(v,rows,cols);
    //cout << max_column_diff (v,rows,cols) << endl;
    cout << result << endl;
} 