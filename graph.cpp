//
//  graph.cpp
//  PrimsAlgorithm
//
//  Created by Utkarsh Khandelwal on 29/03/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//


#include "graph.hpp"
Graph::Graph(string inputPath)
{
    //Creating the graph
    ifstream input(inputPath);
    int iLine = 0;
    string lineData;
    while(  getline(input, lineData))
    {
        stringstream lineStream(lineData);
        vector<int> values;
        int value;
        while(lineStream >> value)
        {
            values.push_back(value);
        }
        if(iLine == 0)
        {
            p_nodesCount = values[0];
            p_edgesCount = values[1];
            iLine++;
        }
        else
        {
            int node1 = values[0];
            int node2 = values[1];
            int edgeCost = values[2];
            Edge currEdge;
            currEdge.node1 = node1;
            currEdge.node2 = node2;
            currEdge.edgeCost = edgeCost;
            p_edges.emplace_back(currEdge);
            iLine++;
        }
    }
    
    //All edges done
    for(auto edge : p_edges)
    {
        std::vector<int> nodes{edge.node1, edge.node2};
        for(auto node : nodes)
        {
            p_nodes.insert(node);
            auto it = tableNodeToEdges.find(node);
            if(it != tableNodeToEdges.end())
            {
                auto &edges = tableNodeToEdges[node];
                edges.push_back(edge);
            }
            else
            {
                std::vector<Edge> edges;
                edges.push_back(edge);
                tableNodeToEdges.insert({node, edges});
            }
        }
    }
}

int Graph::UpdateCost(int &nodeAdded, std::vector<Node> &minNodesData)
{
    auto &edges = tableNodeToEdges[nodeAdded];
    for(auto edge : edges)
    {
        int otherNode;
        if(nodeAdded == edge.node1)
            otherNode = edge.node2;
        else
            otherNode = edge.node1;
        
        auto &otherNodesEdges = tableNodeToEdges[otherNode];
        auto compLambda = [](const Edge &edge1, const Edge &edge2)->bool
        {
            return edge1.edgeCost < edge2.edgeCost;
        };
        auto smallIt = std::min_element(otherNodesEdges.begin(), otherNodesEdges.end(), compLambda);
        int minCost = (*smallIt).edgeCost;
        auto foundIt = std::find_if(minNodesData.begin(), minNodesData.end(), [&otherNode](const Node &node)->bool{
            return node.nodeValue == otherNode;
        });
        (*foundIt).nodeMinCost = minCost;
    }
    return 0;
}

int Graph::FindMST()
{
    vector<int> costs;

    Edge currEdge = p_edges.front();
    int seedNode = currEdge.node1;

    std::vector<Node> minNodesData;
    for(auto node : p_nodes)
    {
        Node nodeData;
        nodeData.nodeValue = node;
        nodeData.nodeMinCost = INT_MAX;
        minNodesData.push_back(nodeData);
    }
    UpdateCost(seedNode, minNodesData);
    
    set<int> domainNodes;
    domainNodes.insert(seedNode);
    
    while(domainNodes.size() != p_nodes.size())
    {
        auto compLamb = [](const Node &node1, const Node &node2)->bool
        {
            return node1.nodeMinCost < node2.nodeMinCost;
        };
        std::function<bool(const Node &, const Node &)> fxn= compLamb;
        priority_queue<Node, std::vector<Node>, std::function<bool(const Node &, const Node &)>> min_heap(fxn);
        
        for(auto data : minNodesData)
        {
            min_heap.push(data);
        }
        Node minCostNode = min_heap.top();
        costs.push_back(minCostNode.nodeMinCost);
        UpdateCost(minCostNode.nodeValue, minNodesData);        domainNodes.insert(minCostNode.nodeValue);
    }
    int sum = 0;
    sum = std::accumulate(costs.begin(), costs.end(), sum);
    return sum;
}
