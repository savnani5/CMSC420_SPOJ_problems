// SPOJ username: madara_op
// Status: https://www.spoj.com/status/ARRAYSUB,madara_op/

#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

// Optimized O(n) approach

int main()
{
    int x,size,k,max;
    cin >> size;
    vector<int> A;
    deque<int> D;
    for(int i=0; i<size; i++)
    {
        cin >> x;
        A.push_back(x);
    }
    cin >> k;

    for(int i=0; i<k; i++)
    {
        while(D.empty() != true && A[D.back()] < A[i])
        {
            D.pop_back();
        }
        D.push_back(i);
    }

    for(int i=k; i<size; i++)
    {
        cout << A[D.front()] << " ";
        while(D.empty() != true && D.front() < (i-k+1))
        {
            D.pop_front();
        }
        while(D.empty() != true && A[D.back()] < A[i])
        {
            D.pop_back();
        }
        D.push_back(i);      
    }
    cout << A[D.front()];
}

// Optimized -- O(nlogk) approach

// int main()
// {
//     int x,size,k,max;
//     cin >> size;
//     vector<int> A;
//     for(int i=0; i<size; i++)
//     {
//         cin >> x;
//         A.push_back(x);
//     }
//     cin >> k;

//     priority_queue<pair<int, int>> p;
//     for(int i=0; i<k; i++)
//     {
//         p.push(make_pair(A[i], i));
//     }
//     cout << p.top().first << " ";

//     for(int i=k; i<size; i++)
//     {   
//         p.push(make_pair(A[i], i));
//         while(p.top().second < i-k+1)
//         {
//             p.pop();
//         }
//         cout << p.top().first << " ";
//     }
// }


//Brute Force -- O(n*n) approach

// int main()
// {   
//     int x,size,k,max;
//     cin >> size;
//     vector<int> A;
//     for(int i=0; i<size; i++)
//     {
//         cin >> x;
//         A.push_back(x);
//     }
//     cin >> k;

//     for(int i=0; i<size-k+1; i++)
//     {
//         max = A[i];
//         for(int j=i; j<i+k; j++)
//         {
//             if(A[j]>max)
//                 max = A[j];
//         }
//         cout << max << " ";
//     }
//     return 0;
// }
