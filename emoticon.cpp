// SPOJ username: madara_op
// Status: https://www.spoj.com/status/EMOTICON,madara_op/

#include <bits/stdc++.h>
#include <iostream>
#include <string>

using namespace std;

const int SIZE = 95;
 
// Trie node
class Node
{
    public: 
        Node *children[SIZE];
        bool isEndOfWord;                           
       
        Node(){
            for(int i = 0; i < SIZE; i++)
                children[i] = NULL;
            isEndOfWord = false;
        }
};

class Trie
{ 
    public:
        Node *root = NULL;
        int emoCounter=0;
        void insert(string key);
        int emoCount(string key);
};
 

void Trie::insert(string key)
{
    Node *pCrawl = Trie::root;
 
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - ' ';
        if (!pCrawl->children[index])
            pCrawl->children[index] = new Node();

        pCrawl = pCrawl->children[index];
    } 
    
    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}
 
//  No. of smallest(base) emoticons inside a bigger one
int Trie::emoCount(string key)
{
    Node *pCrawl = root;
    static int emo_size = 0;
    static int end_ind = 0;
    int i=0, start_ind=0, no_of_emoticons=0;
    string new_key;

    while(key[i]!='\0')
    {       
        int index = key[i] - ' ';

        if(pCrawl->children[index])
        {  
            if(new_key == "") 
                start_ind = i;

            new_key = new_key + key[i];
            pCrawl = pCrawl->children[index];
        }
        else
        {
            pCrawl = root;
            
            // Correction of variable i
            if(new_key != "")
            {
                while(i != start_ind)
                {
                    i--;
                }
            }
            new_key = "";
        }

        if(pCrawl->isEndOfWord == true)
        {
            // Check for number of emoticons in the substring
            int c = emoCount(new_key.substr(1,new_key.length())); 
            no_of_emoticons +=c;
            if(c==0)
            {
                no_of_emoticons++;
                emo_size = new_key.length();
                end_ind = start_ind + emo_size -1;
            }
            else 
                end_ind = start_ind + end_ind +1;
            
            // Condition for correction of overlapping emoticons
             
            while(i != end_ind)
            {
                i--;
            }

            pCrawl = root;
            new_key = "";
        }  

        // Increment i
        i++;      
    }
    return no_of_emoticons; 
}

int main()
{
    // Trie t;
    // t.root = new Node();

    // // int n=1,q=0;
    // // string keys[n] = {"aa"}; 
    // // string queries[q] = {};

    // // int n=2,q=2;
    // // string keys[n] = {"aabe", "ab"}; 
    // // string queries[q] = {"aabes", "abaabs"};

    // // int n=3,q=1;
    // // string keys[n] = {"a", "aa", "aaa"}; 
    // // string queries[q] = {"aaaaaa"};

    // int n=6,q=1;
    // string keys[n] = {"Aabcd", "abc", "cdd$", "d$#", "d$", "$"}; 
    // string queries[q] = {"-Aabcdd$# --"};

    // // int n=4, q=1;
    // // string keys[n] = {"!-",":?", "-))", "y-~!-"};
    // // string queries[q] = {"! y-~!-)):?"}; 

    // // int n=10,q=1;
    // // string keys[n] = {"--","y-~!", "-~", "-~$", "yy-~!-", "-yy-~!-~$--", ":-)", ":-(", "(-:", ")-:"}; 
    // // string queries[q] = {"! -yy-~!-~$-:-)!? :-D"};

    // // int n=4, q=6;
    // // string keys[n] = {":-)", ":-(", "(-:", ")-:"}; 
    // // string queries[q] = {"Hello uncle John! :-) :-D", "I am sad or happy? (-:-(?","I feel so happy, my head spins","(-:-)(-:-)(-:-)(-:-) :-) (-: :-)","but then sadness comes :-(","Loves you, Joanna :-)))))}"}; 


    // for(int i=0; i<n; i++)
    //     t.insert(keys[i]);
    
    // for(int i=0; i<q; i++)
    // {
    //     t.emoCounter += t.emoCount(queries[i]);
    // }

    // cout << t.emoCounter << endl;
    // return 0;

    while(1)
    {    
        Trie t;
        t.root = new Node();

        int n,q;
        cin >> n >> q;
        if(n==0 && q==0)
            break;
        string dummy, s; 

        // Dummy input for new line character
        getline(cin, dummy);
        
        for(int i=0; i<n; i++)
        {
            getline(cin, s);
            t.insert(s);
        }
        
        for(int i=0; i<q; i++)
        {
            getline(cin, s);
            t.emoCounter += t.emoCount(s);     
        }
        cout << t.emoCounter << endl;
        t.emoCounter=0;
    }  
}
