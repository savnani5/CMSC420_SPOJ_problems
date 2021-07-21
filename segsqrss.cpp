// SPOJ username: madara_op
// Status : https://www.spoj.com/status/SEGSQRSS,madara_op/

#include <bits/stdc++.h>
#include <iostream>
#include <math.h>

using namespace std;

// With lazy propogation (delayed updates)
class SegmentTree
{
    public:
        int sum_tree[1000000] = {0};
        int sum_of_sq_tree[1000000] = {0};
        int lazy_query0[1000000] = {0};
        int lazy_query1[1000000] = {0};
        vector<int> update_seq[1000000];

        void construct(int*, int ss, int se, int si);
        int getSumOfSquares(int ss, int se, int qs, int qe, int si);
        void updateRange(int si, int ss, int se, int us, int ue, int diff, int type);
}; 

void SegmentTree::construct(int* A, int ss, int se, int si)
{   
    // Leaf node
    if (ss == se)
    {
        sum_tree[si] = A[ss];
        sum_of_sq_tree[si] = pow(A[ss],2);
        return;
    }
  
    int mid = (ss + se)/2;
    SegmentTree::construct(A, ss, mid, si*2+1);
    SegmentTree::construct(A, mid+1, se, si*2+2);
  
    sum_tree[si] = sum_tree[si*2 + 1] + sum_tree[si*2 + 2];
    sum_of_sq_tree[si] = sum_of_sq_tree[si*2 + 1] + sum_of_sq_tree[si*2 + 2];
}


int SegmentTree::getSumOfSquares(int ss, int se, int qs, int qe, int si)
{
    if(!update_seq[si].empty())
    {
        for(auto x:update_seq[si])
        {
            if(x==0)
            {
                if (lazy_query0[si] != 0)
                {
                    sum_of_sq_tree[si] = (se-ss+1)*pow(lazy_query0[si],2);
                    sum_tree[si] = (se-ss+1)*lazy_query0[si];

                    // If not a leaf node propogate the value to the children
                    if (ss != se)
                    {
                        lazy_query0[si*2 + 1] = lazy_query0[si];
                        lazy_query0[si*2 + 2] = lazy_query0[si];
                        update_seq[si*2 + 1].push_back(0);
                        update_seq[si*2 + 2].push_back(0);
                    }
                    lazy_query0[si] = 0;
                }
            }
            else
            {
                if (lazy_query1[si] != 0)
                {
                    sum_of_sq_tree[si] += ((se-ss+1)*pow(lazy_query1[si],2) + 2*lazy_query1[si]*sum_tree[si]);
                    sum_tree[si] += (se-ss+1)*lazy_query1[si];

                    // If not a leaf node propogate the value to the children
                    if (ss != se)
                    {
                        lazy_query1[si*2+1] += lazy_query1[si];
                        lazy_query1[si*2+2] += lazy_query1[si];
                        update_seq[si*2 + 1].push_back(1);
                        update_seq[si*2 + 2].push_back(1);
                    }
                    lazy_query1[si] = 0;
                }
            }
        }
        update_seq[si].clear();
    }
  
    // Disjoint case
    if (ss>se || ss>qe || se<qs)
        return 0;
  
    // Completely inside case
    if (ss>=qs && se<=qe)
        return sum_of_sq_tree[si];
  
    // Partial overlap case
    int mid = (ss + se)/2;
    return SegmentTree::getSumOfSquares(ss, mid, qs, qe, 2*si+1) + SegmentTree::getSumOfSquares(mid+1, se, qs, qe, 2*si+2);
}
  

void SegmentTree::updateRange(int si, int ss, int se, int us, int ue, int diff, int type)
{
    if(!update_seq[si].empty())
    {
        for(auto x:update_seq[si])
        {
            if(x==0)
            {
                if (lazy_query0[si] != 0)
                {
                    sum_of_sq_tree[si] = (se-ss+1)*pow(lazy_query0[si],2);
                    sum_tree[si] = (se-ss+1)*lazy_query0[si];

                    // If not a leaf node propogate the value to the children
                    if (ss != se)
                    {
                        lazy_query0[si*2 + 1] = lazy_query0[si];
                        lazy_query0[si*2 + 2] = lazy_query0[si];
                        update_seq[si*2 + 1].push_back(0);
                        update_seq[si*2 + 2].push_back(0);
                    }
                    lazy_query0[si] = 0;
                }
            }
            else
            {
                if (lazy_query1[si] != 0)
                {
                    sum_of_sq_tree[si] += ((se-ss+1)*pow(lazy_query1[si],2) + 2*lazy_query1[si]*sum_tree[si]);
                    sum_tree[si] += (se-ss+1)*lazy_query1[si];

                    // If not a leaf node propogate the value to the children
                    if (ss != se)
                    {
                        lazy_query1[si*2+1] += lazy_query1[si];
                        lazy_query1[si*2+2] += lazy_query1[si];
                        update_seq[si*2 + 1].push_back(1);
                        update_seq[si*2 + 2].push_back(1);
                    }
                    lazy_query1[si] = 0;
                }
            }
        }
        update_seq[si].clear();
    }
    
    // Disjoint case
    if (ss>se || ss>ue || se<us)
        return ;
  
    // Completely inside case
    if (ss>=us && se<=ue)
    {
        if(type==0)
        {
            sum_of_sq_tree[si] = (se-ss+1)*pow(diff,2);
            sum_tree[si] = (se-ss+1)*diff;

            if (ss != se)
            {
                lazy_query0[si*2 + 1] = diff;
                lazy_query0[si*2 + 2] = diff;
                update_seq[si*2 + 1].push_back(0);
                update_seq[si*2 + 2].push_back(0);
            }
        }
        else
        {
            sum_of_sq_tree[si] += ((se-ss+1)*pow(diff,2) + 2*diff*sum_tree[si]);
            sum_tree[si] += (se-ss+1)*diff;

            if (ss != se)
            {
                lazy_query1[si*2 + 1] += diff;
                lazy_query1[si*2 + 2] += diff;
                update_seq[si*2 + 1].push_back(1);
                update_seq[si*2 + 2].push_back(1);
            }
        }
        return;
    }
  
    // Partial overlap case
    int mid = (ss+se)/2;
    updateRange(si*2+1, ss, mid, us, ue, diff, type);
    updateRange(si*2+2, mid+1, se, us, ue, diff, type);
    
    // Updating current node
    sum_tree[si] = sum_tree[si*2 + 1] + sum_tree[si*2 + 2];
    sum_of_sq_tree[si] = sum_of_sq_tree[si*2 + 1] + sum_of_sq_tree[si*2 + 2];
}


int main()
{
    // Input
    int t;
    int num, type;
    cin >> t;
    for(int i=0; i<t; i++)
    {
        cout << "Case "<< i+1 <<":" << endl;
        int n,q;
        cin >> n >> q;
        int array[n+1];
        
        for(int i=0; i<n; i++)
            cin >> array[i];

        SegmentTree St;
        St.construct(array, 0, n-1, 0);

        for(int i=0; i<q; i++)
        {
            cin >> type;
            
            if(type==2)
            {
                int qs, qe;
                cin >> qs >> qe;
                cout << St.getSumOfSquares(0, n-1, qs-1, qe-1, 0) << endl;
            }
            else
            {
                int us, ue, diff;
                cin >> us >> ue >> diff;
                St.updateRange(0, 0, n-1, us-1, ue-1, diff, type); 
            }
            
        }
    }
}
