#include <stdio.h>
#include <stdlib.h>

// 定义双向链表节点结构
typedef struct Node {
    int data;           // 节点数据
    struct Node* prev;  // 指向前一个节点的指针
    struct Node* next;  // 指向后一个节点的指针
    int insert_order;   // 记录插入顺序
} Node;

// 全局变量
Node* head = NULL;          // 链表头指针
Node* tail = NULL;          // 链表尾指针
Node** order_array;         // 按插入顺序存储节点指针的数组
int insert_count = 0;       // 插入计数器
int max_operations;         // 最大操作数

// 初始化函数
void init(int M) {
    max_operations = M;
    order_array = (Node**)malloc(sizeof(Node*) * (M + 1));
    for (int i = 0; i <= M; i++) {
        order_array[i] = NULL;
    }
}

// 在链表最左端插入节点
void insert_left(int x) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = x;
    new_node->prev = NULL;
    new_node->next = head;
    new_node->insert_order = ++insert_count;
    
    if (head != NULL) {
        head->prev = new_node;
    } else {
        tail = new_node;
    }
    head = new_node;
    
    order_array[insert_count] = new_node;
}

// 在链表最右端插入节点
void insert_right(int x) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = x;
    new_node->next = NULL;
    new_node->prev = tail;
    new_node->insert_order = ++insert_count;
    
    if (tail != NULL) {
        tail->next = new_node;
    } else {
        head = new_node;
    }
    tail = new_node;
    
    order_array[insert_count] = new_node;
}

// 删除第k个插入的节点
void delete_k(int k) {
    if (k <= 0 || k > insert_count) return;
    
    Node* to_delete = order_array[k];
    if (to_delete == NULL) return;
    
    if (to_delete->prev != NULL) {
        to_delete->prev->next = to_delete->next;
    } else {
        head = to_delete->next;
    }
    
    if (to_delete->next != NULL) {
        to_delete->next->prev = to_delete->prev;
    } else {
        tail = to_delete->prev;
    }
    
    order_array[k] = NULL;
    free(to_delete);
}

// 在第k个插入的数左侧插入新节点
void insert_left_of_k(int k, int x) {
    if (k <= 0 || k > insert_count) return;
    
    Node* k_node = order_array[k];
    if (k_node == NULL) return;
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = x;
    new_node->insert_order = ++insert_count;
    
    new_node->prev = k_node->prev;
    new_node->next = k_node;
    
    if (k_node->prev != NULL) {
        k_node->prev->next = new_node;
    } else {
        head = new_node;
    }
    k_node->prev = new_node;
    
    order_array[insert_count] = new_node;
}

// 在第k个插入的数右侧插入新节点
void insert_right_of_k(int k, int x) {
    if (k <= 0 || k > insert_count) return;
    
    Node* k_node = order_array[k];
    if (k_node == NULL) return;
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = x;
    new_node->insert_order = ++insert_count;
    
    new_node->next = k_node->next;
    new_node->prev = k_node;
    
    if (k_node->next != NULL) {
        k_node->next->prev = new_node;
    } else {
        tail = new_node;
    }
    k_node->next = new_node;
    
    order_array[insert_count] = new_node;
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
    
    char op[3];
    int k, x;
    
    for (int i = 0; i < M; i++) {
        scanf("%s", op);
        if (op[0] == 'L') {
            scanf("%d", &x);
            insert_left(x);
        }
        else if (op[0] == 'R' && op[1] == '\0') {
            scanf("%d", &x);
            insert_right(x);
        }
        else if (op[0] == 'D') {
            scanf("%d", &k);
            delete_k(k);
        }
        else if (op[0] == 'I' && op[1] == 'L') {
            scanf("%d %d", &k, &x);
            insert_left_of_k(k, x);
        }
        else if (op[0] == 'I' && op[1] == 'R') {
            scanf("%d %d", &k, &x);
            insert_right_of_k(k, x);
        }
    }
    
    print_list();
    cleanup();
    return 0;
}
