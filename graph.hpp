//
//  graph.hpp
//  PrimsAlgorithm
//
//  Created by Utkarsh Khandelwal on 29/03/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <string>
#include <set>
#include <map>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <numeric>


using namespace std;
struct Edge
{
    int node1;
    int node2;
    int edgeCost;
};

struct Node
{
    int nodeValue;
    int nodeMinCost;
};

class Graph{
public:
    Graph(std::string inputPath);
    int FindMST();
    int UpdateCost(int &nodeAdded, std::vector<Node> &minNodesData);
    
private:
    std::vector<Edge> p_edges;
    std::set<int> p_nodes;

    std::unordered_map<int, std::vector<Edge>> tableNodeToEdges;
    std::map<int, std::vector<Edge>> p_map_nodeToEdges;
    
    
    int p_nodesCount;
    int p_edgesCount;
};
#endif
