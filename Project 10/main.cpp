//
//  main.cpp
//  project10
//
//  Created by Emani Hunter on 4/9/19.
//  Copyright © 2019 Emani Hunter. All rights reserved.
//

#include<iostream>
using std::cout; using std::endl; using std::boolalpha;
#include<algorithm>
using std::copy;
#include<iterator>
using std::ostream_iterator;
#include <string>
using std::string;

#include "proj10_class.h"
using namespace std;

int main (){

    
    MVM<string, string> mvm1 { {"abc", {"a","b", "c"}},
        {"qrs", {"q","a"}},
        {"xyz", {"x","y","z"}}
    };
    
    size_t sz = 3;
    string * key_vec = nullptr;
    auto key_size = mvm1.remove_value("a", key_vec);
    cout<<mvm1.size()<< "--"<< sz << endl;
    vector<string> ans  {"abc", "qrs"};
    cout<< key_size << " ans: " << ans.size() << endl;
    
    for(size_t i = 0; i < key_size; i++){
        cout<<key_vec[i] << " ans: " <<ans[i] << endl;
    }
    Element<string, string> e ={"qrs",{"q"}};
    cout<<mvm1.data_[1] << " " << e << endl;
    
//    try{
//        auto key_size = mvm1.remove_value("q", key_vec);
//        ASSERT_FALSE(true);
//    } catch(std::runtime_error e){
//        ASSERT_TRUE(true);
//    }
//
    delete [] key_vec;
//    MVM<string,string> mvm1 { {"abc", {"a","b", "c"}},
//        {"qrs", {"q","a"}},
//        {"xyz", {"x","y","z"}}
//    };
//
//    size_t sz = 2;
//    mvm1.remove_key("abc");
//    mvm1.remove_key("tuv");
//    cout << mvm1.size()<<"--" <<  sz << endl;
//
//
//    Element<string,string> e = {"qrs", {"q","a"}};
//    cout<<mvm1.data_[0] << e << endl;
    //ASSERT_FALSE(mvm1.remove_key("abc"));
    
//    MVM<long, string> mvm1 { {10, {"a","b", "c","d", "e"}},
//        {50, {"x","y","z"}}
//    };
//
//    mvm1.add(30,"q");
//    mvm1.add(20,"a");
//    mvm1.add(30,"a");
//
//    size_t sz = 4;
//    //MVM<string, string> mvm1 { {"abc", {"a","b", "c"}},
////        {"xyz", {"x","y","z"}}
////    };
//
//    //mvm1.add("qrs","q");
//
//    //size_t sz = 3;
//
//    cout<<mvm1<<"--"<<sz<<endl;
//
//    //Element<string, string> e2 = {"qrs",{"q"}};
//    //cout<<mvm1.data_[1]<<e2<<endl;
//
//    Element<long, string> e1 = {20,{"a"}};
//    cout<<mvm1.data_[1] << e1 << endl;
//    Element<long, string> e2 = {30,{"q","a"}};
//    cout<<mvm1.data_[2]<<e2<<endl;

//    cout << boolalpha;
//    Element<string, string> e1;
//    e1.key_ = "abc";
//    e1.values_[0] = "a";
//    e1.values_[1] = "b";
//    e1.values_[2] = "c";
//    e1.count_ = 3;
//    cout << e1 << endl;
//    Element<string, string> e2("abc", {"a", "b", "c"} );
//    cout << (e1 == e2) << endl;
//
//    MVM<string, string> mvm1 { {"abc", {"a","b", "c"}},{"xyz", {"x","y","z"}}};
//    cout << "mvm " <<  mvm1 << endl;
//    auto result = mvm1.find_key("abc");
//    cout << result->key_ << endl;
//    string * result_key = nullptr;
//    size_t size_result_key = mvm1.find_value("a", result_key);
//    copy(result_key, result_key + size_result_key, ostream_iterator<string>(cout, ",") );
//    cout <<"\n"<<mvm1.size() << endl;
//    delete [] result_key;
//    result_key = nullptr;
//    cout << mvm1.add("qrs", "q") << endl;
//    cout << mvm1.add("bcd", "a") << endl;
//    cout << mvm1.add("qrs", "a") << endl;
//    cout << mvm1 << endl;
//    size_result_key = mvm1.find_value("a", result_key);
//    copy(result_key, result_key + size_result_key, ostream_iterator<string>(cout, ",") );
//    cout <<"\n"<< mvm1.remove_key("bcd") << endl;
//    delete [] result_key;
//    result_key = nullptr;
//    cout << mvm1 << endl;
//    size_result_key = mvm1.remove_value("a", result_key);
//    copy(result_key, result_key + size_result_key, ostream_iterator<string>(cout, ",") );
//    cout << "\n" << mvm1 << endl;
//    delete [] result_key;
//    result_key = nullptr;
}


