  /* proj09; Sect. 06; 4/8/2019 */

#include <stdio.h>
#include "proj09_class.h"
#include<sstream>
#include<algorithm>
using std::ostringstream;

//Element :

/* Element constructor with given parameters, assigned data members to given parameters,
 assigned values to vector/ initializer list, keys to given input string*/
Element::Element(string key, initializer_list<string> values){
    key_ = key;
    values_ = values;
}

/* Checks if two elements are equal by checking if keys and values
 are the same*/
bool Element::operator==(const Element& new_element)const{
    if (key_ == new_element.key_ && values_ == new_element.values_){
        return true; //returns true of keys and and val are the same
    }
    return false;
}

/*Prints out elements values and keys */
ostream& operator<<(ostream& out, Element& new_element){
    ostringstream value;

    for (int i = 0; i < new_element.values_.size(); ++i){ //iterates through values to outstream the elements
        value << new_element.values_[i] << ",";
    }
    string vect = value.str();
    string print_vals = vect.substr(0, vect.length()-1);
    
    out << new_element.key_ << ":" << print_vals; //outputs the keys and values in key: value format
    return out;
}

//MVM :

/* MVM constructor with given paramenter, assigns element vector
 data_ to given initializer list*/
MVM::MVM(initializer_list<Element> element_data){
    data_ = element_data;
}

/* Looks given input key in data_ vector, returns iterator
 that points to position of where input key is*/
vector<Element>::iterator MVM::find_key(string key){
    vector<Element>::iterator key_itr;
    
    key_itr = std::lower_bound(data_.begin(), data_.end(),key, [] (Element& e, string key){ return key > e.key_;
    }); //uses lowerbound algorithm, that returns iterator pointing to first element in container
        //that is >= provided key
    
    return key_itr;
    
}
/*Finds input value, returns vector of strings that is a list of all
the keys that have the given value */
vector<string> MVM::find_value(string val){
    vector<string> val_vect;
    Element e;
    
    for (auto e: data_){
        auto itr = std::find(e.values_.begin(), e.values_.end(), val); //creates an iterator to find the value in the values vector
        
        if (itr != e.values_.end()){ //as long as the iterator is not past the end of the values vector
            val_vect.push_back(e.key_); //create a new vector containing all keys that have the corresponding value
        }
    }
    
    return val_vect;

}

/* Add function adds element containing new key and value pair if key and value
pair do not exist/ adds new value to corresponding key if key exists and value is
not in the values vector- returns true if "anything" could be added
 return false otherwise*/
bool MVM::add(string key ,string value){
    Element e;
    auto key_itr = find_key(key); //creates iterator that points to position of input key

    if (key_itr != data_.end() && key_itr->key_ == key){ //if key exists_
        for (int i = 0; i < key_itr->values_.size(); i++){
            if (value != key_itr->values_[i]){ //if val not in vals_
                key_itr->values_.push_back(value); //push back value into vector
            }
            else {
                return false;
            }
        }
    }
    
    if (key_itr == data_.end() || key_itr->key_ != key){ //if key does not exist
        data_.insert(key_itr, Element(key,{value})); //inserts new element with key value pair into position that find_key iterator points to
        return true;
    }
 
    return true; //returns true if anything could be added
    
}

/* Returns the size of the data vector*/
size_t MVM::size(){
    return data_.size();
}

/* Checks if key is in the MVM member, removes key if it exists
and returns true, otherwise, returns false */
bool MVM::remove_key(string key){
    auto key_itr = find_key(key); //find_key iterator to point to position that input key is located
    
    if (key_itr != data_.end()){
        if (key_itr->key_ == key){
            data_.erase(key_itr); //erase the key that corresponds to the key pointing the corresponding position
            return true;
            
        }
        return false;

    }
    return false;
}

/* Checks if value is in values_ vector, removes value if it exists within,
and adds all keys that had a value removed to a vector  */
vector<string> MVM::remove_value(string val){
    Element e;
    vector<string> key_vect;
    auto val_itr_vect = find_value(val); //gives position that value is located
    
    for (int i = 0; i < val_itr_vect.size(); i++ ){
        auto found_vals_key = find_key(val_itr_vect[i]); //finds position that key is located
        found_vals_key->values_.erase(std::find(found_vals_key->values_.begin(), found_vals_key->values_.end(), val)); //erases corresponding values

    }
    return val_itr_vect; //returns all keys that had value removed
    
}

/*Prints out all elements that are in the MVM constructor */
ostream& operator<<(ostream& out, MVM& map){
    ostringstream value;
    Element e;
    
    for(auto i =0; i < map.data_.size(); i++){
        value << map.data_[i] <<" "; //outs all corresponding elements in data_ vector in map in MVM
    }
    string map_items = value.str(); //turns comma separated elements into string
    string print_map = map_items.substr(0, map_items.length() - 1); //create substring include first element to the last element (disregarding last comma)
    out << print_map;
    
    return out;
}


