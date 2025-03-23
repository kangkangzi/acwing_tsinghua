#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100010
#define MAX_M 100010

// 定义邻接表节点
typedef struct AdjNode {
    int vertex;
    struct AdjNode* next;
} AdjNode;

// 定义图节点
typedef struct Node {
    AdjNode* adj_list;
} Node;

Node nodes[MAX_N];      // 邻接表
int color[MAX_N];       // 颜色数组：0表示未访问，1和2表示两种不同颜色
int n, m;              // 节点数量和边数量

// 创建新的邻接表节点
AdjNode* create_adj_node(int vertex) {
    AdjNode* new_node = (AdjNode*)malloc(sizeof(AdjNode));
    new_node->vertex = vertex;
    new_node->next = NULL;
    return new_node;
}

// 添加边（无向图需要添加两条边）
void add_edge(int a, int b) {
    AdjNode* new_node1 = create_adj_node(b);
    new_node1->next = nodes[a].adj_list;
    nodes[a].adj_list = new_node1;
    
    AdjNode* new_node2 = create_adj_node(a);
    new_node2->next = nodes[b].adj_list;
    nodes[b].adj_list = new_node2;
}

// DFS染色函数
// 返回1表示当前子图可以构成二分图，返回0表示不能构成二分图
int dfs(int node, int c) {
    color[node] = c;  // 给当前节点染色
    
    // 遍历所有邻接节点
    AdjNode* adj = nodes[node].adj_list;
    while (adj != NULL) {
        int next_vertex = adj->vertex;
        
        if (color[next_vertex] == 0) {
            // 如果邻接节点未被访问，则用另一种颜色染色
            if (!dfs(next_vertex, 3 - c)) {  // 3-c在1和2之间交替
                return 0;  // 如果子图不能构成二分图，返回0
            }
        } else if (color[next_vertex] == c) {
            // 如果邻接节点已被访问且颜色相同，则不是二分图
            return 0;
        }
        
        adj = adj->next;
    }
    
    return 1;  // 当前子图可以构成二分图
}

// 判断是否是二分图
int is_bipartite() {
    // 初始化颜色数组
    memset(color, 0, sizeof(color));
    
    // 处理可能的多个连通分量
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {  // 如果节点未被访问
            if (!dfs(i, 1)) {  // 从颜色1开始染色
                return 0;  // 如果任何一个连通分量不是二分图，整个图就不是二分图
            }
        }
    }
    
    return 1;  // 所有连通分量都是二分图
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
    
    // 初始化邻接表
    for (int i = 1; i <= n; i++) {
        nodes[i].adj_list = NULL;
    }
    
    // 读入边并构建邻接表
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
    }
    
    // 判断是否是二分图
    if (is_bipartite()) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    // 释放内存
    free_graph();
    
    return 0;
}
