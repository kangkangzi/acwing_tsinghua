#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100010  // 因为题目范围是1≤n≤105，所以设置MAX_N为100010

// 定义邻接表节点
typedef struct AdjNode {
    int vertex;              // 邻接的顶点
    struct AdjNode* next;    // 指向下一个邻接节点
} AdjNode;

// 定义图节点
typedef struct Node {
    AdjNode* adj_list;       // 邻接表头指针
    int subtree_size;        // 以该节点为根的子树大小
} Node;

Node nodes[MAX_N];          // 节点数组
int n;                      // 节点数量
int min_max_size = 0x7fffffff;  // 全局最小最大值

// 创建新的邻接表节点
AdjNode* create_adj_node(int vertex) {
    AdjNode* new_node = (AdjNode*)malloc(sizeof(AdjNode));
    new_node->vertex = vertex;
    new_node->next = NULL;
    return new_node;
}

// 添加边
void add_edge(int a, int b) {
    // 添加a到b的边
    AdjNode* new_node = create_adj_node(b);
    new_node->next = nodes[a].adj_list;
    nodes[a].adj_list = new_node;
    
    // 添加b到a的边（因为是无向图）
    new_node = create_adj_node(a);
    new_node->next = nodes[b].adj_list;
    nodes[b].adj_list = new_node;
}

// 第一次DFS：计算每个节点的子树大小
int dfs_size(int current, int parent) {
    nodes[current].subtree_size = 1;  // 包含当前节点
    
    // 遍历所有邻接节点
    AdjNode* adj = nodes[current].adj_list;
    while (adj != NULL) {
        if (adj->vertex != parent) {  // 避免访问父节点
            nodes[current].subtree_size += dfs_size(adj->vertex, current);
        }
        adj = adj->next;
    }
    
    return nodes[current].subtree_size;
}

// 第二次DFS：计算删除每个节点后的最大连通块大小
void dfs_center(int current, int parent) {
    int max_size = 0;
    int total_size = 0;
    
    // 遍历所有邻接节点
    AdjNode* adj = nodes[current].adj_list;
    while (adj != NULL) {
        if (adj->vertex != parent) {  // 避免访问父节点
            max_size = (nodes[adj->vertex].subtree_size > max_size) ? 
                      nodes[adj->vertex].subtree_size : max_size;
            total_size += nodes[adj->vertex].subtree_size;
        }
        adj = adj->next;
    }
    
    // 计算删除当前节点后的最大连通块大小
    int remaining_size = n - total_size - 1;  // 减去当前节点
    max_size = (remaining_size > max_size) ? remaining_size : max_size;
    
    // 更新全局最小值
    if (max_size < min_max_size) {
        min_max_size = max_size;
    }
    
    // 继续遍历子节点
    adj = nodes[current].adj_list;
    while (adj != NULL) {
        if (adj->vertex != parent) {
            dfs_center(adj->vertex, current);
        }
        adj = adj->next;
    }
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
    scanf("%d", &n);
    
    // 读入边并构建邻接表
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
    }
    
    // 第一次DFS：计算子树大小
    dfs_size(1, 0);  // 以1为根节点
    
    // 第二次DFS：寻找重心
    dfs_center(1, 0);
    
    // 输出结果
    printf("%d\n", min_max_size);
    
    // 释放内存
    free_graph();
    
    return 0;
}
