#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
typedef struct Node {
    int data;           // 节点数据
    struct Node* next;  // 指向下一个节点的指针
    int insert_order;   // 记录插入顺序
} Node;

// 全局变量
Node* head = NULL;          // 链表头指针
Node** order_array;         // 按插入顺序存储节点指针的数组
int insert_count = 0;       // 插入计数器
int max_operations;         // 最大操作数

// 初始化函数
void init(int M) {
    max_operations = M;
    // 分配指针数组空间，大小为操作数（最大可能的节点数）
    order_array = (Node**)malloc(sizeof(Node*) * (M + 1));
    // 初始化指针数组
    for (int i = 0; i <= M; i++) {
        order_array[i] = NULL;
    }
}

// 在链表头部插入节点
void insert_head(int x) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = x;
    new_node->next = head;
    new_node->insert_order = ++insert_count;
    head = new_node;
    // 在指针数组中记录新节点
    order_array[insert_count] = new_node;
}

// 在第k个插入的数后插入新节点
void insert_after_k(int k, int x) {
    if (k <= 0 || k > insert_count) return;
    
    Node* k_node = order_array[k];
    if (k_node == NULL) return;
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = x;
    new_node->next = k_node->next;
    new_node->insert_order = ++insert_count;
    k_node->next = new_node;
    // 在指针数组中记录新节点
    order_array[insert_count] = new_node;
}

// 删除第k个插入的数后面的节点
void delete_after_k(int k) {
    Node* prev;
    Node* to_delete;
    
    if (k == 0) {
        // 删除头节点
        if (head == NULL) return;
        to_delete = head;
        head = head->next;
    } else {
        if (k > insert_count) return;
        prev = order_array[k];
        if (prev == NULL || prev->next == NULL) return;
        to_delete = prev->next;
        prev->next = to_delete->next;
    }
    
    // 在指针数组中将被删除节点的记录设为NULL
    order_array[to_delete->insert_order] = NULL;
    free(to_delete);
}

// 打印链表
void print_list() {
    Node* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");
}

// 清理内存
void cleanup() {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(order_array);
}

int main() {
    int M;
    scanf("%d", &M);
    init(M);
    
    char op;
    int k, x;
    
    for (int i = 0; i < M; i++) {
        scanf(" %c", &op);
        switch (op) {
            case 'H':
                scanf("%d", &x);
                insert_head(x);
                break;
            case 'D':
                scanf("%d", &k);
                delete_after_k(k);
                break;
            case 'I':
                scanf("%d %d", &k, &x);
                insert_after_k(k, x);
                break;
        }
    }
    
    print_list();
    cleanup();
    return 0;
}
