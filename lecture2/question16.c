#include <stdio.h>
#include <stdlib.h>

#define P 12345  // 散列表的大小

// 链表节点结构
typedef struct Node {
    int val;           // 节点值
    struct Node* next; // 下一个节点的指针
} Node;

Node* hash[P];  // 散列表，每个位置存储一个链表的头指针

// 计算哈希值
int hash_func(int x) {
    // 处理负数的情况
    return ((x % P) + P) % P;
}

// 在链表中查找值
int find(Node* head, int x) {
    Node* current = head;
    while (current != NULL) {
        if (current->val == x) {
            return 1;  // 找到了
        }
        current = current->next;
    }
    return 0;  // 没找到
}

// 在链表头部插入新节点
void insert(int x) {
    int h = hash_func(x);
    
    // 如果值已经存在，不重复插入
    if (find(hash[h], x)) {
        return;
    }
    
    // 创建新节点
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val = x;
    new_node->next = hash[h];  // 新节点指向原来的头节点
    hash[h] = new_node;        // 更新头节点
}

// 查询值是否存在
int query(int x) {
    int h = hash_func(x);
    return find(hash[h], x);
}

// 释放链表内存
void free_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    // 初始化散列表
    for (int i = 0; i < P; i++) {
        hash[i] = NULL;
    }
    
    // 处理操作
    while (n--) {
        char op[2];
        int x;
        scanf("%s%d", op, &x);
        
        if (op[0] == 'I') {  // 插入操作
            insert(x);
        } else {  // 查询操作
            if (query(x)) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        }
    }
    
    // 释放内存
    for (int i = 0; i < P; i++) {
        free_list(hash[i]);
    }
    
    return 0;
}
