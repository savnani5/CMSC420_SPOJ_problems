// SPOJ username: madara_op
// Status : https://www.spoj.com/status/INVENT,madara_op/

#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

class Node
{ 
    public:
        int parent=-1;
        int children=0;
        int rank=0;
};

// Find operation with path compression
int Find(int x, vector<Node>& DisjointSet)
{
    if(DisjointSet[x].parent == -1)
        return x;
    return DisjointSet[x].parent = Find(DisjointSet[x].parent, DisjointSet); 
}

// Union of nodes by Rank 
long Union(pair<int, pair<int, int>> e, vector<Node>& DisjointSet)
{
    int AR1 = Find(e.second.first, DisjointSet);
    int AR2 = Find(e.second.second, DisjointSet);

    // Calculating the sum of set
    long sum = e.first;
    long nodes_set1 = DisjointSet[AR1].children+1;
    long nodes_set2 = DisjointSet[AR2].children+1;
    sum+=(e.first+1)*((nodes_set1*nodes_set2)-1);

    // Conditions for union
    if(DisjointSet[AR1].rank > DisjointSet[AR2].rank)
    {
        DisjointSet[AR2].parent = AR1;
        DisjointSet[AR1].children+=DisjointSet[AR2].children+1;
    }
    else if(DisjointSet[AR1].rank < DisjointSet[AR2].rank)
    {
        DisjointSet[AR1].parent = AR2;
        DisjointSet[AR2].children+=DisjointSet[AR1].children+1;
    }
    else
    {
        DisjointSet[AR2].parent = AR1;
        DisjointSet[AR1].children+=DisjointSet[AR2].children+1;
        DisjointSet[AR1].rank++;
    }

    return sum;
}

long OutputMinWeight(int n, vector<Node>& DisjointSet, vector<pair<int, pair<int, int>>>& EdgeList)
{
    // Sum of weights in the graph
    long total_sum=0;

    // Adding nodes to the DisjointSet vector
    for(int i=0; i<=n; i++)
    {
        Node n;
        DisjointSet.push_back(n);       
    }

    // Sorting the edge list based on weights
    sort(EdgeList.begin(), EdgeList.end());

    for(auto e: EdgeList)
    {
        total_sum += Union(e, DisjointSet);
    }
    return total_sum;
}


int main()
{
    // Input conditions
    int test_cases;
    cin >> test_cases;
    vector<vector<pair<int, pair<int, int>>>> test_edges;
    cout << endl;
    for(int i=0; i<test_cases; i++)
    {
        int n;
        cin >> n;
        vector<pair<int, pair<int, int>>> EdgeList;  // Vector of pairs {weight, {node1, node2}}
        for(int j=0; j<n-1; j++)
        {
            int n1,n2,w;
            cin >> n1 >> n2 >> w;
            EdgeList.push_back(make_pair(w, make_pair(n1,n2))); 
        }
        test_edges.push_back(EdgeList);
        cout << endl;
    }

    // Output 
    for(auto EdgeList: test_edges)
    {
        vector<Node> DisjointSet;
        long weight = OutputMinWeight(EdgeList.size()+1, DisjointSet, EdgeList);
        cout << weight << endl;
    }
}

