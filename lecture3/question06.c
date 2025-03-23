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
} Node;

// 定义队列节点
typedef struct {
    int vertex;             // 顶点编号
    int distance;           // 从起点到该顶点的距离
} QueueNode;

// 定义队列结构
typedef struct {
    QueueNode data[MAX_N];  // 队列数据
    int front;              // 队首指针
    int rear;               // 队尾指针
} Queue;

Node nodes[MAX_N];          // 节点数组
int visited[MAX_N];         // 访问标记数组
int n, m;                   // 节点数量和边数量
Queue queue;                // 队列

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

// 初始化队列
void init_queue() {
    queue.front = queue.rear = 0;
}

// 入队
void enqueue(int vertex, int distance) {
    queue.data[queue.rear].vertex = vertex;
    queue.data[queue.rear].distance = distance;
    queue.rear++;
}

// 出队
QueueNode dequeue() {
    return queue.data[queue.front++];
}

// 判断队列是否为空
int is_empty() {
    return queue.front == queue.rear;
}

// 广度优先搜索
int bfs() {
    // 初始化队列和访问数组
    init_queue();
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }
    
    // 将起点加入队列
    enqueue(1, 0);
    visited[1] = 1;
    
    // 添加层分隔符
    enqueue(-1, -1);
    
    while (!is_empty()) {
        QueueNode current = dequeue();
        
        // 如果是层分隔符
        if (current.vertex == -1) {
            if (!is_empty()) {
                enqueue(-1, -1);  // 为下一层添加分隔符
            }
            continue;
        }
        
        // 如果到达终点
        if (current.vertex == n) {
            return current.distance;
        }
        
        // 遍历所有邻接节点
        AdjNode* adj = nodes[current.vertex].adj_list;
        while (adj != NULL) {
            if (!visited[adj->vertex]) {
                visited[adj->vertex] = 1;
                enqueue(adj->vertex, current.distance + 1);
            }
            adj = adj->next;
        }
    }
    
    return -1;  // 没有找到路径
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
    
    // 计算最短距离
    int result = bfs();
    
    // 输出结果
    printf("%d\n", result);
    
    // 释放内存
    free_graph();
    
    return 0;
}
