#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<string>
using std::string;
#include<cctype>
using std::isdigit; using std::isalpha;

/* Hexadecimal number classifier. Finds hexadecimal
prefix 0x. After position is found, function
iterates through each character after said
position to find characters that are only 
classified as hex. Using isxdigit function. */
bool valid_hex(string hex){

    int find_neg = hex.find("-");
    int find_hex = hex.find("0x");    
    if (find_neg == string::npos && find_hex == 0){
        string new_substr = hex.substr(2);
        for(int i=0; i < new_substr.length(); i++){
            if(!isxdigit(new_substr[i])){
                return false;
            }
        }
        return true;
    }
    else if (find_neg == 0 && find_hex == 1) {
        string new_substr = hex.substr(3);
        for(int i=0; i < new_substr.length(); i++){
            if(!isxdigit(new_substr[i])){
                return false;
            }
        }
        return true;
    }
    else {
        return false;
    }
}
/* Octal number classifier. Finds octal prefix 0.
After position is found, function iterates
through each character after said position
to find characters ONLY between numbers
0 and 7. */
 bool valid_octal(string oct){

    int find_neg = oct.find("-");
    int find_oct = oct.find("0");
    if (find_neg == string::npos && find_oct == 0){
        string new_substr = oct.substr(1);
        for(int i=0; i < new_substr.length(); i++){
            if (new_substr[i] < '0' || new_substr[i] > '7'){
                return false;
            }
        }
        return true;
    }
    else if (find_neg == 0 && find_oct == 1){
        string new_substr = oct.substr(2);
        for(int i=0; i < new_substr.length(); i++){
            if (new_substr[i] < '0' || new_substr[i] > '7'){
                return false;
            }
        }
        return true;
    }
    else {
        return false;
    }
}
/* Binary number classifier. Finds binary prefix
0b. After position is found, function
iterates through each character after said
position to find characters ONLY between
numbers 0 and 1 */
bool valid_binary(string bin){

    int find_neg = bin.find("-");
    int find_bin = bin.find("0b");
    if (find_neg == string::npos && find_bin == 0){
        string new_substr = bin.substr(2);
        for(int i=0; i < new_substr.length(); i++){
            if (new_substr[i] == '0' && new_substr[i] <= '1'){
                return true;
            }
        }
        return false;
    }
    else if (find_neg == 0 && find_bin == 1){
        string new_substr = bin.substr(3);
        for(int i=0; i < new_substr.length(); i++){
            if(new_substr[i] == '0' && new_substr[i] <= '1'){
                return true;
            }
        }
        return false;
    }
    else {
        return false;
    }
}
/* Decimal number integer classifier. Finds any
order of integers without decimal point. Function
iterates through each character and uses
isdigit function to classify characters
that are ONLY digits. */
bool valid_int(string intgr){
    int find_neg = intgr.find("-");
    int find_intgr = intgr.find(intgr);

    if(find_neg == string::npos && find_intgr == 0){
        string new_substr = intgr.substr(1);
        for (int i = 0; i < new_substr.length(); i++){
            if( !isdigit(new_substr[i])){
                return false;
            }
        }
        return true;
    }
    else if (find_neg == 0){
        string new_substr = intgr.substr(2);
        for (int i=0; i <new_substr.length(); i++){
            if(!isdigit(new_substr[i])){
                return false;
            }
        }
        return true;
    }
    else {
        return false;
    }

}
/* Decimal number float classifier. Does 
two classifications: decimal point or scientific
notation classification. Function finds decimal
point or character 'e' for scientific notation. 
Determines whether characters before and after said
 positions are ONLY digits. */
bool valid_float(string flt){

    int find_neg = flt.find("-");
    int find_e = flt.find("e");
    int find_decimal = flt.find(".");
    if (find_neg == string::npos){
        for (int i = 0; i < find_decimal; i++){
            if (!isdigit(flt[i])){
                if(find_decimal != string::npos){
                    return false;
                }
            }
            else {
                string new_substr = flt.substr(find_decimal + 1);
                for(int i = 0; i < new_substr.length(); i++){
                    if(!isdigit(new_substr[i])){
                        return false;
                    }
                }
                return true;
            }
        }
        for (int i = 0 ; i < find_e; i++){

            if(!isdigit(flt[i])){
                return false;
            }
        if (find_e != string::npos){
            string new_substr = flt.substr(find_e + 1);

            int second_neg = new_substr.find_last_of("-");
            if (second_neg != string::npos){ //if second negative is found
                string another_substr = new_substr.substr(second_neg + 1);
                for (int i = 0; i < another_substr.length(); i++){
                    if(!isdigit(another_substr[i])){
                        return false;
                    }
                }
                return true;
            } 
            else { //if second negative is not found
                for (int i = 0; i < new_substr.length(); i++){
                    if(!isdigit(new_substr[i])){
                        return false;
                    }
                }
                return true;
            }             
        }
    }
} 
    else if (find_neg == 0){

        for (int i = 1; i < find_decimal; i++){
            if(!isdigit(flt[i])){
                return false;
            }
        }
        if (find_decimal != string::npos) {

            string new_substr = flt.substr(find_decimal +1);
            for(int i = 0; i < new_substr.length(); i++){
                if(!isdigit(new_substr[i])){
                    return false;
                }
            }
            return true;
        }
        for(int i = 1; i < find_e; i++){
            if(!isdigit(flt[i])){
                return false;
            }
        }
        if (find_e != string::npos){ 
            string new_substr = flt.substr(find_e + 1);
            int second_neg = new_substr.find_last_of("-");
            for(int i = 0; i < new_substr.length(); i++){
                if (second_neg != string::npos){ //if second negative is found
                    string another_substr = new_substr.substr(second_neg + 1);
                    for (int i = 0; i < another_substr.length(); i++){
                        if(!isdigit(another_substr[i])){
                            return false;
                        }
                    }
                    return true;
                }
                else { //if the second negative cannot be found
                    for (int i = 0; i < new_substr.length(); i++){
                        if(!isdigit(new_substr[i])){
                            return false;
                        }
                    }
                    return true;
                } 

            }
        }
    }
    else {
        return false;
    }
    
    return false;
}
/* Calls all above functions to classify
the correct string input. If input is not
correct string input for any of the following
functions- returns false as an invalid classification. */
string classify_string(string clas){

    if (valid_hex (clas) == true){
        return "hexadecimal";
    }
    else if (valid_octal (clas) == true) {
        return "octal";
    }

    else if (valid_binary (clas) == true){
        return "binary";
    }

    else if(valid_float (clas) == true) {
        return "float";
    }
    else {
        return "false";
    }
    
} 

int main (){

  cout << boolalpha;
  int testnum;
  cin >> testnum;

  switch (testnum) {
  case 1 : {
    string to_test;
    cin >> to_test;
    cout << valid_hex(to_test) << endl;
    break;
  }
  
  case 2:{
    string to_test;
    cin >> to_test;
    cout << valid_octal(to_test) << endl;
    break;
  }

  case 3:{
    string to_test;
    cin >> to_test;
    cout << valid_binary(to_test) << endl;
    break;
  }

  case 4:{
    string to_test;
    cin >> to_test;
    cout << valid_float(to_test) << endl;
    break;
  }

  case 5:{
    string to_test;
    cin >> to_test;
    cout << valid_int(to_test) << endl;
    break;
  }

  case 6:{
    string to_test;
    cin >> to_test;
    cout << classify_string(to_test) << endl;
    break;
  }

  }// of switch 
}// of main