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
        int left_children;
        int right_children;
        int height;
        Node* left;
        Node* right;

        Node(long long data)
        {
            this->data=data;
            left_children=0;
            right_children=0;
            height=1;
            left=NULL;
            right=NULL;
        }
};

class AVL
{
    public:

        Node* root=NULL;
        int index_counter=1;
        
        int height(Node *p)
        {
            if (p == NULL)
                return 0;
            return p->height;
        }

        int balanceFactor(Node* p)
        {
            if (p == NULL)
                return 0;
            return AVL::height(p->right) - AVL::height(p->left); 
        }

        int max(int a, int b)
        {
            return (a > b)? a : b;
        }

        void updateHeight(Node *p)
        {
            p->height = 1 + AVL::max(AVL::height(p->left), AVL::height(p->right));
        }

        Node* rotateRight(Node* p)
        {
            Node* q = p->left;
            p->left = q->right;
            p->left_children = q->right_children;
            q->right = p;
            q->right_children = 1 + p->left_children + p->right_children;
            AVL::updateHeight(p);
            AVL::updateHeight(q);
            return q;
        }

        Node* rotateLeft(Node* p)
        {
            Node* q = p->right;
            p->right = q->left;
            p->right_children = q->left_children;
            q->left = p;
            q->left_children = 1 + p->left_children + p->right_children;
            AVL::updateHeight(p);
            AVL::updateHeight(q);
            return q;
        }

        Node* rotateLeftRight(Node* p)
        {
            p->left = AVL::rotateLeft(p->left);
            return AVL::rotateRight(p);
        }

        Node* rotateRightLeft(Node* p)
        {
            p->right = AVL::rotateRight(p->right);
            return AVL::rotateLeft(p);
        }
        
        // Rebalance
        Node* rebalance(Node* p)
        {
            if(p==NULL)
                return p;

            int balance = balanceFactor(p);
            if(balance<-1)
            {
                if(AVL::height(p->left->left) >= AVL::height(p->left->right))
                    p = AVL::rotateRight(p);
                else
                    p = AVL::rotateLeftRight(p);
            }
            else if(balance>1)
            {
                if(AVL::height(p->right->right) >= AVL::height(p->right->left))
                    p = AVL::rotateLeft(p);
                else
                    p = AVL::rotateRightLeft(p);
            }
            return p;
        }

        // Function to insert the node
        Node* insert(long long x, Node* p)
        {
            if(p==NULL)
                p = new Node(x);
            else if(x < p->data)
            {
                p->left=insert(x,p->left);
                p->left_children++;
            }
            else if(x > p->data)
            {
                p->right=insert(x,p->right);  
                p->right_children++;
            }
            else
                return p;

            AVL::updateHeight(p);
            return AVL::rebalance(p);

        }

        Node* find(long long x, Node* p)
        {
            if(p==NULL)
                return NULL;
            else if(x<p->data)
                return find(x,p->left);
            else if(x>p->data)
            {
                index_counter += (p->left_children +1);
                return find(x,p->right);
            }
            else 
            {
                index_counter += (p->left_children+1);
                return p;
            }
        }
};

int main()
{
    int n, type,ind;
    long long x;
    cin >> n;
    AVL b;
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
