#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100010

// 定义邻接表节点
typedef struct AdjNode {
    int vertex;
    struct AdjNode* next;
} AdjNode;

// 定义图节点
typedef struct Node {
    AdjNode* adj_list;
} Node;

// 定义栈结构
typedef struct {
    int data[MAX_N];
    int top;
} Stack;

Node nodes[MAX_N];
int visited[MAX_N];  // 0: 未访问, 1: 正在访问, 2: 已完全访问
int n, m;
Stack stack;        // 主栈
Stack result_stack; // 结果栈

// 创建新的邻接表节点
AdjNode* create_adj_node(int vertex) {
    AdjNode* new_node = (AdjNode*)malloc(sizeof(AdjNode));
    new_node->vertex = vertex;
    new_node->next = NULL;
    return new_node;
}

// 添加边
void add_edge(int a, int b) {
    AdjNode* new_node = create_adj_node(b);
    new_node->next = nodes[a].adj_list;
    nodes[a].adj_list = new_node;
}

// 初始化栈
void init_stack(Stack* s) {
    s->top = -1;
}

// 入栈
void push(Stack* s, int value) {
    s->data[++s->top] = value;
}

// 出栈
int pop(Stack* s) {
    return s->data[s->top--];
}

// 获取栈顶元素
int peek(Stack* s) {
    return s->data[s->top];
}

// 判断栈是否为空
int is_empty(Stack* s) {
    return s->top == -1;
}

// 深度优先搜索
int dfs(int vertex) {
    // 如果节点正在访问中，说明存在环
    if (visited[vertex] == 1) {
        return 0;
    }
    
    // 如果节点已经访问完成，直接返回
    if (visited[vertex] == 2) {
        return 1;
    }
    
    // 标记节点为正在访问
    visited[vertex] = 1;
    push(&stack, vertex);
    
    // 访问所有邻接节点
    AdjNode* adj = nodes[vertex].adj_list;
    while (adj != NULL) {
        if (!dfs(adj->vertex)) {
            return 0;  // 发现环
        }
        adj = adj->next;
    }
    
    // 节点访问完成
    visited[vertex] = 2;
    pop(&stack);  // 从主栈弹出
    push(&result_stack, vertex);  // 压入结果栈
    
    return 1;
}

// 拓扑排序
int topological_sort() {
    init_stack(&stack);
    init_stack(&result_stack);
    
    // 初始化访问数组
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }
    
    // 从每个未访问的节点开始DFS
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (!dfs(i)) {
                return 0;  // 发现环
            }
        }
    }
    
    return 1;  // 成功完成拓扑排序
}

// 释放内存
void free_graph() {
    for (int i = 1; i <= n; i++) {
        AdjNode* current = nodes[i].adj_list;
        while (current != NULL) {
            AdjNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    
    // 读入边并构建邻接表
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
    }
    
    // 进行拓扑排序
    if (topological_sort()) {
        // 输出拓扑序列
        while (!is_empty(&result_stack)) {
            printf("%d", pop(&result_stack));
            if (!is_empty(&result_stack)) {
                printf(" ");
            }
        }
        printf("\n");
    } else {
        printf("-1\n");
    }
    
    // 释放内存
    free_graph();
    
    return 0;
}
