//
//  main.cpp
//  project09
//
//  Created by Emani Hunter on 3/31/19.
//  Copyright © 2019 Emani Hunter. All rights reserved.
//

#include <iostream>
#include "proj09_class.h"

int main() {

    
    MVM mvm1 { {"abc", {"a","b", "c"}},
        {"xyz", {"x","y","z"}}
    };
    
    mvm1.add("qrs","q");
    
    std::cout << mvm1.data_[1] << std::endl;
    //size_t sz = 3;
    
    //ASSERT_EQ(mvm1.size(), sz);
    
    //Element e2 = {"qrs",{"q"}};
    //ASSERT_EQ(mvm1.data_[1],e2);
    
//    return add;
}
