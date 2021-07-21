// C++ implementation of search and insert
// operations on Trie
#include <bits/stdc++.h>
#include <string>
#include <cstring>

using namespace std;
const int ALPHABET_SIZE = 27;  // 26 alphabets + 1 '$' character
 
// PatriciaNode
struct PatriciaNode
{
    struct PatriciaNode *children[ALPHABET_SIZE];
    string substr[ALPHABET_SIZE];
    int child_count;

    PatriciaNode(){
        for(int i=0 ; i<ALPHABET_SIZE; i++)
        {
            children[i] = NULL;
            substr[i] = "";
            child_count = 0;
        }
    }
};
 
struct PatriciaNode *insert(struct PatriciaNode *root, string s, int index)
{
    if(index >= s.length())
        return NULL;
    else if(root==NULL)
    {
        root = new PatriciaNode();
        if(s=="{")
            root->substr[s[index]-'a'] = "{";
        else
            root->substr[s[index]-'a'] = s.substr(index, s.length()) + "{";
        root->child_count++;
        return root;
    }
    else
    {
        if(root->substr[s[index]-'a'] == "")
        {
            if(s=="{")
                root->substr[s[index]-'a'] = "{";
            else
                root->substr[s[index]-'a'] = s.substr(index, s.length()) + "{";
            root->child_count++;
        }
        else
        {
            int i;
            string org = root->substr[s[index]-'a'];
            if(org[org.length()-1] == '{')
                org = org.substr(0, org.length()-1);

            for(i=0; org[i]!='\0' && s[i]!='\0'; i++)
            {
                if(org[i] != s[i])
                {    
                    struct PatriciaNode *t = insert(NULL, org, i);
                    t = insert(t, s, i);
                    root->children[s[index]-'a'] = t;
                    root->substr[s[index]-'a'] = s.substr(0, i);
                    return root;
                }            
            }
            if(org[i]=='\0' && s[i] == '\0')
                root->children[s[index]-'a'] = insert(root->children[s[index]-'a'], "{", 0);
            else if(org[i]!='\0' && s[i] == '\0')
            {
                struct PatriciaNode *t = insert(NULL, "{", 0);
                t = insert(t, org, i);
                t->children[s[i]-'a'] = root->children[s[index]-'a'];
                root->children[s[index]-'a'] = t;
                root->substr[s[index]-'a'] = s.substr(0, i);
            }
            else
            {
                string new_s = s.substr(i, s.length());
                root->children[s[index]-'a'] = insert(root->children[s[index]-'a'], new_s, 0);
            }
        }   
        return root;
    }
}
 
// Returns true if s presents in trie, else
// false 
bool find_prefix(struct PatriciaNode *root, string s, int index)
{
    if(index >= s.length())
        return true;
    else if(root==NULL)
        return false;
    else
    {
        if(root->substr[s[index]-'a'] == "")
            return false;
        else
        {
            int i;
            string org = root->substr[s[index]-'a'];
            for(i=0; org[i]!='\0';i++)
            {
                if(s[i]=='\0')
                    return true;
                if(org[i]!=s[i])
                    return false;
            }
            return find_prefix(root->children[s[index]-'a'], s.substr(i,s.length()), 0);
        }
    }
}   
 
// Driver
int main()
{
    // Input keys (use only 'a' through 'z'
    // and lower case)
    string keys[] = {"essence", "sublease", "estimate",
                    "essential", "es", "e", "estimation" };
    // string keys[] = {"catastroph", "catastroph"};
    int n = sizeof(keys)/sizeof(keys[0]);
    
    struct PatriciaNode* root = new PatriciaNode();
    
    // Construct trie
    for (int i = 0; i < n; i++)
        root = insert(root, keys[i], 0);
 
    // // Search for different keys
    find_prefix(root, "es", 0)? cout << "Yes\n" :
                         cout << "No\n";
   
    find_prefix(root, "est", 0)? cout << "Yes\n" :
                           cout << "No\n";
    
    find_prefix(root, "sublent", 0)? cout << "Yes\n" :
    cout << "No\n";
    return 0;
}