#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 150005      // 最大顶点数 (n ≤ 1.5×10^5)
#define MAX_M 150005      // 最大边数 (m ≤ 1.5×10^5)
#define MAX_HEAP 500005   // 优先队列的最大容量，适当取大一些
#define INF 0x3f3f3f3f   // 无限大

// 定义边结构体，用于邻接表存储
typedef struct {
    int v;      // 边的终点
    int w;      // 边的权重
    int next;   // 指向下一条边的索引
} Edge;

Edge edges[MAX_M];
int head[MAX_N];
int edge_count = 0;

// 添加边到邻接表
void add_edge(int u, int v, int w) {
    edges[edge_count].v = v;
    edges[edge_count].w = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count;
    edge_count++;
}

// 定义优先队列节点，存储当前到达某顶点的距离和该顶点编号
typedef struct {
    int d;  // 从起点到该顶点的距离
    int u;  // 顶点编号
} Node;

Node heap[MAX_HEAP];
int heap_size = 0;

// 交换两个节点
void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

// 向小顶堆中插入节点
void push(Node node) {
    heap[++heap_size] = node;
    int i = heap_size;
    while(i > 1 && heap[i].d < heap[i/2].d) {
        swap(&heap[i], &heap[i/2]);
        i /= 2;
    }
}

// 弹出堆顶节点
Node pop() {
    Node top = heap[1];
    heap[1] = heap[heap_size--];
    int i = 1;
    while(i * 2 <= heap_size) {
        int child = i * 2;
        if(child < heap_size && heap[child+1].d < heap[child].d)
            child++;
        if(heap[i].d > heap[child].d) {
            swap(&heap[i], &heap[child]);
            i = child;
        } else {
            break;
        }
    }
    return top;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    // 初始化邻接表：将所有头指针置为 -1
    memset(head, -1, sizeof(head));
    
    // 读入所有边并构建邻接表
    for(int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }
    
    // 初始化最短距离数组，所有距离初始为 INF
    int *dist = (int*)malloc((n + 1) * sizeof(int));
    for(int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[1] = 0;
    
    // 使用 Dijkstra 算法求最短路径，优先队列存储 (distance, vertex)
    push((Node){0, 1});
    
    while(heap_size) {
        Node cur = pop();
        int d = cur.d, u = cur.u;
        // 跳过已经更新的过期节点
        if(d != dist[u])
            continue;
        // 如果达到终点 n，可提前退出
        if(u == n)
            break;
        
        // 遍历 u 的所有邻接边，进行松弛操作
        for(int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].v;
            int nd = d + edges[i].w;
            if(nd < dist[v]) {
                dist[v] = nd;
                push((Node){nd, v});
            }
        }
    }
    
    // 如果终点不可达，输出 -1；否则输出最短距离
    if(dist[n] == INF)
        printf("-1\n");
    else
        printf("%d\n", dist[n]);
    
    free(dist);
    return 0;
}
