#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2010  // 修改为2000+10，确保足够大
#define INF 0x3f3f3f3f

// 邻接表节点
typedef struct Node {
    int to;         // 目标节点
    int weight;     // 边权
    struct Node* next;
} Node;

Node* graph[MAX_N];     // 邻接表
int dist[MAX_N];        // 距离数组
int cnt[MAX_N];         // 访问计数数组，记录每个节点被松弛的次数
int in_queue[MAX_N];    // 标记节点是否在队列中
int queue[MAX_N];       // 循环队列
int front, rear;        // 队列指针
int n, m;               // n:节点数，m:边数

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

// 从起点s开始检查是否存在负权回路
int check_from_start(int s) {
    // 初始化距离数组和访问计数数组
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        cnt[i] = 0;
    }
    dist[s] = 0;  // 起点到自身的距离为0
    
    // 初始化标记数组
    for (int i = 1; i <= n; i++) {
        in_queue[i] = 0;
    }
    front = rear = 0;
    // 将起点入队（循环队列写法）
    queue[rear] = s;
    rear = (rear + 1) % MAX_N;
    in_queue[s] = 1;
    
    // 主循环（队列不空）
    while (front != rear) {
        int u = queue[front];
        front = (front + 1) % MAX_N;
        in_queue[u] = 0;
        
        // 遍历u的所有邻接点
        Node* current = graph[u];
        while (current != NULL) {
            int v = current->to;
            int weight = current->weight;
            
            // 如果通过u到达v的路径更短
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                cnt[v] = cnt[u] + 1;  // 更新访问计数
                
                // 如果某个节点被松弛的次数超过n-1，说明存在负权回路
                if (cnt[v] >= n) {
                    return 1;
                }
                
                // 如果v不在队列中，将其加入循环队列
                if (!in_queue[v]) {
                    queue[rear] = v;
                    rear = (rear + 1) % MAX_N;
                    in_queue[v] = 1;
                }
            }
            
            current = current->next;
        }
    }
    
    return 0;  // 不存在负权回路
}

// 检查是否存在负权回路（使用SPFA算法）
int check_negative_cycle() {
    // 从每个节点开始尝试
    for (int i = 1; i <= n; i++) {
        if (check_from_start(i)) {
            return 1;  // 如果从某个节点开始找到负权回路，直接返回
        }
    }
    return 0;  // 从所有节点开始都没有找到负权回路
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
    
    // 检查是否存在负权回路
    if (check_negative_cycle()) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    // 释放内存
    free_memory();
    
    return 0;
}
