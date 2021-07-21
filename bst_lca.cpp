#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

class Node
{
    public:
        int data;
        Node* left;
        Node* right;

        Node(int data)
        {
            this->data=data;
            left=NULL;
            right=NULL;
        }
};

class BT 
{
    public:

        Node* root=NULL;
        int flag=0;
        vector<int> path;

        Node* find(int key, Node* p)
        {
            if(p==NULL)
                return NULL;
            if(p->data == key)
            {   
                flag=1;
                path.push_back(p->data);
                return p;
            }
            Node* res1 = find(key, p->left);
            if(res1)
            {
                if(flag==1)
                    path.push_back(p->data);
                return res1;
            }
            Node* res2 = find(key, p->right);
            if(flag==1)
                path.push_back(p->data);
            return res2;
        } 

        int find_lca_bt (int a, int b, Node* p) 
        {
            Node* alpha = BT::find(a, p);
            vector<int> path_a = BT::path;
            BT::path.clear();
            Node* beta = BT::find(b,p);
            vector<int> path_b = BT::path;
            
            auto itA = path_a.rbegin();
            auto itB = path_b.rbegin();
            int prev;
            while(itA != path_a.rend() || itB != path_b.rend())
            {
                if(*itA!=*itB)
                    return prev;

                prev = *itA;
                itA++;
                itB++;
            }
            return -1;
        }
};

class BST
{
    public:

        Node* root=NULL;
        
        // Function to insert the node
        Node* insert(int x, Node* p)
        {
            if(p==NULL)
                p = new Node(x);
            else if(x < p->data)
                p->left=insert(x,p->left);
            else if(x > p->data)
                p->right=insert(x,p->right);
            return p;
        }

        Node* find(int x, Node* p)
        {
            if(p==NULL)
                return NULL;
            else if(x<p->data)
                return find(x,p->left);
            else if(x>p->data)
                return find(x,p->right);
            else 
                return p;
        }

        int find_lca_bst(int a, int b, Node* p)
        {
            if(p==NULL)
                return -1;
            else if(a<p->data && b<p->data)
                return find_lca_bst(a,b,p->left);
            else if(a>p->data && b>p->data)
                return find_lca_bst(a,b,p->right);
            else 
                return p->data;
        }
};

int main()
{
    // BT b;
    BST b;
    b.root = new Node(8);
    b.root->left = new Node(3);
    b.root->left->left = new Node(1);
    b.root->left->right = new Node(6);
    b.root->left->right->left = new Node(4);
    b.root->left->right->right = new Node(7);
    b.root->right = new Node(10);
    b.root->right->right = new Node(14);
    b.root->right->right->left = new Node(13);

    // int ans = b.find_lca_bt(13,7,b.root);
    int ans = b.find_lca_bst(1,3,b.root);
    cout << ans;
}