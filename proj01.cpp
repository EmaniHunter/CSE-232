//This program takes in 4 doubles (floating point) values (to two decimal points) 
//to be considered for the manipulation of two real numbers and two imaginary numbers. Complex number addition,subtraction, 
//multiplication and division are taken into account. All outputs are in the standard
// a + bi form

#include <iostream>
using std::cout; using std::cin; using std::endl; using std::fixed;

#include<iomanip>
using std::setprecision;

int main() {
    double real_num1, imaginary1, real_num2, imaginary2;
    double complex1_sum, complex2_sum,complex1_difference,complex2_difference,complex1_product,complex2_product, complex1_quotient,complex2_quotient;
    //cout << setprecision(2) << fixed << endl;
    cin >> real_num1 >> imaginary1 >> real_num2 >> imaginary2;
    cout << setprecision(2) << fixed << endl;
    //Complex Addition
    complex1_sum = real_num1 + real_num2;
    complex2_sum = imaginary1 + imaginary2;
    cout << complex1_sum << " + "<< complex2_sum <<"i" << endl;
    //Complex Difference
    complex1_difference = real_num1 - real_num2;
    complex2_difference = imaginary1 - imaginary2;
    cout << complex1_difference << " + " << complex2_difference << "i" << endl;
    //Complex Product
    complex1_product = (real_num1 * real_num2) - (imaginary1 * imaginary2);
    complex2_product = (real_num1 * imaginary2) + (real_num2 * imaginary1);
    cout << complex1_product << " + " << complex2_product << "i" << endl;
    //Complex Quotient
    complex1_quotient = ((real_num1 * real_num2) + (imaginary1 * imaginary2)) / ((real_num2 * real_num2) + (imaginary2 * imaginary2));
    complex2_quotient = ((imaginary1 * real_num2) - (real_num1* imaginary2)) / (((real_num2 * real_num2)*(real_num2 * real_num2)) + ((imaginary2 * imaginary2) * (imaginary2 * imaginary2)));
    cout << complex1_quotient << " + " <<complex2_quotient << "i" << endl;
}

