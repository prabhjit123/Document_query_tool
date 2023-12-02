#include <assert.h>
#include <sstream>
#include "qna_tool.h"

using namespace std;

// class new_node{
//     public: 
//     new_node* left;
//     new_node* right;
//     int book_code;
//     int page;
//     int paragraph;
//     int sentence_no;
//     double offset;
//     new_node()
//     {
//     };
//     new_node(int b_code, int pg, int para, int s_no, float off)
//     {
//         book_code = b_code;
//         page = pg;
//         paragraph = para;
//         sentence_no = s_no;
//         offset = off;
//     };
// };


int hasher2(char s){
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

QNA_tool::QNA_tool(){
    // last_book = 0; 
    // last_page = last_para = -1;
    // d = Dict();
}

QNA_tool::~QNA_tool(){
    // Implement your function here  
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // while(last_book < book_code){
    //     scores.emplace_back();
    //     last_book++;
    //     last_page = last_para = -1;
    // }
    // while(last_page < page){
    //     scores[book_code - 1].emplace_back();
    //     last_page++;
    //     last_para = -1;
    // }
    // while(last_para < paragraph){
    //     scores[book_code - 1][page].push_back(0);
    //     last_para++;
    // }
    d.insert_sentence( book_code,page,paragraph,sentence_no,sentence);
}

long long word_count_find(string word)
{
    string filename = "unigram_freq.csv";
    string searchWord = word;
    string line;
    ifstream inputFile(filename);
    while (getline(inputFile, line)) {
        istringstream lineStream(line);
        string word;
        string countStr;
        if (std::getline(lineStream, word, ',') && std::getline(lineStream, countStr)) {
            if (word == searchWord) {
                try {
                    long long count = stoll(countStr);
                    return count;
                    break; 
                } catch (const std::invalid_argument& e) {
                    return 0;
                }
            }
        }
    }
    inputFile.close();
}

double word_score(long long my_corpus, long long general_corpus)
{
    return (double)(my_corpus+1)/(double)(general_corpus+1);
}

// vector<int> getTopK(int k) {
//     if(k>size){k=size;}
//     std::vector<int> v; int s=0;
//     for(std::vector<Account> a: bankStorage2d){
//         for(Account b: a){
//             int i= BinaryS(v, s, b.balance);
//             v.insert(v.begin()+i,b.balance);
//             if(s<k){s++;}
//             else{v.erase(v.end()-1);}
//         }
//     }
//     return v;
// }

int hashing(double a, double b, double c){
    return 0;
}

Node* QNA_tool::get_top_k_para(string question, int k_para) {
    vector <string> word_list = vector<string>();
    string word="";
    char temp;

    for(int i=0;i<question.size();i++){
        if(hasher2(question[i])==-1){
            if (word != "") {
                word_list.push_back(word); 
            }
            word="";
        }
        else{
            temp = question[i];
            if (question[i]>='A' && question[i]<='Z')
            {
                temp = temp + ('a'-'A');
            }
            word=word + temp;
        }
    }
    if(word!=""){
        word_list.push_back(word);
    }
    // query word list created till here
    int sz = word_list.size();
    vector <long long> my_corpus_score = vector<long long>(sz);
    vector <long long> general_corpus_freq = vector<long long>(sz);
    vector <double> score = vector<double>(sz);
    // cout << word_list[0] << " first element of word_list" << endl;
    // cout << word_list[1] << " second element of word_list" << endl;
    for (int i = 0; i < sz; i++)
    {
        my_corpus_score[i] = d.get_word_count(word_list[i]);
        general_corpus_freq[i] = word_count_find(word_list[i]);
        score[i] = word_score(my_corpus_score[i],general_corpus_freq[i]);
    }
    vector<int> ptr (sz, 0);
    vector<Node1*> ptr_to_words_freq(sz, nullptr);
    vector<long long> fvector_size(sz, 0);
    for(int iter = 0 ; iter < sz ; iter++){
        ptr_to_words_freq[iter] = d.dictionary->search_node(word_list[iter]);
        if(ptr_to_words_freq[iter]){
            fvector_size[iter] = ptr_to_words_freq[iter]->freq_para.size();
        }
    }

    // int capacity = 10000;
    // vector<vector<float>> score(capacity) ;
    vector<vector<double > > para_score2(540, vector<double>(80, 0));  // not to be used
    vector<vector<vector<double> > > para_scores(10, vector<vector<double> >(540, vector<double>(80, 0)));  // not to be used
    // for (int j = 0; j < 98; j++)
    //         {
    //             para_scores.push_back(vector < vector <float> >());
    //             for (int k = 0; k <600; k++)
    //             {
    //                 para_scores[j].push_back(vector <float>());
    //                 for(int l = 0; l<100; l++)
    //                 {
    //                     para_scores[j][k].push_back(0);
    //                 }
    //             }
    //         }

    heap sorter = heap();
    for(int iter = 0 ; iter < 98; iter++){ //change to 98
        for(int i = 0 ; i < sz ; i++){
            string temp_word = word_list[i];
            Node1 * t_n = ptr_to_words_freq[i];
            if(t_n == nullptr) continue;
            for(int j = ptr[i] ; j < fvector_size[i] ; j++){
                vector<long long> f = t_n->freq_para[j];
                if(f[1] > iter + 1) {
                    ptr[i] = j;
                    break;
                }          
                // this ensures that the ptr does not exceed the book which we want to check
                para_score2[f[2]][f[3]] += score[i]*(double)(f[0]);
            }
        }
        for(int i = 0 ; i < 540 ; i++){
            for(int j = 0 ; j < 80 ; j++){ //{para_score2[i][j], (float)(iter + 1), (float)i, (float)j}
                vector <double> v;
                v.push_back(para_score2[i][j]);
                v.push_back((double)(iter + 1));
                v.push_back((double)i);
                v.push_back((double)j);
                if(sorter.size < k_para){sorter.insert(v);}
                else{
                    // cout<<sorter.get_top()[0]<<endl;
                    if(para_score2[i][j]!=0 && (sorter.get_top())[0] < para_score2[i][j] ){
                        sorter.delmin();
                        sorter.insert(v);
                        
                    }   
                } 
            }
        }
        para_score2.clear();
        para_score2.resize(540, vector<double>(80, 0));
    }
    // for(int i = 0; i < sz; i++){
    //     string temp_word = word_list[i];
    //     Node1 * t_n = d.dictionary->search_node(temp_word);
    //     if(t_n == nullptr) continue;
    //     // int lj, lk, ll;
    //     for (int j = 0; j < t_n->freq_para.size(); j++ )
    //     {
    //         vector<int> f = t_n->freq_para[j];
    //         para_scores[f[1]][f[2]][f[3]] += my_corpus_score[i]*f[0];
    //         // int idx = hashing(f[1], f[2], f[3]);
    //         // for(int i = 0 ; i < score[idx].size() ; i++){
    //         //     score[idx] = 
    //         // }
            
    //     }
    // } 
    // Till here

    // sorter.insert({para_scores[0][0][0], 0, 0, 0});

    //this was used
    // for (int j = 0; j < para_scores.size(); j++ )
    // {
    //     for (int k = 0; k < para_scores[j].size(); k++)       
    //     {
    //         for(int l = 0; l < para_scores[j][k].size() ; l++)
    //         {
    //             // if( sorter.get_top()[0] < para_scores[j][k][l]){sorter.insert({para_scores[j][k][l], (float)j, (float)k, (float)l});}
    //             if(sorter.size < k_para){sorter.insert({para_scores[j][k][l], (float)j, (float)k, (float)l});}
    //             else{
    //                 // cout<<sorter.get_top()[0]<<endl;
    //                 if(para_scores[j][k][l]!=0 && (sorter.get_top())[0] < para_scores[j][k][l] ){
    //                     sorter.insert({para_scores[j][k][l], (float)j, (float)k, (float)l});
    //                     sorter.delmin();
    //                 }   
    //             } 
    //         }
    //     }
    // }

    Node* head_final = new Node();  // Assuming Node is the correct type
    Node* current = head_final;
    int count = 0;
    while (count<k_para) 
    {
        Node* temp = new Node((int)sorter.get_top()[1], (int)sorter.get_top()[2], (int)sorter.get_top()[3], 0, 0);
        double out = sorter.get_top()[0];
        //cout<<"Book number: "<<temp->book_code<<", Page number: "<<temp->page<<", Paragraph: "<<temp->paragraph<<", Score: "<<out<<endl;
        sorter.delmin();
        current->left = temp;
        temp->right = current;
        current = temp;
        count++;
    }
    head_final->left->right = nullptr;
    // current = head_final->right;
    delete head_final;

    return current;
}

void QNA_tool::query(string question, string filename){
    // Implement your function here  
    std::cout << "Q: " << question << std::endl;
    std::cout << "A: " << "Studying COL106 :)" << std::endl;
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){
    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";
    //cout << "Getting para " << book_code << " " << page << " " << paragraph << endl;
    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    std::string res = "";

    if (!inputFile.is_open()) {
        return res;
    }

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY, string question){

    // first write the k paragraphs into different files

    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();
 
    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}