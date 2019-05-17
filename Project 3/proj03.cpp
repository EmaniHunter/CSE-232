#include<iostream>
using std::cout; using std::cin; using std::endl;
using std::boolalpha;
#include<cmath>

bool is_prime (long n){ //Prime number function
/* Iterates through 2 to n-1
All numbers that divides into n without a remainder = not prime, false 
true otherwise */
    for (long num = 2; num * num <= n; num++){ 
        if (n % num == 0) { 
            return false; 
        }
    }
    return true; 
}

bool is_powerful (long n){ //Powerful number function
/* Iterate through 2 to (n-1) / considerably high limit
Find factors of number that divides n without remainder
Factors that are prime, divides n without remainder = powerful */
    long power_of_num = 0;
    for (long num = 2; num * num <= 999999999999; num++){ 
        power_of_num = pow(num,2);
        if (n % num == 0){ 
            if (is_prime(num) == true){ 
                if (n % power_of_num == 0){ 
                    return true; 
                }
            }
        }
        if (is_prime(num) == true){ 
            return false;
        }
    }
}

bool is_perfect_power (long n){ //Perfect power function
/* Iterate through powers 2 to high limit 
find all roots of powers, integer root = input 'n'
number is perfect power */
    double i = 2, root_power_num = 0;
    for (i; i <= sqrt(n); i++){
        root_power_num = pow(n, 1/i);
        root_power_num = round(root_power_num);
        if (pow(root_power_num, i) == n){
            return true;
        }

    }
}

bool is_achilles (long n){ //Achilles number function
/* Reigns true if and only if number is powerful
and is not a perfect power. 
*Achilles* */
    if (is_powerful(n) == true){
        if (is_perfect_power(n) == false){
            return true;
        }
    }
    return false;
}



// main is below. You cannot modify main
int main (){
  cout << boolalpha;

  int test_case;
  cin >> test_case;

  switch (test_case){

    
  case 1 : {
    long num;
    cin >> num;
    cout <<  is_prime(num) << endl;
    break;
  } // of case 1

  case 2 : {
    long num;
    cin >> num;
    cout << is_powerful(num) << endl;
    break;
  } // of case 2

  case 3 : {
    long num;
    cin >> num;
    cout << is_perfect_power(num) << endl;
    break;
  } // of case 3   

  case 4 : {
    long num;
    cin >> num;
    cout << is_achilles(num) << endl;
    break;
  } // of case 4
    
  } // of switch
} // of main