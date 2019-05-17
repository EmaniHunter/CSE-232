/* proj11, sect.6 , 4/22/19 */
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
using std::ostringstream;
#include<string>
using std::string;

const static size_t element_array_size = 5;

template<typename K, typename V>
struct Element{
public:
    K key_;
    V values_[element_array_size];
    Element* next_ = nullptr;
    
    //Optional
    //Element* previous = nullptr;
    
    size_t count_ = 0;
    
    Element()=default;
    Element(K, initializer_list<V>);
    Element(const Element&);
    bool operator==(const Element&)const;
    bool operator<(const K&) const;
    friend ostream& operator<<(ostream& oss, Element<K,V>& ele){
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
    std::copy(values.begin(), values.end(), values_);//copied initializer list elements into values_ array
    count_ = values.size();//count is size of initializer list
    key_ = key;
    next_ = nullptr;
}
//check if two elements are equal by checking if size, keys and values are the same
template<typename K, typename V>
bool Element<K,V>::operator==(const Element<K,V>& new_element)const{
    for (int i = 0; i < new_element.count_ ; i++){
        if (key_ == new_element.key_ && values_[i] == new_element.values_[i] && count_ == new_element.count_){
            return true;//returns true if keys and val are the same
        }
    }
    return false;
}
//copy constructor for new element
template<typename K, typename V>
Element<K,V>::Element(const Element<K,V>& other){
    
    key_ = other.key_;
    count_ = other.count_;
    std::copy(other.values_, other.values_ + other.count_, values_); //copies new elements val array into val array
    next_ = nullptr;
}

//MVM

template<typename K, typename V>
class MVM{
public:
    Element<K, V> * data_head_ = nullptr;
    
    //optional
    Element<K, V> * data_tail_ = nullptr;
    size_t num_elements_ = 0;
    
    size_t num_keys_ = 0;
    
    pair <Element<K,V>*, Element<K,V> *> find_key(K);
    MVM find_value(V);
    
public:
    //Constructors
    MVM()=default;
    MVM(initializer_list<Element<K,V>>);
    
    //Rule of Three
    MVM(const MVM&);
    MVM& operator=(const MVM& other);
    ~MVM();
    
    //Other Functions
    size_t size();
    bool add(K,V);
    bool remove_key(K);
    MVM remove_value(V);
    
    friend ostream& operator<<(ostream& oss, MVM& mv){
        //Code for the ostream operator goes here
        ostringstream os;
        for (Element<K,V>* ptr = mv.data_head_; ptr != nullptr; ptr = ptr->next_){//outs all corresponding elements in linked list
            os << *ptr << " ";
        }
        string str = os.str();  //turns space separated elements into string
        oss << str.substr(0, str.size()-1); //create substring include first element to the last element (disregarding last space)
        return oss;
    }
};

// Code for MVM functions goes here
//mvm constructor with initializer list given parameter, data_ head_ assigned to beginning of linked list , moves on to next element in list
template<typename K, typename V>
MVM<K,V>::MVM(initializer_list<Element<K,V>> data){ //from example code
    //Element<K,V>* current;
    num_keys_ = data.size();
    int cnt = 0;
    for (auto element: data){ //iterate through initializer list
        Element<K,V>* ptr = new Element<K,V>(element);

        if (cnt == 0){ //if we only have one element,first and last element
            data_head_ = ptr;
            data_tail_ = ptr;
        }
        cnt++;
        data_tail_->next_ = ptr; //move on to next element in list
        data_tail_ = data_tail_->next_;
        
    }
}
//copy constructor, assigns what is needed for  MVM passed in
template<typename K, typename V>
MVM<K,V>::MVM(const MVM& other){
    if (other.data_head_ == nullptr){
        data_head_ = nullptr;
        data_tail_ = nullptr;
    }
    else {
        data_head_ = new Element<K,V>(*other.data_head_); //creates new element with the first element being the first in the MVM
        data_tail_ = data_head_; //assigns the end of list to beginning
        Element<K,V>* initlist_ptr = other.data_head_->next_;
        Element<K,V>* new_ele;
        
        while(initlist_ptr != nullptr){
            new_ele = new Element<K,V>(*initlist_ptr);
            data_tail_->next_ = new_ele; //move on to next element in list
            
            initlist_ptr = initlist_ptr->next_;
            data_tail_ = new_ele; //assign end of list to element
        }
        
    }
}
//deconstructor, deletes data_head_ moves data_head_ on to next element in list
template<typename K, typename V>
MVM<K,V>::~MVM(){
    Element<K,V>* to_del = data_head_;
    while(to_del != nullptr){
        data_head_ = data_head_->next_;
        delete to_del; //deconstruction
        to_del = data_head_;
    }
    data_head_ = nullptr;
    data_tail_ = nullptr;
}
//returns pair that is of previous element and element coming next after given
template<typename K, typename V>
pair <Element<K,V>*, Element<K,V> *> MVM<K,V>::find_key(K key){
    Element<K,V> *result = nullptr; //from example code
    Element<K,V> *ptr_pair1 = nullptr;
    
    for (Element<K,V> *ptr = data_head_; ptr != nullptr; ptr= ptr->next_){
        
        if (ptr->key_ >= key){ //referenced from example code, if element at beginning of linked list?
            result = ptr;
            break;
        }
        
        else if (ptr->key_ < key){ //if element smaller than .key_
            ptr_pair1 = ptr;
        }
        
        else {
            result = nullptr;
            ptr_pair1 = nullptr;
        }
    }
    
    pair <Element<K,V>*, Element<K,V> *> new_pair = make_pair(ptr_pair1, result);
    return new_pair;
}
//finds input value, returns keys sorted into a new MVM
template<typename K, typename V>
MVM<K,V> MVM<K,V>::find_value(V val){
    MVM<K,V> new_mvm;

    int cnt = 0;
    for (Element<K,V> *ptr = data_head_; ptr != nullptr; ptr = ptr->next_){
        for (auto i: ptr->values_){ //iterate through the values array
            if (val == i){
                Element<K,V>* new_ele = new Element<K,V>(ptr->key_, {val}); //creates new element with key and given value
                if (cnt == 0){ //first and only element in list
                    new_mvm.data_head_ = new_ele;
                    new_mvm.data_tail_ = new_ele;
   
                }
                else {
                    
                    new_mvm.data_tail_->next_ = new_ele; //move on to next element in list
                    new_mvm.data_tail_ = new_mvm.data_tail_->next_;
                }
                cnt++;
                
            }
        }
    }
    return new_mvm;
}

//swaps and re-assigns data members in passed in parameter
template<typename K, typename V>
MVM<K,V>& MVM<K,V>::operator=(const MVM& other){
    MVM<K,V>cop_mvm(other);
    std::swap(num_keys_, cop_mvm.num_keys_);
    std::swap(data_head_, cop_mvm.data_head_);
    std::swap(data_tail_, cop_mvm.data_tail_);
    return *this;
}

//returns number of keys in linked list
template<typename K, typename V>
size_t MVM<K,V>::size(){
    return num_keys_;
}
//adds element containing new key and value pair if key and value pair do not exist, adds new value to key if key exists and value is not in values
template<typename K, typename V>
bool MVM<K,V>::add(K key,V val){
    auto key_ptr = find_key(key);
    Element<K,V>* new_element = new Element<K,V>(key, {val});
    
    if (key_ptr.second != nullptr && key_ptr.second->key_ == key){ //if key exists

        if (key_ptr.second->count_ == element_array_size){ //must check if at max capacity
            return false;
        }

        for (int i = 0; i < key_ptr.second->count_; i++){
            if (val == key_ptr.second->values_[i]){ //if val in vals
                return false;
            }
            
        }
        
        key_ptr.second->values_[key_ptr.second->count_] = val; //adds in the value
        key_ptr.second->count_++;

        return true;
    }
    else {
        num_keys_++;
    }

    if (key_ptr.first != nullptr && key_ptr.second != nullptr ){ //middle edge case for check
        key_ptr.first->next_ = new_element; //pointers first moves on to the next and assigned to the new element
        new_element->next_ = key_ptr.second;
        
        return true;
        
    }
    if (key_ptr.first == nullptr && key_ptr.second != nullptr){ //beginning edge case for check

        if (data_head_ != nullptr){
            new_element->next_ = data_head_; //new element moved on to next and assgined to the head of the list
            data_head_ = new_element;
            return true;
        }
        else {
            data_head_ = new_element;
            data_tail_ = new_element;
            return true;
        }
    }
    if (key_ptr.first != nullptr && key_ptr.second == nullptr ){ //end edge case for check

        data_tail_ = new_element;
        data_tail_->next_ = nullptr; //end of list moves on to the next and points to null
        return true;

    }
    
    if (key_ptr.first == nullptr && key_ptr.second == nullptr){//checking if both pairs are nullptrs
        data_head_ = new_element; //turns beginning and end of list to new element respectively
        data_tail_ = new_element;
        return true;
    }
    
    return true;
    
}
//overwrites elements on top of the key that we want "removed", so elements are shifted by one
template<typename K, typename V>
bool MVM<K,V>::remove_key(K key){
    auto key_ptr = find_key(key);
 
    if (key_ptr.first == nullptr && key_ptr.second != nullptr){
        if (key_ptr.second->key_ == key){ //check if keys are the same
            data_head_ = data_head_->next_; //overwrites
            delete key_ptr.second; //removes the key
            num_keys_--;
            return true;
        }
    }

    if ( key_ptr.first != nullptr && key_ptr.second != nullptr){
        if (key_ptr.second->key_ == key){ //check keys are the same

            key_ptr.second = key_ptr.second->next_;
            delete key_ptr.second; //removes the key
            key_ptr.first->next_ = key_ptr.second->next_; //moves on to the next

            num_keys_--;
            return true;
        }
        return false;
    }
    return false;
}

 //check if value is in values_ array, tries to overwrite elements on top of value we want to remove, and return the MVM of keys affected.
template<typename K, typename V>
MVM<K,V> MVM<K,V>::remove_value(V val){
    MVM<K,V> new_mvm;
    int cnt = 0;
    
    for (Element<K,V> *ptr = data_head_; ptr != nullptr; ptr = ptr->next_){
        for (auto i: ptr->values_){
            if (val == i){
                Element<K,V>* new_ele = new Element<K,V>(ptr->key_, {val}); //creates new element with key and given value
                if (cnt == 0){ //first and only element in list
                    
                    new_mvm.data_head_ = new_ele;
                    new_mvm.data_tail_ = new_ele;

                    ptr->count_--; //decrement the count

                }
                else {

                    new_mvm.data_tail_->next_ = new_ele; //move on to next element in list
                    new_mvm.data_tail_ = new_mvm.data_tail_->next_;
                    ptr->count_--;

                }
                cnt++;
            }
        }
    }
    return new_mvm;
}


//memory leak unresolved
