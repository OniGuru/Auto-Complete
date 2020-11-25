#include<bits/stdc++.h>
#include <string>
#include<iostream>
#include <vector>
using namespace std;
class TrieNode {
	public :
	char data;
	TrieNode **children;
	bool isTerminal;

	TrieNode(char data) {
		this -> data = data;
		children = new TrieNode*[26];
		for(int i = 0; i < 26; i++) {
			children[i] = NULL;
		}
		isTerminal = false;
	}
};

class Trie {
	TrieNode *root;

	public :
	int count;

	Trie() {
		this->count = 0;
		root = new TrieNode('\0');
	}

	bool insertWord(TrieNode *root, string word) {
		// Base case
		if(word.size() == 0) {
			if (!root->isTerminal) {
				root -> isTerminal = true;
				return true;
			} else {
				return false;
			}
		}

		// Small Calculation
		int index = word[0] - 'a';
		TrieNode *child;
		if(root -> children[index] != NULL) {
			child = root -> children[index];
		}
		else {
			child = new TrieNode(word[0]);
			root -> children[index] = child;
		}

		// Recursive call
		return insertWord(child, word.substr(1));
	}

	// For user
	void insertWord(string word) {
		if (insertWord(root, word)) {
			this->count++;
		}
	}
    void complete( TrieNode *root, string word, string output ){
        if( word.length()==0 ){
        	if( root->isTerminal )
                cout<<output<<endl;
            for(int i=0; i<26; i++){
            	if( root->children[i]!=NULL ){
                    string output1 = output;
            	    output1 += root->children[i]->data;
            	    complete( root->children[i], word.substr(), output1);
        	    }
        	}
            return;
        }
        int index = word[0] - 'a';
        if( root->children[index]==NULL )
            return;
        else
            complete(root->children[index], word.substr(1), output+word[0]);
    }

    void autoComplete(string key) {
        string output = "";
        complete( root, key, output);
    }

};

int main()
{
    Trie *t = new Trie();

    ifstream fin;
    string line;
	fin.open("wordlist.txt");

	while( !fin.eof() ){

	   getline(fin,line);
	   t->insertWord(line);

	}

	fin.close();

    cout<<"Enter a word to auto-complete it :\n";
    string key;
    cin>>key;
    cout<<"\nWords containing "<<key<<" as prefix are:\n";
    t->autoComplete(key);
}

