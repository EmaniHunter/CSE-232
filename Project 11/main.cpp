#include<iostream>
using std::cout; using std::endl; using std::boolalpha;
#include<algorithm>
using std::copy;
#include<iterator>
using std::ostream_iterator;
#include <string>
using std::string;
#include<vector>
using std::vector;

#include "proj11_class.h"

int main (){
    cout << boolalpha;
    MVM<string, string> mvm1 { {"abc", {"a","b", "c"}},
        {"qrs", {"q","a"}},
        {"xyz", {"x","y","z"}}
    };
    
    
    MVM<string, string> temp = mvm1.remove_value("a");
    size_t sz = 3;
    cout << "size: " << mvm1.size() << " actual: " << sz << endl;
    vector<string> ans ={"abc","qrs"};
    auto head = temp.data_head_;
    for(size_t i = 0; i < ans.size(); i++){
        cout << head->key_ << " answer: " <<  ans[i] << endl;
        cout << head->values_[0] << " val: " <<  "a" << endl;
        head = head->next_;
    }
    
    Element<string, string> e ={"qrs",{"q"}};
    cout << *mvm1.data_head_->next_<< " next:" << e << endl;
//
//    MVM<string,string> mvm1 { {"abc", {"a","b", "c"}},
//        {"qrs", {"q","a"}},
//        {"xyz", {"x","y","z"}}
//    };
//
//    size_t sz = 2;
//    cout <<"must be true: " << mvm1.remove_key("abc") << endl;
//    cout << "must be false: " << mvm1.remove_key("tuv") << endl;
//    cout << "same size? " << mvm1.size() << " actual: " << sz << endl;
//    Element<string,string> e = {"qrs", {"q","a"}};
//    cout << *mvm1.data_head_ << " " << e << endl;
//    cout << "must be false: " << mvm1.remove_key("abc") << endl;
//    MVM<long, string> mvm1 { {10, {"a","b", "c","d", "e"}},
//        {50, {"x","y","z"}}
//    };
//
//    cout << mvm1.add(30,"q") << endl;
//    cout << mvm1.add(20,"a") << endl;
//    cout << mvm1.add(30,"a") << endl;
//
//    size_t sz = 4;
//
//    cout << mvm1.size() << " Actual: " << sz << endl;
//    Element<long, string> e1 = {20,{"a"}};
//    cout << *mvm1.data_head_->next_ << " " << e1 << endl;
//    Element<long, string> e2 = {30,{"q","a"}};
//    cout << *mvm1.data_head_->next_->next_ << " " << e2 << endl;
//
//    cout << mvm1.add(10, "c") << endl;
//    cout << mvm1.add(30, "a") << endl;
//    cout << mvm1.add(10, "e") << endl;
//
//    MVM<string, string> mvm1 { {"abc", {"a","b", "c"}},
//        {"xyz", {"x","y","z"}}
//    };
//
//    mvm1.add("qrs","q");
//
//    size_t sz = 3;
//
//    cout << mvm1.size() << " " <<  sz << endl;
//
//    Element<string, string> e2 = {"qrs",{"q"}};
//    cout << *mvm1.data_head_->next_ << " " << e2 << endl;
//    cout << mvm1.size() << endl;
//    cout << mvm1 << endl;
//    cout << boolalpha;
//    MVM<string, string> mvm1 { {"abc", {"a","b", "c"}},
//        {"xyz", {"x","y","z"}}
//    };
//
//    Element<string, string> e {"abc", {"a","b", "c"}};
////
//    cout << *mvm1.data_head_ << " " << e << endl;
    cout << boolalpha;
//    Element<string, string> e1;
//    e1.key_ = "abc";
//    e1.values_[0] = "a";
//    e1.values_[1] = "b";
//    e1.values_[2] = "c";
//    e1.count_ = 3;
//    cout << e1 << endl;
//    Element<string, string> e2("abc", {"a", "b", "c"} );
//    cout << (e1 == e2) << endl;
////
//    MVM<string, string> mvm1 { {"abc", {"a","b", "c"}},{"xyz", {"x","y","z"}}};
//    cout << "actual mvm " <<  mvm1 << endl;
//    auto result = mvm1.find_key("tuv");
//    cout << "find key stuff: " << result.second->key_ << endl;
//        Element<string, string> e {"abc", {"a","b", "c"}};
//    //
//    cout << "constructor stuff:  "<< *mvm1.data_head_ << " " << e << endl;
//    size_t sz = 3;
//    MVM<string,string> result_key = mvm1.find_value("a");
//    cout << "result_key for find_val: " <<  result_key << endl;
//    cout << mvm1.size() << " " << "but the answer size is: "<< sz<< endl;
//    cout << "check for qrs and q: " << mvm1.add("qrs", "q") << endl;
//    cout << "check for bcd and a: " << mvm1.add("bcd", "a") << endl;
//    cout << "check for qrs and a: " << mvm1.add("qrs", "a") << endl;
//    cout << "for add: " << mvm1 << endl;
//    cout << "new size: " << mvm1.size() << endl;
//    result_key = mvm1.find_value("a");
//    cout << "result_key for find_val" <<  result_key << endl;
//    cout << mvm1.remove_key("bcd") << endl;
//    cout << mvm1 << endl;
//    result_key = mvm1.remove_value("a");
//    cout << "result_key " <<  result_key << endl;
//    cout << mvm1 << endl;
}
