//
//  main.cpp
//  PrimsAlgorithm
//
//  Created by Utkarsh Khandelwal on 29/03/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#include <iostream>
#include "graph.hpp"
int main(int argc, const char * argv[]) {

    // insert code here...
    string filePath;
    if(argc == 2)
    {
        filePath = argv[1];
    }
    else
        return 1;
    
    Graph graph(filePath);
    int cost = graph.FindMST();

    std::cout << "Net Cost is : " << cost <<endl;;
    return 0;
}
