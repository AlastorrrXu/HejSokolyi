#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include <cassert>
#include <stdexcept>

struct Node {
    char data;
    Node* next; 
    Node(char data) : data(data), next(nullptr) {} 
};

class DNAstrand {
public:
    DNAstrand(); 
    ~DNAstrand();
    void SpliceIn(const char* pattern, DNAstrand& to_splice_in);

    void push_back(char nucleotide); 
    void print() const;             

private:
    Node* head_; // 链表头节点
    Node* tail_; // 链表尾节点
    void clear(); // 清空链表
};

#endif
