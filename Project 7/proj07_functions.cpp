/* Sect. 06; 3/17/19; proj07 */

#include<string>
using std::string;
#include<vector>
using std::vector;
#include<iostream>
using std::ostream; using std::cout; using std::endl;
#include<map>
using std::map;
#include <ostream>
using std::ostream;
#include<sstream>
using std::ostringstream; using std::stringstream;
#include<fstream>
using std::ifstream;
#include<algorithm>
using std::set_intersection;
using std::set_union;
using std::back_inserter;
#include<cmath>
using std::pow;

#include "proj07_functions.hpp"

using map_type = map<string, long >;

/* Prints input vector into given ostream, separates
 each element with a comma */
ostream& print_vector (ostream &out, const vector<string> &v){
    ostringstream vect_str;
    for (int i = 0; i < v.size(); ++i){ //iterate through input vector
        vect_str << v[i] << ","; //comma separated elements
    }
    string vect = vect_str.str(); //turns comma separated elements into string
    string  print_vec = vect.substr(0, vect.length()-1); //create substring include first element to the last element (disregarding last comma)
    out << print_vec;
    return out;
}
/* Cleans input string of non-alphabetic
characters and turns string to lower-case */
string clean_word(const string &s){
    string new_str = "";
    for (int i = 0; i < s.length(); i++){ //go through each char in string
        
        if (isalpha(s[i])){ //check if char is alphabetic
            new_str += tolower(s[i]); //turns lowercase
        }
    }
    return new_str;
}
/* Splits string by a given character (delim) */
vector<string> split(const string &s, char delim){
    vector<string> split_vec;
    stringstream s1(s);
    string split_string;
    
    while (getline(s1, split_string, delim)){ //grabs string with delim //splits string
        split_vec.push_back(split_string);
    }

    return split_vec;
}
/* Opens input file, reads, splits each line
and cleans each corresponding word, establishes
the key and value for each word */
bool process_words(map_type &m, string file){
    ifstream infile;
    string line;
    vector<string> words_vect;
 
    infile.open(file); //open file
    if (infile.fail()){ //if file does not open, run false
        return false;
    }
    
    else {
        while (getline(infile, line)){
            words_vect = split(line); //split each line of default character
            for (auto i : words_vect){
                string key_words = clean_word(i); //clean each word of non-alpha and turn lower
                m[key_words] += 1; //establishes value, +=1 everytime the word shows up in map

            }
        }
        return true;
    }
}
/* Prints input map into given ostream, separates
 each pair with a comma */
ostream& print_map(ostream& out, const map_type& m){
    ostringstream map_contents;
    
    for (auto i : m){ //iterate through input map
        map_contents << i.first <<":"<< i.second << ",";
    }
    
    string map_items = map_contents.str(); //turns comma separated elements into string
    string print_map = map_items.substr(0, map_items.length() - 1); //create substring include first element to the last element (disregarding last comma)
    out << print_map;
    
    return out;
}
/* Takes in two input maps, uses keys in each map
to determine what words are similar in each map and determine
overall frequency/ jaccard similarity using quotient formula */
double jaccard_similarity(const map_type &m1, const map_type &m2){
    vector<string> map_to_vec1;
    vector<string> map_to_vec2;
    vector<string> intersection;
    vector<string> new_union;

    for (auto i1 : m1){ //iterate through input map
        string word_processed = clean_word(i1.first);
        map_to_vec1.push_back(word_processed);
        
    }
    for (auto i2 : m2){ //iterate through input map
        string word_processed2 = clean_word(i2.first);
        map_to_vec2.push_back(word_processed2);
    }
    set_intersection(map_to_vec1.begin(), map_to_vec1.end(), map_to_vec2.begin(), map_to_vec2.end(), back_inserter(intersection)); //find what words are the same in both maps
    set_union(map_to_vec1.begin(), map_to_vec1.end(), map_to_vec2.begin(), map_to_vec2.end(), back_inserter(new_union)); //find everything in both maps

    double jaccard = (static_cast<double>(intersection.size())/ static_cast<double>(new_union.size())); //compute jaccard similarity
    
    return jaccard;
}
/* Takes in input map, looks at the values in the map
to help determine the normalized frequency of each word */
double calc_norm_factor(const map_type &m1){
    vector<long> val_vect;
    double norm_fact = 0;
    double term_seq = 0;
    
    for (auto i: m1){ //iterate through input map
        val_vect.push_back(i.second); //add all values to vector
    }
    
    for (int j = 0; j < val_vect.size(); j++){
        term_seq += pow(val_vect[j], 2); //calculate sum of all terms squared
    }
    norm_fact = sqrt(term_seq); //calculate normalized frequency by squaring the sum of squared terms
    
    return norm_fact;
}
/* this is very inefficient and i'm sorry you have to see this again so sad :( ,
 
 calculates cosine similarity by taking normalized frequency and
 value of each corresponding key and dividing them together,
 then taking the sum of these quotients to find cos sim*/
 double cosine_similarity_tf(const map_type &m1, const map_type &m2){
     vector<long> val_vect1;
     vector<long> val_vect2;
     map_type map1 = m1;
     map_type map2 = m2;
     
     double cosine_sim = 0;
     double u = calc_norm_factor(map1);
     double v = calc_norm_factor(map2);
     
     for (auto i1: m1){
         if (map2.find(i1.first) == map2.end()){ //checks if specific word (key) in map 1 is not found in map 2
             map2.insert(std::make_pair(clean_word(i1.first), 0)); //adds the key to map 2 and gives value of 0
         }
     }
     for (auto i2: m2){
         if (map1.find(i2.first) == map1.end()){ //vice versa for any key in map 2 not found in map 1
             map1.insert(std::make_pair(clean_word(i2.first), 0));
         }
         
     }
     
     for (auto i : map1){ //iterate through maps to store values in new vector
         val_vect1.push_back(i.second);
     }
     
     for (auto i : map2){
         val_vect2.push_back(i.second);
     }
     
     for (int i = 0; i < val_vect1.size(); i++){ //because previously considering both vectors to be of same size, iterate through one vector
         double norm_freq1 = val_vect1[i] / u; //find normalized frequency by dividing each value by normal factor
         double norm_freq2 = val_vect2[i] / v;
         
         cosine_sim += (norm_freq1 * norm_freq2); //computer cosine_similary ; dot product
     }

     return cosine_sim;
 }
