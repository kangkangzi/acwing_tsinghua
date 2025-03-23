#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 510
#define INF 0x3f3f3f3f

// 定义邻接表节点
typedef struct AdjNode {
    int vertex;           // 邻接的顶点
    int weight;           // 边的权重
    struct AdjNode* next;
} AdjNode;

// 定义图节点
typedef struct Node {
    AdjNode* adj_list;
} Node;

Node nodes[MAX_N];
int visited[MAX_N];    // 访问标记数组
int cost[MAX_N];       // 到达每个节点的最小代价
int n, m;              // 节点数量和边数量

// 创建新的邻接表节点
AdjNode* create_adj_node(int vertex, int weight) {
    AdjNode* new_node = (AdjNode*)malloc(sizeof(AdjNode));
    new_node->vertex = vertex;
    new_node->weight = weight;
    new_node->next = NULL;
    return new_node;
}

// 添加边（无向图需要添加两条边）
void add_edge(int a, int b, int w) {
    AdjNode* new_node1 = create_adj_node(b, w);
    new_node1->next = nodes[a].adj_list;
    nodes[a].adj_list = new_node1;
    
    AdjNode* new_node2 = create_adj_node(a, w);
    new_node2->next = nodes[b].adj_list;
    nodes[b].adj_list = new_node2;
}

// 找到未访问节点中代价最小的节点
int find_min_cost_vertex() {
    int min_cost = INF;
    int min_vertex = -1;
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && cost[i] < min_cost) {
            min_cost = cost[i];
            min_vertex = i;
        }
    }
    return min_vertex;
}

// Prim算法
int prim() {
    // 初始化访问数组和代价数组
    memset(visited, 0, sizeof(visited));
    for (int i = 1; i <= n; i++) {
        cost[i] = INF;  // 初始时所有节点的代价为无穷大
    }
    
    // 从节点1开始
    cost[1] = 0;
    int total_cost = 0;
    int visited_count = 0;
    
    while (visited_count < n) {
        // 找到未访问节点中代价最小的节点
        int current = find_min_cost_vertex();
        
        // 如果找不到可访问的节点（返回 -1），说明图不连通
        if (current == -1) {
            return INF;  // 用 INF 表示“不连通”
        }
        
        // 访问当前节点
        visited[current] = 1;
        visited_count++;
        
        // 更新从当前节点可达的其他节点的代价
        AdjNode* adj = nodes[current].adj_list;
        while (adj != NULL) {
            int next_vertex = adj->vertex;
            if (!visited[next_vertex]) {
                if (adj->weight < cost[next_vertex]) {
                    cost[next_vertex] = adj->weight;
                }
            }
            adj = adj->next;
        }
    }
    
    // 计算最小生成树的总代价
    total_cost = 0;
    for (int i = 2; i <= n; i++) {
        // 如果有节点的 cost 仍是 INF，说明不连通
        if (cost[i] == INF) {
            return INF;
        }
        total_cost += cost[i];
    }
    
    return total_cost;
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
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        add_edge(a, b, w);
    }
    
    // 计算最小生成树的总代价
    int result = prim();
    
    // 输出结果
    if (result == INF) {
        // 当 prim() 返回 INF，说明图不连通
        printf("impossible\n");
    } else {
        // 否则输出 MST 的总权值
        printf("%d\n", result);
    }
    
    // 释放内存
    free_graph();
    
    return 0;
}
