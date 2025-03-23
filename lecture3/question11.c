#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100010
#define INF 0x3f3f3f3f

// 邻接表节点
typedef struct {
    int to;         // 目标节点
    int weight;     // 边权
    struct Node* next;
} Node;

Node* graph[MAX_N];     // 邻接表
int dist[MAX_N];       // 距离数组
int in_queue[MAX_N];   // 标记节点是否在队列中
int queue[MAX_N];      // 普通队列
int front, rear;       // 队列指针
int n, m;              // n:节点数，m:边数

// 添加边
void add_edge(int from, int to, int weight) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->to = to;
    new_node->weight = weight;
    new_node->next = graph[from];
    graph[from] = new_node;
}

// 释放内存
void free_memory() {
    // 释放邻接表
    for (int i = 1; i <= n; i++) {
        Node* current = graph[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

// SPFA算法求最短路
int spfa() {
    // 初始化距离数组
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[1] = 0;  // 起点到自身的距离为0
    
    // 初始化队列和标记数组
    for (int i = 1; i <= n; i++) {
        in_queue[i] = 0;
    }
    front = rear = 0;
    queue[rear++] = 1;  // 将起点加入队列
    in_queue[1] = 1;
    
    // 主循环
    while (front < rear) {  // 队列判空条件
        int u = queue[front++];  // 出队
        in_queue[u] = 0;  // 标记u已出队
        
        // 遍历u的所有邻接点
        Node* current = graph[u];
        while (current != NULL) {
            int v = current->to;
            int weight = current->weight;
            
            // 如果通过u到达v的路径更短
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                
                // 如果v不在队列中，将其加入队列
                if (!in_queue[v]) {
                    queue[rear++] = v;  // 入队
                    in_queue[v] = 1;
                }
            }
            
            current = current->next;
        }
    }
    
    // 返回到达n号点的最短距离
    return dist[n];
}

int main() {
    scanf("%d %d", &n, &m);
    
    // 初始化邻接表
    for (int i = 1; i <= n; i++) {
        graph[i] = NULL;
    }
    
    // 读入边并构建邻接表
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        add_edge(x, y, z);
    }
    
    // 计算最短路径
    int result = spfa();
    
    // 输出结果
    if (result == INF) {
        printf("impossible\n");
    } else {
        printf("%d\n", result);
    }
    
    // 释放内存
    free_memory();
    
    return 0;
}
