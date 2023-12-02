// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

//So we essentially have to maintain a list of characters a,b,c,.... 

class Node_new{
    public:
    Node_new* left;
    Node_new* right;

    int book_code;
    int page;
    int paragraph;
    int sentence_no;
    int offset;
    char ch;
    Node_new * next;
    Node_new(){
    
    };
    Node_new(int b_code, int pg, int para, int s_no, int off){
    book_code = b_code;
    page = pg;
    paragraph = para;
    sentence_no = s_no;
    offset = off;
    next = NULL;
    };

};

class SearchEngine {
private:
    vector < vector <Node_new*> > baseline = vector < vector <Node_new *> >(130);
public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
    vector < vector <Node_new *> > get_base()
    {
        return baseline;
    }
};