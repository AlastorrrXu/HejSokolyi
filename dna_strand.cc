#include "dna_strand.hpp"

DNAstrand::DNAstrand() : head_(nullptr), tail_(nullptr) {}

DNAstrand::~DNAstrand() {
    clear();
}
void DNAstrand::clear() {
    Node* current = head_;
    while (current) {
        Node* to_delete = current;
        current = current->next;
        delete to_delete;
    }
    head_ = nullptr;
    tail_ = nullptr;
}

void DNAstrand::push_back(char nucleotide) {
    Node* new_node = new Node(nucleotide);
    if (!head_) { // 如果链表为空，直接设置头尾节点
        head_ = tail_ = new_node;
    } else { // 如果链表非空，将新节点连接到尾部
        tail_->next = new_node;
        tail_ = new_node; // 更新尾指针
    }
}

void DNAstrand::print() const {
    Node* current = head_;
    while (current) {
        // 输出每个节点的数据
        current = current->next;
    }
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
    if (!pattern || !*pattern || &to_splice_in == this) {
        return; // 空模式或自引用，直接返回
    }

    Node* previous_node = nullptr;  // 记录当前节点的前一个节点
    Node* current_node = head_;    // 遍历链表的当前节点
    Node* last_match_start = nullptr; // 记录最后一次匹配的起始节点
    Node* last_match_prev = nullptr;  // 记录最后一次匹配起始节点的前一个节点

    // 遍历链表，寻找最后一次匹配
    while (current_node) {
        Node* temp = current_node;
        const char* p = pattern;

        // 检查从当前节点开始是否匹配模式
        while (temp && *p && temp->data == *p) {
            temp = temp->next;
            ++p;
        }

        // 如果完全匹配，记录当前位置
        if (!*p) {
            last_match_prev = previous_node;
            last_match_start = current_node;
        }

        previous_node = current_node;
        current_node = current_node->next;
    }

    // 如果找不到匹配，抛出异常
    if (!last_match_start) {
        throw std::runtime_error("Pattern not found");
    }

    // 删除匹配的部分
    Node* match_end = last_match_start;
    for (const char* p = pattern; *p && match_end; ++p) {
        Node* to_delete = match_end;
        match_end = match_end->next;
        delete to_delete;
    }

    if (last_match_prev) {
        last_match_prev->next = match_end; // 更新上一节点的 next 指针
    } else {
        head_ = match_end; // 如果匹配从头开始，更新头节点
    }

    if (!match_end) {
        tail_ = last_match_prev; // 如果匹配到链表尾部，更新尾节点
    }

    // 拼接 to_splice_in 的节点
    if (to_splice_in.head_) {
        if (last_match_prev) {
            last_match_prev->next = to_splice_in.head_;
        } else {
            head_ = to_splice_in.head_; // 如果从头开始拼接，更新头节点
        }

        if (to_splice_in.tail_) {
            to_splice_in.tail_->next = match_end; // 拼接尾节点到剩余链表
        } else {
            tail_ = match_end; // 拼接链表为空时，更新尾节点
        }
    }
    to_splice_in.head_ = nullptr;
    to_splice_in.tail_ = nullptr;
}
