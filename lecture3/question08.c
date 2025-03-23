#include <stdio.h>
#include <stdlib.h>

#define MAX_N 510
#define INF 0x3f3f3f3f

// 定义边结构
typedef struct Edge {
    int from;       // 起点
    int to;         // 终点
    int weight;     // 权重
    int total_dist; // 从起点到终点的总距离
} Edge;

// 定义邻接表节点
typedef struct AdjNode {
    int vertex;     // 邻接的顶点
    int weight;     // 边的权重
    struct AdjNode* next;
} AdjNode;

// 定义图节点
typedef struct Node {
    AdjNode* adj_list;
} Node;

// 定义优先队列（小顶堆）
typedef struct {
    Edge* data[MAX_N * MAX_N];  // 存储边的指针数组
    int size;                   // 堆的大小
} PriorityQueue;

Node nodes[MAX_N];
int visited[MAX_N];        // 访问标记数组
int dist[MAX_N];          // 最短距离数组
int n, m;                 // 节点数量和边数量
PriorityQueue pq;         // 优先队列

// 创建新的邻接表节点
AdjNode* create_adj_node(int vertex, int weight) {
    AdjNode* new_node = (AdjNode*)malloc(sizeof(AdjNode));
    new_node->vertex = vertex;
    new_node->weight = weight;
    new_node->next = NULL;
    return new_node;
}

// 添加边
void add_edge(int a, int b, int w) {
    AdjNode* new_node = create_adj_node(b, w);
    new_node->next = nodes[a].adj_list;
    nodes[a].adj_list = new_node;
}

// 创建新的边
Edge* create_edge(int from, int to, int weight, int total_dist) {
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->from = from;
    new_edge->to = to;
    new_edge->weight = weight;
    new_edge->total_dist = total_dist;
    return new_edge;
}

// 初始化优先队列
void init_pq() {
    pq.size = 0;
}

// 交换堆中的两个元素
void swap(int i, int j) {
    Edge* temp = pq.data[i];
    pq.data[i] = pq.data[j];
    pq.data[j] = temp;
}

// 上浮操作
void swim(int k) {
    while (k > 1) {
        int parent = k / 2;
        if (pq.data[parent]->total_dist > pq.data[k]->total_dist) {
            swap(parent, k);
            k = parent;
        } else {
            break;
        }
    }
}

// 下沉操作
void sink(int k) {
    while (2 * k <= pq.size) {
        int j = 2 * k;
        if (j < pq.size && pq.data[j]->total_dist > pq.data[j + 1]->total_dist) {
            j++;
        }
        if (pq.data[k]->total_dist > pq.data[j]->total_dist) {
            swap(k, j);
            k = j;
        } else {
            break;
        }
    }
}

// 插入边到优先队列
void pq_insert(Edge* edge) {
    pq.data[++pq.size] = edge;
    swim(pq.size);
}

// 删除并返回最小边
Edge* pq_del_min() {
    if (pq.size == 0) return NULL;
    
    Edge* min = pq.data[1];
    pq.data[1] = pq.data[pq.size--];
    sink(1);
    return min;
}

// Dijkstra算法
int dijkstra() {
    // 初始化距离数组
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[1] = 0;  // 起点距离为0
    
    // 初始化优先队列
    init_pq();
    
    // 将起点连接的所有边加入优先队列
    AdjNode* adj = nodes[1].adj_list;
    while (adj != NULL) {
        Edge* edge = create_edge(1, adj->vertex, adj->weight, adj->weight);
        pq_insert(edge);
        adj = adj->next;
    }
    
    // 主循环
    while (pq.size > 0) {
        Edge* current = pq_del_min();
        
        // 如果终点已经被访问过，跳过这条边
        if (visited[current->to]) {
            free(current);
            continue;
        }
        
        // 标记终点为已访问
        visited[current->to] = 1;
        
        // 更新距离
        if (current->total_dist < dist[current->to]) {
            dist[current->to] = current->total_dist;
        }
        
        // 如果到达终点，直接返回
        if (current->to == n) {
            free(current);
            return dist[n];
        }
        
        // 将终点连接的所有边加入优先队列
        adj = nodes[current->to].adj_list;
        while (adj != NULL) {
            Edge* edge = create_edge(current->to, adj->vertex, adj->weight, 
                                   current->total_dist + adj->weight);
            pq_insert(edge);
            adj = adj->next;
        }
        
        free(current);
    }
    
    // 如果无法到达终点，返回-1
    return -1;
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
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        add_edge(a, b, w);
    }
    
    // 计算最短路径
    int result = dijkstra();
    
    // 输出结果
    printf("%d\n", result);
    
    // 释放内存
    free_graph();
    
    return 0;
}
