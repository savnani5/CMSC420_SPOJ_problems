// SPOJ username: madara_op
// Status: https://www.spoj.com/status/ADAINDEX,madara_op/

#include <bits/stdc++.h>
#include <iostream>
#include <string>
using namespace std;
 
const int ALPHABET_SIZE = 26;
 
// Trie node
class Node
{
    public:
        Node *children[ALPHABET_SIZE];
        bool isEndOfWord;                              
        int copies;
        Node(){
            for(int i = 0; i < ALPHABET_SIZE; i++)
                children[i] = NULL;
            isEndOfWord = false;
            copies = 0;
        }
};

class Trie
{
    public:
        Node *root = NULL;
        void insert(string key);
        int prefixCount(string key);
};
 

void Trie::insert(string key)
{
    Node *pCrawl = Trie::root;
 
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = new Node();

        pCrawl = pCrawl->children[index];
        pCrawl->copies++;
    }
    
    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}
 

int Trie::prefixCount(string key)
{
    Node *pCrawl = root;
    int i;
    for (i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return 0;
 
        pCrawl = pCrawl->children[index];
    }
    if(key[i] == '\0')
        pCrawl->isEndOfWord = true;
    
    if(!pCrawl->isEndOfWord)
        return 0;
    else
        return (pCrawl->copies);
}

int main()
{
    Trie t;
    t.root = new Node();
    int n=12,q=6;
    cin >> n >> q;
    string s, keys[n], queries[q]; 
    for(int i=0; i<n; i++)
    {
        cin >> s;
        keys[i] = s;
    }
    for(int i=0; i<q; i++)
    {
        cin >> s;
        queries[i] = s;
    }

    for (int i = 0; i < n; i++)
        t.insert(keys[i]);
    
    for(int i=0; i<q; i++)
        cout << t.prefixCount(queries[i]) << endl;
    return 0;
}