/* proj10 , section 6, 4/15/19*/
#include <stdio.h>
#pragma once
#include<iostream>
using std::cout; using std::endl; using std::boolalpha; using std::ostream;
#include<initializer_list>
using std::initializer_list;
#include <algorithm>
using std::max; using std::copy; using std::swap;
#include <utility>
using std::make_pair; using std::pair;
#include <stdexcept>
using std::runtime_error;
#include<sstream>
#include<algorithm>
#include<string>
using std::string;
#include<vector>
using std::vector;

const static size_t element_array_size = 5;

template<typename K, typename V>
struct Element{
public:
    K key_;
    V values_[element_array_size];
    size_t count_ = 0;
    Element()=default;
    Element(K, initializer_list<V>);
    bool operator==(const Element&)const;
    bool operator<(const K&) const;
    //prints out elements using ostream
    friend ostream& operator<<(ostream& oss, Element<K, V>& ele)
    {
        //Code for the ostream operator goes here
        
        std::ostringstream value;
        
        for (int i = 0; i < ele.count_; ++i){ //iterates through values to outstream the elements
            value << ele.values_[i] << ",";
        }
        string vect = value.str();
        string print_vals = vect.substr(0, vect.length()-1); //disregards last comma
        
        oss << ele.key_ << ":" << print_vals; //outputs the keys and values in key: value format
        return oss;
        
    }
    
};

//Code for Element functions goes here
//element constructor, assigned data members to given parameters
template<typename K, typename V>
Element<K,V>::Element(K key, initializer_list<V> values){
    std::copy(values.begin(), values.end(), values_); //copied initializer list elements into values_ array
    count_ = values.size(); //count is size of initializer list
    key_ = key;
}
//check if two elements are equal by checking if size, keys and values are the same
template<typename K, typename V>
bool Element<K,V>::operator==(const Element<K,V>& new_element)const {
    for (int i = 0; i < new_element.count_ ; i++){
        if (key_ == new_element.key_ && values_[i] == new_element.values_[i] && count_ == new_element.count_){
            return true;//returns true if keys and val are the same
        }
    }
    return false;
}


//MVM

template<typename K, typename V>
class MVM{
public:
    Element<K, V> * data_ = nullptr;
    //Element<K,V> * ptr;
    size_t num_keys_ = 0;
    size_t num_elements_ = 0;
    Element<K, V> * find_key(K);
    size_t find_value(V, K*&);
    void grow();
    
public:
    MVM()=default;
    MVM(initializer_list<Element<K,V>>);
    MVM(const MVM&);
    ~MVM();
    size_t size();
    bool add(K,V);
    bool remove_key(K);
    size_t remove_value(V, K*&);
    //prints out mvm elements using ostream
    friend ostream& operator<<(ostream& oss, MVM& mvm)
    //Code for the ostream operator goes here
    {
        std::ostringstream value;
       
        for(auto i =0; i < mvm.size(); i++){
            value << mvm.data_[i] <<" "; //outs all corresponding elements in data_ vector in map in MVM
        }
        string map_items = value.str(); //turns comma separated elements into string
        string print_map = map_items.substr(0, map_items.length() - 1); //create substring include first element to the last element (disregarding last comma)
        oss << print_map;
        
        return oss;
    }
    
};

// Code for MVM functions goes here
//mvm constructor with initializer list given parameter, data_ assigned to new array, initializer list elements copied to data array
template<typename K, typename V>
MVM<K,V>::MVM(initializer_list<Element<K,V>> element_data){

    num_keys_ = element_data.size();
    num_elements_ = element_data.size();
    data_ = new Element<K,V>[num_elements_];
    std::copy(element_data.begin(), element_data.end(), data_);
    
}
//returns pointer that points to position of where input key is
template<typename K, typename V>
Element<K, V> * MVM<K,V>::find_key(K key){
   
    return std::lower_bound(data_, data_ + num_keys_ ,key, [] (Element<K,V>& e, K key)
                            { return e.key_ < key;
                            }); //uses lowerbound algorithm, that returns iterator pointing to first element in container
    //that is < provided key

}
//finds input value, returns number of keys that had that value
template<typename K, typename V>
size_t MVM<K,V>::find_value(V val, K* (&keys_found)){
    vector<K> key_vect;
    size_t cnt = 0;
    
    if (keys_found != nullptr){
        throw runtime_error( "Runtime Error");
        return 0;
    }
    else {
        
        for (auto i = data_; i < data_ + num_elements_; i++){
            for (auto j: (*i).values_) {
                
                if (val == j){//if input value equals one of the values in the values_ data member
                    key_vect.push_back((*i).key_); //pushes back keys that had corresponding val
                    cnt++; //incremenet count by one to count how many keys are added
                }
            }
            
        }
        if (key_vect.size() >= 1) {
            keys_found = new K[cnt]; //sets keys_found to new array
            
            std::copy(key_vect.begin(), key_vect.end(), keys_found);//copy key vector elements into keys_found array
        }
        
    }
    
    return cnt;
}

//mvm copy constructor, copies all data elements into new array
template<typename K, typename V>
MVM<K,V>::MVM(const MVM& mvm){
    
    data_ = new Element<K,V>[mvm.num_elements_]; //new array created
    std::copy(data_, data_ + num_elements_, mvm.num_keys_); //copy algorithm using data_ data member
    
    num_elements_ = mvm.num_elements_;
    num_keys_ = mvm.num_keys_;
    
}
//deconstructor, deletes data_ array after data_ has be assigned to new array previously
template<typename K, typename V>
MVM<K,V>::~MVM(){
    if (data_ != nullptr){
        delete[] data_;
    }
}
//grows array to allocate more memory/space
template<typename K, typename V>
void MVM<K,V>::grow(){
    Element<K,V> *new_ary;
    
    if (num_elements_ == 0){
        new_ary = new Element<K,V>[2]{};
        num_elements_ = 2;
        data_ = new_ary; //data_ array assigned to newly created array
    }
    else{
        
        new_ary = new Element<K,V>[num_elements_ * 2]{};//new array created of doubled size
        copy(data_, data_+num_elements_, new_ary); //copies data_ elements into new array
        num_elements_ *= 2; //grows num elements by 2
        
        std::swap (new_ary, data_);
        delete [] new_ary;
    }
    
}

//adds element containing new key and value pair if key and value pair do not exist, adds new value to key if key exists and value is not in values
template<typename K, typename V>
bool MVM<K,V>::add(K key,V val){

    auto key_ptr = find_key(key); //creates pointer that points to position of input key
    
    if (key_ptr != data_ + num_keys_ && key_ptr->key_ == key){ //if key exists_
        auto ptr = std::find(key_ptr->values_, key_ptr->values_ + key_ptr->count_, val);
        
        if (ptr == key_ptr->values_ + key_ptr->count_){ //if value not in values_
            if (key_ptr->count_ == element_array_size){ //must check if array is at max capacity, if so, can't add value
                return false;
            }
            else {
                
                key_ptr->values_[key_ptr->count_] = val; //adds new value
                key_ptr->count_++;
    
            }
        }
        else {
            return false;
        }
        
    }
    
    if (key_ptr == data_ + num_elements_|| key_ptr->key_ != key){ //if key does not exist
        size_t insert_position = std::distance(data_, key_ptr); //use distance algorithm to find distance between two pointer for help for element insertion position
        if (num_keys_ == num_elements_ ){ //must grow the array if there is not enough room
            grow();
            
        }
        data_[num_keys_] = Element<K,V>(key,{val}); //adds element
        num_keys_ ++;
        std::rotate (data_ + insert_position, data_ + num_keys_ - 1, data_ + num_keys_); //rotates the array so that the element added is at the end instead of the beginning?
        
        return true;
    }
    
    return true;
}
//returns num_keys_ data member
template<typename K, typename V>
size_t MVM<K,V>::size(){
    return num_keys_;
}
//overwrites elements on top of the key that we want "removed", so elements are shifted by one
template<typename K, typename V>
bool MVM<K,V>::remove_key(K key){
    
    auto key_ptr = find_key(key); //find_key iterator to point to position that input key is located
    
    if (key_ptr != data_ + num_keys_){
        if (key_ptr->key_ == key){
            std::move(key_ptr + 1 , key_ptr + num_keys_  , data_); //moves elements, disregards key that we want to remove and shifts the elements by one starting at the position that the key that we want to remove is
            num_keys_ --;
            
            return true;
        }
        return false;
    }
    return false;
    
}
//check if value is in values_ array, tries to overwrite elements on top of value we want to remove, and return the number of keys affected, unresolved.
template<typename K, typename V>
size_t MVM<K,V>::remove_value(V val, K* (&keys_found)){
    
    
    vector<K> key_vect;
    size_t cnt = 0;
    auto val_ptr = find_value(val, keys_found); 
    if (keys_found != nullptr){
        throw runtime_error( "Runtime Error");
        return 0;
    }
    
    else {

        auto val_ptr = find_value(val, keys_found); //give number of keys where value is located
        for (auto i = data_; i < data_ + num_elements_; i++){
            
            for (auto j: (*i).values_) {
                auto found_vals_key = find_key(i->key_);
                if (val == j){ //if input val is equal to value in values_
   
                    std::move(val_ptr + data_, found_vals_key + val_ptr +num_keys_ , data_);//unresolved/issues
                    num_keys_ --;
              
                    key_vect.push_back((*i).key_); //keys affected vect
                    cnt++;
                
                }
            }
            
        }
        
        if (key_vect.size() >= 1){
            keys_found = new K[cnt];
            
            std::copy(key_vect.begin(), key_vect.end(), keys_found); //copies keys affected into keys_found array like find_value
        }
    }
    return cnt;
    //unresolved, sorry.
}




