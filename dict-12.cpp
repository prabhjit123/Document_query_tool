// Do NOT add any other includes
#include "dict.h"

Node1 :: Node1(){
    v.resize(55, nullptr);
    count = 0;
    // page_last = para_last = -1;
    // book_last = 0;
};

Node1 :: ~Node1(){}

int hasher(char s){
    int out = s;
    if(out >= 35 && out <= 38){
        out -= 35;
    }
    else if(out == 42 || out == 43){
        out -= 38;
    }
    else if(out >= 47 && out <= 57){
        out -= 41;
    }
    else if(out >= 60 && out <= 62){
        out -= 43;
    }
    else if((out >= 65 && out <= 90)){
        out -= 45;
    }
    else if((out >= 97 && out <= 122)){
        out -= 77;
    }
    else if( out == 92){
        out = 46;
    }
    else if((out ==94 || out == 95)){
        out -= 47;
    }
    else if((out >= 123 && out <= 126)){
        out -= 74;
    }
    else if(out == 96){
        out = 53;
    }
    else{
        out = -1;
    }
    return out;
}

Trie :: Trie() {
    root = new Node1();
};

long long Trie :: search(string word) {
    Node1* temp = root;
    for (char s : word){
        if(temp->v[hasher(s)] == nullptr){
            return 0;
        }
        temp = temp->v[hasher(s)];
    }
    return temp->count;
};

Node1 * Trie :: search_node(string word) {
    Node1* temp = root;
    for (char s : word){
        if( temp->v[hasher(s)] == nullptr){
            return nullptr;
        }
        temp = temp->v[hasher(s)];
    }
    return temp;
};

// int Trie :: search_corpus(int book_code, int page, int paragraph, string word) {
//     Node1* temp = root;
//     for (char s : word){
//         if( temp->v[hasher(s)] == nullptr){
//             return 0;
//         }
//         temp = temp->v[hasher(s)];
//     }
//     return temp->freq_para[book_code - 1][page][paragraph];
// };

void destr(Node1* a){
    if(a == nullptr){return ;}
    for(auto s : a->v){
        delete s;
    }
    a->v.clear();
    delete a;
}

Trie :: ~Trie() {
    destr(root);
};

Dict::Dict(){    
    dictionary = new Trie();
}

Dict::~Dict(){    
    delete dictionary;
}

void Dict:: set_para_freq(Node1* temp, int book_code, int page, int para){
    vector <long long> v;
        v.push_back(1);
        v.push_back(book_code);
        v.push_back(page);
        v.push_back(para);
    if((temp->freq_para).empty()){temp->freq_para.push_back(v); return;}
    vector<long long> t = temp->freq_para.back();
    if( t[1] == book_code && t[2] == page && t[3] == para){
        t[0]++;
        temp->freq_para.pop_back();
        temp->freq_para.push_back(t);
    }
    else{
        vector <long long> v;
        v.push_back(1);
        v.push_back(book_code);
        v.push_back(page);
        v.push_back(para);
        temp->freq_para.push_back(v);
    }
};


void Dict::insert_sentence( int book_code, int page, int paragraph, int sentence_no, string sentence){  
    // string separator = " .,-:!\'\"()?—[]“”‘’˙;@";
    Node1* temp = dictionary->root;
    for(char s : sentence){
        int idx = hasher(s);
        if(idx == -1){
            if(temp == dictionary->root){continue;}
            temp->count ++;
            set_para_freq(temp, book_code, page, paragraph);
            temp = dictionary->root;
            continue;
        }
        if(temp->v[idx] == nullptr){
            temp->v[idx] = new Node1();
        }
        temp = temp->v[idx];
    }
    if(temp!=dictionary->root){
        temp->count++;
        // cout<< book_code << " " << page << " " << paragraph << endl;
        set_para_freq(temp, book_code, page, paragraph);
    }
    return;
}

long long Dict::get_word_count(string word){  
    return dictionary->search(word);
}

// int Dict :: get_frequency(int book_code, int page, int paragraph, string word){
//     return dictionary->search_corpus( book_code,  page,  paragraph,  word);
// }

// void swap(int& a, int& b){
//     int c=a;
//     a=b;
//     b=c;
// }

// int min(int a, int b){
//     if(a>b){return b;}
//     else{return a;}
// }

heap::heap(){
    // data = new int[100001];
    size=0;
}

void heap::heapify_up(){
    int parent, child=size-1;
	parent = (child-1)/2;

    while ((child > 0) && (data[parent][0] > data[child][0])) {
        swap(data[parent], data[child]);
        child = parent;
        parent = (child - 1) / 2;
    }
}

void heap::insert( vector<double> key){
	data.push_back(key);
    size++;
	heapify_up();
};

void heap::heapify_down(){
    int parent=0, c1=2*parent + 1, c2=2*parent + 2;
    while(c2<size ){
        double m= min(data[c1][0], data[c2][0]);
        if(data[parent][0] > m){
            if(m==data[c1][0]){swap(data[parent], data[c1]); parent = c1;}
            else{swap(data[parent], data[c2]); parent = c2;}
        }
        else{break;}
        c1 = 2*parent + 1;
        c2 = 2*parent + 2;
    }
    if(c1==size - 1){
        if(data[parent][0] > data[c1][0]){swap(data[parent], data[c1]);}
    }
}

void heap::delmin(){
    if(size==0){
        return ;
    }
    vector<double> r = data[0];
    data[0] = data[--size];
    data.pop_back();
    heapify_down();
    // return r[0];
};


vector<double> heap::get_top() {
    // if(size == 0){return {-12345.3};}
    // cout<<data.size()<<" "<< size <<endl;

    vector<double> v(data[0].begin(), data[0].end());
    return v;
}

// to do - query word count change krna h
// have to split the words based