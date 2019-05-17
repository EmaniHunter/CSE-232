#include <iostream>
using std::cout; using std::cin; using std::endl; using std::fixed;

#include<cmath>

int main () {
    long low_val, high_val, seq_val, new_seq = 0, max_seq_length = 0, largest_num = 0, starting_num2 = 0, starting_num1 = 0, longest_seq = 0;
    cin >> low_val >> high_val;

    //If input high value is smaller than low value, error is outputted
    if (high_val < low_val) {
            cout << "Error" << endl;
            return 0;
        }
    for (seq_val = low_val; seq_val <= high_val; ++seq_val) {
        new_seq = seq_val; 

        //Begin Juggler Sequence
        while (new_seq > 1) {
        
            if (new_seq % 2 == 0){ //account for even numbers for juggler
                new_seq = pow(new_seq, 0.5);
                new_seq = floor(new_seq);
            }  
            else { //account for all numbers not even for juggler
                new_seq = pow(new_seq, 1.5);
                new_seq= floor(new_seq);
            }
            
            if (largest_num < new_seq) {
                largest_num = new_seq; //Gives largest number in sequence
                starting_num2 = seq_val; //Finds starting value of sequence
            } 

        max_seq_length = max_seq_length + 1; //Iterates through to find sequence of longest length
        if (longest_seq < max_seq_length) {
            longest_seq = max_seq_length; // Re-define iteration 
            starting_num1 = seq_val;    //Finds starting value of sequence
        } 
        
        
        }
        max_seq_length = 0; //Re-initializes longest sequence length to zero

    }
    //output longest sequence and largest number in sequence
    cout << starting_num1 << " " << longest_seq << endl;
    cout << starting_num2 << " " << largest_num << endl;
 
}
    