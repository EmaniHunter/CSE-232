/* Sect. 06; 02-25-2019; proj05 */
#include<iostream>
using std::boolalpha; using std::cout; using std::endl; using std::cin;
#include<string>
using std::string;
#include<cmath>
#include<istream>
//#include<algorithm>

/* Take input string and turn all alphabetic chars to 
lowercase */
string lower_case(const string& s){
    string lowercase_str = "" ;
    for(unsigned int i = 0; i < s.length(); i++){
        if(isalpha(s[i])){ //if char elements in string are alphabetic
            lowercase_str = lowercase_str + static_cast<char>(tolower(s[i])); //turns chars to lowercase
        }

        else {
            lowercase_str += s[i];
        }
    }
    return lowercase_str; //new string containing lowercase chars of input string
}

/* Take input char and return binary string of length five
at the index of the give char */
string to_binary(char c){
    int index = 0;
    index = c - 'a'; //index found by taking int data-type char and substracting by char a, substracts the coresponding ascii num
    string bit_str = ""; 

    if (!islower(c)){
        return "";
    } 
   
    for (int i = 0; i < 5; i++){ //binary string must be size 5
        if (index % 2 == 0){ //finds binary 0 if found index goes into 2 with no remainder
            bit_str.push_back ('0');
        }

        if (index % 2 != 0){ //finds binary 1 if found index does not go into 2 and has a remainder
            bit_str.push_back ('1');
        }
        index = index / 2;//continue to divide the found index by 2 and go back up to the previous if states to see what reigns true
    }
    reverse (bit_str.begin(), bit_str.end()); //reverse the binary string
    return bit_str;
} 

/* Opposite of to_binary. Take input binary string, return
character that corresponds to that binary string */
char from_binary(const string& s){
    int ascii_num_char = 0;
    int index = 0;

    if (s.length() != 5){ //length of binary string MUST be 5
        return 0;
    } 

    for(int i = s.length() - 1; i >= 0; --i){ //iterate through binary string from right to left
        if (s[i] == '1' || s[i] == '0'){ //accounts for each element in string being a 1 or 0
            if (s[i] == '1'){
                ascii_num_char = ascii_num_char + pow (2, index); //finds corresponding "ascii" num for each char
            }
        }

        else {
            return 0;
        }
    index = index + 1; //increment index by 1
    }
    char ch = 'a' + ascii_num_char; //add ascii of char a by previously found "ascii" num to find corresponding character
    if (!islower(ch)) { //character must be lowercase
        return 0;
    }
    return ch;
} 

/* Given input plaintext string s must be at least
5 times the size of given input secret message string */
bool check_message (const string& s, const string& c){
    string plain_text = s;
    string secret_msg = c;
    int plaintxt_cnt = 0, secretmsg_cnt = 0;

    for (int i = 0; plain_text[i]; ++i){ //count each character in plaintext string
        if (isalpha(plain_text[i])){
            plaintxt_cnt++;
        }
    }
    
    for (int i = 0; secret_msg[i]; ++i){ //count each character in secret message string
        if(isalpha(secret_msg[i])){
            secretmsg_cnt++;
        }
    }

    if (plaintxt_cnt >= (5 * secretmsg_cnt)){ //boolean condition, plaintext character count must be greater than or equal to 5 times
                                                // the character count of secret message
        return true;
    }
    else {
        return false;
    }

} 

/* Encode secret message in the plaintext by creating
binary string for each char in secret message, iterating through
that string and looking at each character in plaintext that is at the same
positiong of each binary num in binary string and turns char
to lowercase if bin num at the same position is 0, uppercase
if bin num is 1 */
string encode (const string& s, const string& c){
    string plaintext = s;
    string secret_message = c;
    lower_case(plaintext);
    lower_case(secret_message);
    string encoded_text = "";

    if (check_message(plaintext, secret_message) == false){
        return "Error";
    }

    else {
        string bit_str = "";
        int plain_indx = 0;
        for (unsigned i = 0; i < secret_message.length(); ++i){ //iterate through each character in secret message and gives the binary number corresponding to the character
            if (isalpha(secret_message[i])){
                bit_str += to_binary(secret_message[i]);
            }
        }
        
        for (unsigned bit_char = 0; bit_char < bit_str.length(); ++bit_char){ //iterate through binary string
            while (!isalpha(plaintext[plain_indx])){ //if character in plaintext is not alphabetic add it to encoded text with no change
                encoded_text.push_back(plaintext[plain_indx]);
                plain_indx++;
            }
          
            if (bit_str[bit_char] == '0'){ //for every '0' in binary string, at that same position, turn plaintext char to lower
                if (isalpha(plaintext[plain_indx])){
                    encoded_text.push_back(tolower(plaintext[plain_indx]));
                }
            }

            else {
                if (isalpha(plaintext[plain_indx])){ //for every '1' in binary string, at the same position, turn plaintext char to upper
                    encoded_text.push_back(toupper(plaintext[plain_indx]));
                }
            }
            plain_indx++; //continue to increment index for plaintext by 1
        }
        //encoded text is created by the size of secret message/ binary string of secret message, must account for the rest of the plaintext chars
        while (plaintext.length() > encoded_text.length()){ //grabs the rest of the plaintext characters and turns the rest to lower
            encoded_text.push_back(tolower(plaintext[plain_indx]));
            plain_indx++;
        }
        plain_indx = 0; //re-initialize plaintext index to go back around through the for loop again
    }
    return encoded_text;
} 

/* Takes in a string, creates binary
string for each individual character in string
substring every 5 binary characters, take 
from binary and turn to original secret message */
string decode (const string& s){
    string to_decode = s;
    string binary_str = "";
    string new_secretmsg = "";

    for (unsigned i = 0; i < to_decode.length(); ++i){ //iterate through all characters in given string
        if (isalpha(to_decode[i])){
            if (isupper(to_decode[i])){ //looks to find uppercase characters and adds 1 to binary string
                binary_str += '1';
            }

            if (islower(to_decode[i])){ //looks to find lowercase characters and add 0 to binary string
                binary_str += '0';
            }
        }
    }

  //accounts for all lengths of the binary string that is a multiple of 5 only
    for (unsigned i = 0; i < binary_str.length()-4; i += 5){ //iterate through binary string 
        string new_substr = binary_str.substr(i, 5); //create binary substrings of length 5 
        new_secretmsg += from_binary(new_substr); //add characters that correspond to each binary substring to create original secret message
    }
    return new_secretmsg;
}