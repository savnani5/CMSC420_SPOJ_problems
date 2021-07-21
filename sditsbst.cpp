// SPOJ username: madara_op
// Status : https://www.spoj.com/status/madara_op/

#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

class Node
{
    public:
        long long data;
        int right_children;
        Node* left;
        Node* right;

        Node(long long data)
        {
            this->data=data;
            right_children=0;
            left=NULL;
            right=NULL;
        }
};

class BST
{
    public:

        Node* root=NULL;
        int index_counter=0;
        
        // Function to insert the node
        Node* insert(long long x, Node* p)
        {
            if(p==NULL)
                p = new Node(x);
            else if(x < p->data)
                p->left=insert(x,p->left);
            else if(x > p->data)
            {
                p->right=insert(x,p->right);
                p->right_children++;
            }
            return p;
        }

        Node* find(long long x, Node* p)
        {
            if(p==NULL)
                return NULL;
            else if(x<p->data)
            {
                index_counter += (p->right_children +1);
                return find(x,p->left);
            }
            else if(x>p->data)
                return find(x,p->right);
            else 
            {
                index_counter += (p->right_children+1);
                return p;
            }
        }
};

int main()
{
    int n, type,ind;
    long long x;
    cin >> n;
    BST b;
    vector<pair<int,long long>> v;
    for(int i=0; i<n; i++)
    {
        cin >> type >> x;
        v.push_back(make_pair(type,x));
    }
    for(auto q:v)
    {
        if(q.first==1)
            b.root = b.insert(q.second, b.root);
        else
        {
            b.index_counter=0;
            Node* t = b.find(q.second, b.root);
            if(t)
                cout << b.index_counter << endl;
            else
                cout << "Data tidak ada" << endl;
        }
    }
    return 0;
}


// class Node
// {
//     public:
//         long long data;
//         Node* left;
//         Node* right;

//         Node(long long data)
//         {
//             this->data=data;
//             left=NULL;
//             right=NULL;
//         }
// };

// class BST
// {
//     public:

//         Node* root=NULL;
//         int index;
        
//         // Function to insert the node
//         Node* insert(long long x, Node* p)
//         {
//             if(p==NULL)
//                 p = new Node(x);
//             else if(x < p->data)
//                 p->left=insert(x,p->left);
//             else if(x > p->data)
//                 p->right=insert(x,p->right);
//             return p;
//         }

//         bool CheckElement(long long x, Node* p)
//         {
//             if(p==NULL)
//                 return false;
//             else if(x<p->data)
//                 return CheckElement(x,p->left);
//             else if(x>p->data)
//                 return CheckElement(x,p->right);
//             else 
//                 return true;
//         }

//         // Inorder traversal in decreasing order
//         void find(long long x, Node* p)
//         {
//             if(p==NULL || (p->data==x && p->right==NULL))
//                 return;
//             find(x, p->right);
//             if(p->data<=x)
//                 return;
//             index++;
//             if(p->data >x)
//                 find(x,p->left);
//         }
// };

// int main()
// {
//     int n, type,ind;
//     long long x;
//     cin >> n;
//     BST b;
//     vector<pair<int,long long>> v;
//     for(int i=0; i<n; i++)
//     {
//         cin >> type >> x;
//         v.push_back(make_pair(type,x));
//     }
//     for(auto q:v)
//     {
//         if(q.first==1)
//             b.root = b.insert(q.second, b.root);
//         else
//         {
//             if(b.CheckElement(q.second, b.root))
//             {
//                 b.index=1;
//                 b.find(q.second, b.root);
//                 cout << b.index << endl;
//             }
//             else
//                 cout << "Data tidak ada" << endl;
//         }
//     }
//     return 0;
// }
