#include<iostream>
#include <string>
#include<fstream>
#include <utility>

using namespace std;


class TrieNode {
public:
    char data;
    TrieNode **children;
    bool isTerminal;

    explicit TrieNode(char data) {
        this -> data = data;
        this->children = new TrieNode*[26];
        for(int i = 0; i < 26; i++) {
            this->children[i] = nullptr;
        }
        this->isTerminal = false;
    }
};

class Trie {
    TrieNode *root;

public :
    int count;

    Trie() {
        this->count = 0;
        this->root = new TrieNode('\0');
    }

    bool insertWord(TrieNode *currentNode, string word) {
        // Base case
        if(word.empty()) {
            if (!currentNode->isTerminal) {
                currentNode -> isTerminal = true;
                return true;
            } else {
                return false;
            }
        }

        // Small Calculation
        int index = word[0] - 'a';
        TrieNode *child;
        if(currentNode -> children[index] != nullptr) {
            child = currentNode -> children[index];
        }
        else {
            child = new TrieNode(word[0]);
            currentNode -> children[index] = child;
        }

        // Recursive call
        return insertWord(child, word.substr(1));
    }

    // For user
    void insertWord(string word) {
        if (insertWord(root, std::move(word))) {
            this->count++;
        }
    }

    void complete( TrieNode *currentNode, string word, const string& output, bool &possible, string &key ){
        if( word.length()==0 ){
            // Check if the node is a terminal node meaning it's the end of a word
            if( currentNode->isTerminal ){
                // This is the first word we found with the given key as a prefix
                if( !possible )
                    std::cout << "\nWords containing " << key << " as prefix are:\n";
                possible = true;
                std::cout << output << std::endl;
            }
            // Loop through all of the possible children
            for(int i=0; i<26; i++){
                // Check if the node has a child at the given position
                if(currentNode->children[i] != nullptr){
                    // Add the character at the index to the output
                    std::string output1 = output;
                    output1 += currentNode->children[i]->data;
                    // Recursive call to traverse down the trie
                    complete( currentNode->children[i], word.substr(), output1, possible, key);
                }
            }
            return;
        }
        // Calculate the index of the given word character
        int index = word[0] - 'a';
        // Check if there is a child node at the given index position
        if(currentNode->children[index] == nullptr) {
            // There is no word with the given key as a prefix
            return;
        }
        // Recursive call to traverse down the trie
        complete(currentNode->children[index], word.substr(1), output+word[0], possible, key);
    }

    void autoComplete(std::string &key, bool &possible) {
        std::string output;
        complete( root, key, output, possible, key);
    }

};

int main()
{
    Trie *t = new Trie();

    ifstream fin;
    string line;
    string path;
    cout << "Please enter the path of the word list file: ";
    cin >> path;

    fin.open(path);
    if (!fin.good())
    {
        cerr << "Error: could not open file \n";
        return 1;
    }

    while( !fin.eof() ){
        getline(fin,line);
        t->insertWord(line);
    }

    fin.close();
    bool i = true;
    while(i){
        cout<<"Enter a word to auto-complete it :\n";
        string key;
        cin>>key;
        bool possible = false;
        t->autoComplete( key, possible);

        if( !possible ){
            cout<<"\n\nNo word found with "<<key<<" as prefix\n";
            bool u = true;
            while(u){
                cout<<"Do you wish to add "<<key<<" into the dictionary? \nIf Yes, Press (1) \nIf No, Press(2)\n";
                int s;
                cin>>s;

                if( s == 1 ){
                    ofstream fout;
                    fout.open(path,ios::app);
                    fout<<"\n"<<key;
                    t->insertWord(key);
                    fout.close();
                    cout<<key<<" added to dictionary successfully.\n";
                    u = false;
                }
                else if( s == 2 )
                    u = false;
                else
                    cout<<"Please Enter a Valid Input! ENTER AGAIN\n";
            }
        }

        int x=1;
        while(x){
            cout<<"\nDo You want to auto-complete something else?\nIf Yes: Press (1) \nIf not: Press (2)\n";
            int ch;
            cin>>ch;

            if (ch==1)
                x=0;
            else if (ch==2){
                x=0;
                i = false;
            }
            else
                cout<<"Please Enter a Valid Input! ENTER AGAIN \n";
        }

    }
    return 0;

}

