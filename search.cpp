// Do NOT add any other includes
#include "search.h"

int get_index_alphabets(char ch)
{
    return static_cast<int>(ch);
}

SearchEngine::SearchEngine(){
    
}

SearchEngine::~SearchEngine(){
    // Implement your function here  
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    char temp = sentence[0];
    if (temp >= 'A' && temp <= 'Z') {
            temp = temp + 32;
    }
    Node_new * root = new Node_new(book_code,page,paragraph,sentence_no,0);
    root->ch = temp;
    Node_new * temp_ptr = root;

    int index = get_index_alphabets(temp);
    baseline[index].push_back(temp_ptr);
    for (int i = 1; i <sentence.size(); i++)
    {
        temp = sentence[i];
        if (temp >= 'A' && temp <= 'Z') {
            temp = temp + 32;
        }
        Node_new * temp_node = new Node_new(book_code,page,paragraph,sentence_no,i);
        temp_node->ch = temp;
        temp_ptr->next = temp_node;
        temp_ptr = temp_ptr->next;
        index = get_index_alphabets(temp);
        baseline[index].push_back(temp_ptr);
    }
    return;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    char ch = pattern[0];
    if (ch >= 'A' && ch <= 'Z') {
            ch = ch + 32;
    }
    int index = get_index_alphabets(ch);
    vector <Node_new*> final;           // hello world! --> lo wor
    int i = 0;
    if (baseline[index].size()==0)
    {
        return NULL;
    }
    Node_new * start = baseline[index][i];
    while (i<baseline[index].size())
    {
        start = baseline[index][i];
        int counter = 0;
        Node_new * temp_ptr = baseline[index][i];
        char new_temp = pattern[counter];
        while (temp_ptr != NULL)
        {
            new_temp = pattern[counter];
            if (new_temp >= 'A' && new_temp <= 'Z') {
            new_temp = new_temp + 32;
            }
            if ( new_temp == temp_ptr->ch)
            {
                counter++;
                temp_ptr = temp_ptr->next;
                if (counter > pattern.size()-1)
                {
                    final.push_back(start);
                    n_matches++;
                    break;
                }
            }
            else
            {
                break;
            }
        }
    i++;
    }
    for (int i = 1; i <final.size(); i++)
    {
        final[i-1]->right = final[i];
        final[i]->left = final[i-1];
    }
    vector <Node*> finally;
    if (final.size()!=0)
    {
        for (int i = 0; i<final.size(); i++)
        {
            Node * temp = new Node(final[i]->book_code,final[i]->page,final[i]->paragraph,final[i]->sentence_no,final[i]->offset);
            finally.push_back(temp);
            if (finally.size()!=1)
            {
            finally[finally.size()-1]->left = finally[finally.size()-2];
            finally[finally.size()-2]->right = finally[finally.size()-1];
            }
        };
        return finally[0];
    }
    else
    {
        return NULL;
    }
}

void printBaseline(const std::vector<std::vector<Node_new*> >& baseline) {
    for (int i = 0; i < baseline.size(); i++) {
        std::cout << "Index " << i << ": ";
        for (Node_new* node : baseline[i]) {
            std::cout << "(" << node->book_code << "," << node->page << "," << node->paragraph << "," << node->sentence_no << "," << node->offset << "," << node->ch << ") ";
        }
        std::cout << std::endl;
    }
}

void display_linked_list(Node *n) {
    if (n == nullptr) {cout << "empty linked list" << endl;}
    Node *current = n;
    while (current != nullptr) 
    {cout << current->book_code << " " << current->page << " " << current->paragraph << " " << current->sentence_no << " " << current->offset;
    current = current ->right; cout << endl;}
    //cout << endl;
}
