// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;


class Node1{
public:
    vector<Node1* > v;
    long long count;
    vector<vector<long long> > freq_para;
    Node1();
    ~Node1();
};

class heap{
    // vector<vector<float>> data;

public:
    // int get_size();
    vector<vector<double> > data;
    long long size;
    void insert(vector<double> key);
    void delmin();
    heap();
    void heapify_down();
    void heapify_up();
    vector<double> get_top();
};

class Trie{
public:
    Node1* root;
    Trie();
    ~Trie();
    void insert(string w);
    void insert_query(string w);
    // void insert_for_corpus(string word);
    long long search(string w);
    Node1 * search_node(string w);
    long long search_corpus(int book_code, int page, int paragraph, string w);
};

class Dict {
private:
    // You can add attributes/helper functions here

public: 
    Trie* dictionary;
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    void insert_corpus_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    long long get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/

    void query_word_count( vector<int>& count, vector<string> query, string paragraph);

    long long get_frequency(int book_code, int page, int paragraph, string word);

    vector<string> convert_vector(string sentence);

    void set_para_freq(Node1* temp, int book_code, int page, int para);

};
